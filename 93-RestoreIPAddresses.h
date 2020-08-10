class Solution {
  private:
    vector<string> temp, ans;

    bool splitIPAddresses(string s, int n) {
        bool res = false;
        
        if (n <= 0) {
            if (s.empty()) {
                string s;
                
                for (vector<string>::iterator it = temp.begin(); it != temp.end(); ++it) {

                    s += (it == temp.begin() ? "" : ".") + *it;
                }
                ans.push_back(move(s));
                return true;
            }

            return false;
        }

        vector<char> v(s.begin(), s.end());
        for (vector<char>::iterator p = v.begin(); p != v.end(); p++) {
            string header = string(v.begin(), p+1);

            if (stoi(header) < 0 || stoi(header) > 255 || to_string(stoi(header)) != header)
                break;

            temp.push_back(header);

            if (splitIPAddresses(string(p+1, v.end()), n-1)) {
                res = true;
            }

            temp.pop_back();

        }

        return res;
    }

  public:
    vector<string> restoreIpAddresses(string s) {
        
        splitIPAddresses(s, 4);
        return ans;
    }
};
