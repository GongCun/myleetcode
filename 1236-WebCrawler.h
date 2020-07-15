/**
 * // This is the HtmlParser's API interface.
 * // You should not implement it, or speculate about its implementation
 * class HtmlParser {
 *   public:
 *     vector<string> getUrls(string url);
 * };
 */


class Solution {

    string getHostname(string &url) {
        int len = url.length();
        int i;
        for (i = 7; i < len; i++) {
            if (url[i] == '/')
                break;
        }
        return url.substr(7, i-7);
    }

public:

    vector<string> crawl(string startUrl, HtmlParser htmlParser) {
        set<string> visited;
        stack<string> urls;
        urls.push(startUrl);
        string key = getHostname(startUrl);
        while(!urls.empty()) {
            string tmp = urls.top();
            urls.pop();
            
            if (getHostname(tmp) != key ||
                visited.find(tmp) != visited.end()) {
                continue;
            }

            visited.insert(tmp);
            vector<string> adj = htmlParser.getUrls(tmp);
            for (string s: adj) {
                urls.push(s);
            }
        }

        return vector<string>(visited.begin(), visited.end());
    }
};


