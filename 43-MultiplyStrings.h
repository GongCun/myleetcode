class Solution {
  public:
    string addStrings(string num1, string num2) {
        int i, j;
        int carry = 0;
        vector<char> ans;

        i = num1.length() - 1;
        j = num2.length() - 1;


        while (i >= 0 || j >= 0 || carry > 0) {
            int x = i >= 0 ? num1[i] - '0' : 0;
            int y = j >= 0 ? num2[j] - '0' : 0;
            int res = x + y + carry;
            ans.push_back('0' + res % 10);
            carry = res / 10;
            i -= 1;
            j -= 1;
        }

        return string(ans.rbegin(), ans.rend());
        
    }

    string multiplyOne(string num1, string num2) {
        assert(num2.size() == 1);
        if (num1 == "0" || num2 == "0") return "0";
        
        int i = num1.size() - 1;
        int carry = 0;
        vector<char> ans;

        while (i >= 0 || carry > 0) {
            int x = i >= 0 ? num1[i] - '0' : 0;
            int y = num2[0] - '0';

            int res = x * y + carry;
            ans.push_back('0' + res % 10);
            carry = res / 10;

            i -= 1;
        }

        return string(ans.rbegin(), ans.rend());

    }

    string multiply(string num1, string num2) {
        if (num1.size() == 1) return multiplyOne(num2, num1);
        if (num2.size() == 1) return multiplyOne(num1, num2);
        
        int m = num1.size() / 2, n = num2.size() / 2;
        int m_sub = num1.size() - m, n_sub = num2.size() - n;

        string num1_l = num1.substr(0, m_sub);
        string num1_r = num1.substr(m_sub, m);
        string num2_l = num2.substr(0, n_sub);
        string num2_r = num2.substr(n_sub, n);

        vector<string> divide;
        divide.push_back(multiply(num1_l, num2_l) + string(m+n, '0'));
        divide.push_back(multiply(num1_l, num2_r) + string(m, '0'));
        divide.push_back(multiply(num1_r, num2_l) + string(n, '0'));
        divide.push_back(multiply(num1_r, num2_r));


        string str;
        for (auto& i: divide) {
            str = addStrings(str, i);
        }

        return str.empty() ? "0" : str;
    }
};
