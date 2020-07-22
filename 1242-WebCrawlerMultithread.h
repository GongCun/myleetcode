/**
 * // This is the HtmlParser's API interface.
 * // You should not implement it, or speculate about its implementation
 * class HtmlParser {
 *   public:
 *     vector<string> getUrls(string url);
 * };
 */

string getHostname(string &url) {
    int len = url.length();
    int i;
    for (i = 7; i < len; i++) {
        if (url[i] == '/')
            break;
    }
    return url.substr(7, i-7);
}

class Solution {
  private:
    set<string> visited;
    mutex mtx1, mtx2;
    string key;
    condition_variable cv_in, cv_out;
    queue<string> bfs_in;
    queue<string> bfs_out;

  public:
    void threadFunc(HtmlParser htmlParser) {

        while (true) {
            unique_lock<mutex> l(mtx1);

            while(bfs_in.empty()) {
                cv_in.wait(l);
            }
            string url = bfs_in.front();
            bfs_in.pop();
            l.unlock();

            vector<string> adj = htmlParser.getUrls(url);
            if (adj.empty()) {
                cv_out.notify_one();
            } else {
                for (string s: adj) {
                    unique_lock<mutex> l(mtx2);
                    bfs_out.push(s);
                    cv_out.notify_one();
                }
            }
        }
    }

    vector<string> crawl(string startUrl, HtmlParser htmlParser) {
        key = getHostname(startUrl);
        bfs_out.push(startUrl);

        for (int i = 0; i < 10; i++) {
            thread t(&Solution::threadFunc, this, htmlParser);
            t.detach();
        }

        while (true) {
            unique_lock<mutex> l(mtx2);

            while (bfs_out.empty()) {
                cv_out.wait(l);
                if (bfs_in.empty() && bfs_out.empty())
                    goto end;

            }
            string url = bfs_out.front();
            bfs_out.pop();
            l.unlock();

            if (getHostname(url) != key ||
                visited.find(url) != visited.end()) {
                cv_in.notify_one();
                continue;
            }
            visited.insert(url);

            {
                unique_lock<mutex> l(mtx1);
                bfs_in.push(url);
                cv_in.notify_one();
            }
        }
      end:
        return vector<string>(visited.begin(), visited.end());
    }
};


