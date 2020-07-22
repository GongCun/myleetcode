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
    /* condition_variable cv_in, cv_out; */
    mutable int task;
    queue<string> bfs_in;
    queue<string> bfs_out;

  public:
    void threadFunc(HtmlParser htmlParser) {
        while (true) {
            unique_lock<mutex> l(mtx);
            string url;
            if (!bfs_in.empty()) {
                url = bfs_in.front();
                bfs_in.pop();
                --task;
            }
            l.unlock();

            if (!url.empty()) {
                vector<string> adj = htmlParser.getUrls(url);
                for (string s: adj) {
                    unique_lock<mutex> l(mtx);
                    bfs_out.push(s);
                }
            }
        }
    }

    vector<string> crawl(string startUrl, HtmlParser htmlParser) {
        key = getHostname(startUrl);
        bfs_out.push(startUrl);
        task = 0;

        for (int i = 0; i < 10; i++) {
            thread t(&Solution::threadFunc, this, htmlParser);
            t.detach();
        }

        while (true) {
            unique_lock<mutex> l(mtx);
            if (task == 0 && bfs_out.empty())
                break;

            if (!bfs_out.empty()) {
                string url = bfs_out.front();
                bfs_out.pop();

                if (getHostname(url) != key ||
                    visited.find(url) != visited.end()) {
                    continue;
                }

                visited.insert(url);
                bfs_in.push(url);
                task++;
            }
        }

        return vector<string>(visited.begin(), visited.end());
    }
};


