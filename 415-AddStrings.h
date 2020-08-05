class Solution {
  private:
    inline int ctoi(char c) const {
        return c - 48;
    }

    inline char itoc(int i) const {
        return i + 48;
    }

  public:
    string addStrings(string num1, string num2) {
        int len;
        int carry = 0;
        string s1, s2;
        vector<char> v,r ;

        if (num1.length() < num2.length()) {
            s1 = string(num2.length() - num1.length(), '0') + num1;
            s2 = num2;
        } else {
            s1 = string(num1.length() - num2.length(), '0') + num2;
            s2 = num1;
        }

        assert(s1.length() == s2.length());

        for (int i = s1.length() - 1; i >= 0; i--) {
            int t = ctoi(s1[i]) + ctoi(s2[i]) + carry;
            v.push_back(itoc(t % 10));
            carry = (t > 9 ? 1 : 0);
        }

        if (carry > 0)
            v.push_back(itoc(carry));

        string res = string(v.rbegin(), v.rend());
        return res;
        
    }
};
