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
    mutex mtx;
    string key;
    condition_variable cv_in, cv_out;
    queue<string> bfs_in;
    queue<string> bfs_out;

  public:
    void threadFunc(HtmlParser htmlParser) {

        while (true) {
            unique_lock<mutex> l(mtx);

            while(bfs_in.empty()) {
                cv_in.wait(l);
            }
            string url = bfs_in.front();
            bfs_in.pop();

            vector<string> adj = htmlParser.getUrls(url);
            for (string s: adj) {
                bfs_out.push(s);
            }
            l.unlock();
            cv_out.notify_one();
        }
    }

    vector<string> crawl(string startUrl, HtmlParser htmlParser) {
        key = getHostname(startUrl);
        bfs_out.push(startUrl);

        for (int i = 0; i < 1; i++) {
            thread t(&Solution::threadFunc, this, htmlParser);
            t.detach();
        }

        while (true) {
            unique_lock<mutex> l(mtx);

            while (bfs_out.empty()) {
                cv_out.wait(l);
            }
            string url = bfs_out.front();
            bfs_out.pop();

            if (getHostname(url) != key ||
                visited.find(url) != visited.end()) {
                if (bfs_out.empty())
                    break;
                continue;
            }

            visited.insert(url);
            bfs_in.push(url);
            l.unlock();
            cv_in.notify_one();
        }

        return vector<string>(visited.begin(), visited.end());
    }
};


