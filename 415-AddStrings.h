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
};
