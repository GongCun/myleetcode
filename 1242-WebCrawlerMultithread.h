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
    mutex m;
    string key;

  public:
    void threadFunc(string& startUrl, HtmlParser& htmlParser) {

        doit(startUrl, htmlParser);

    }

    /* bool haveVisited(string& startUrl) { */
    /*     lock_guard<mutex> l(m); */
    /*     return visited.find(startUrl) != visited.end(); */
    /* } */

    vector<string> crawl(string startUrl, HtmlParser htmlParser) {
        key = getHostname(startUrl);
        doit(startUrl, htmlParser);
        return vector<string>(visited.begin(), visited.end());
    }

    void doit(string& startUrl, HtmlParser& htmlParser) {
        unique_lock<mutex> l(m);
        
        if (getHostname(startUrl) != key ||
            visited.find(startUrl) != visited.end()) {
            return;
        }

        visited.insert(startUrl);
        l.unlock();
        
        vector<string> adj = htmlParser.getUrls(startUrl);
        vector<thread> threads;

        for (auto s: adj) {
            threads.emplace_back(&Solution::threadFunc, this, ref(s), ref(htmlParser));
        }

        for (auto& entry: threads)
            entry.join();
    }
};


