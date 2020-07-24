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
    mutex mtx;
    string key;
    condition_variable cv_in, cv_out;

  public:
    void threadFunc(HtmlParser& htmlParser, queue<string>& bfs_in, queue<string>& bfs_out) {

        while (true) {
            unique_lock<mutex> l(mtx);

            while(bfs_in.empty()) {
                cv_in.wait(l);
            }
            string url = bfs_in.front();
            bfs_in.pop();
            l.unlock();

            vector<string> adj = htmlParser.getUrls(url);
            for (string s: adj) {
                unique_lock<mutex> l(mtx);
                bfs_out.push(s);
                l.unlock();
                cv_out.notify_one();
            }
        }
    }

    vector<string> crawl(string startUrl, HtmlParser htmlParser) {
        key = getHostname(startUrl);
        bfs_out.push(startUrl);
        set<string> visited;
        queue<string> bfs_in;
        queue<string> bfs_out;

        for (int i = 0; i < 10; i++) {
            thread t(&Solution::threadFunc, this, ref(htmlParser), ref(bfs_int), ref(bfs_out));
            t.detach();
        }

        while (true) {
            unique_lock<mutex> l(mtx);

            while (bfs_out.empty()) {
                if (cv_out.wait_for(l, chrono::milliseconds(20)) == cv_status::timeout)
                    goto end;
            }

            string url = bfs_out.front();
            bfs_out.pop();

            if (getHostname(url) != key ||
                visited.find(url) != visited.end()) {
                cv_in.notify_one();
                continue;
            }

            
            //cout << url << endl;
            
            visited.insert(url);
            bfs_in.push(url);
            cv_in.notify_one();
        }
      end:
        return vector<string>(visited.begin(), visited.end());
    }
};


