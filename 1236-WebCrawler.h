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
public:
    vector<string> crawl(string startUrl, HtmlParser htmlParser) {
        set<string> visited;
        string key = getHostname(startUrl);
        doit(key, visited, startUrl, htmlParser);
        return vector<string>(visited.begin(), visited.end());
    }

    void doit(string &key, set<string> &visited,
                      string startUrl, HtmlParser htmlParser) {
        if (getHostname(startUrl) != key ||
            visited.find(startUrl) != visited.end()) {
            return;
        }

        visited.insert(startUrl);
        vector<string> paths = htmlParser.getUrls(startUrl);

        for (string s: paths) {
            doit(key, visited, s, htmlParser);
        }
    }
};


