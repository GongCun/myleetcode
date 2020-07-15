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
        vector<string> res;
        map<string, bool> visited;
        string key = getHostname(startUrl);
        doit(key, res, visited, startUrl, htmlParser);
        return res;
    }

    void doit(string &key, vector<string> &res, map<string, bool> &visited,
              string startUrl, HtmlParser htmlParser) {
        if (getHostname(startUrl) != key ||
            visited.count(startUrl) > 0) {
            return;
        }

        res.push_back(startUrl);
        visited[startUrl] = true;
        vector<string> abs = htmlParser.getUrls(startUrl);

        if (!abs.empty()) {
            for (string s: abs) {
                doit(key, res, visited, s, htmlParser);
            }
        }
    }
};


