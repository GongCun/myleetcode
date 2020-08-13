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
        assert(num1.size() == 1);
        if (num1 == "0" || num2 == "0") return "0";
        
        int n = num2.size();
        vector<int> res(1 + n, 0);
        for (int i = n - 1; i >= 0; --i) {
            int mul = (num2[i] - '0') * (num1[0] - '0');
            int sum = mul + res[i+1];
            res[i+1] = sum % 10;
            res[i] += sum / 10;
        }

        int i = 0;
        while (i < res.size() && res[i] == 0)
            ++i;

        string str;
        for (; i < res.size(); i++)
            str.push_back('0' + res[i]);

        return str.empty() ? "0" : str;
    }

    string multiply(string num1, string num2) {
        if (num1.size() == 1) return multiplyOne(num1, num2);
        if (num2.size() == 1) return multiplyOne(num2, num1);
        
        int m = num1.size() / 2, n = num2.size() / 2;
        int m_rem = num1.size() - m, n_rem = num2.size() - n;

        //cout << "m = " << m << "; remain = " << num1.size() - m << endl;
        //cout << "n = " << m << "; remain = " << num2.size() - n << endl;

        string num1_l = num1.substr(0, m);
        string num1_r = num1.substr(m, m_rem);
        //cout << "num1_l = " << num1_l << endl << "num1_r = " << num1_r << endl;
        string num2_l = num2.substr(0, n);
        string num2_r = num2.substr(n, n_rem);
        //cout << "num2_l = " << num2_l << endl << "num2_r = " << num2_r << endl;

        vector<string> divide;
        divide.push_back(multiply(num1_l, num2_l) + string(m_rem + n_rem, '0'));
        divide.push_back(multiply(num1_l, num2_r) + string(m_rem, '0'));
        divide.push_back(multiply(num1_r, num2_l) + string(n_rem, '0'));
        divide.push_back(multiply(num1_r, num2_r));


        string str;
        for (auto& i: divide) {
            //cout << "i = " << i << endl;
            str = addStrings(str, i);
        }

        //cout << "%%%%%%%%%%%\n";

        return str.empty() ? "0" : str;
    }
};
