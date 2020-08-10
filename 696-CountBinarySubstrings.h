class Solution {
  public:
    int myCountBinarySubstrings(string& s, int begin) {
        if (begin == s.size())
            return 0;
        
        int i, j, temp;
        for (i = begin; i < s.size() && s[i] == s[begin]; ++i)
            ;
        

        for (j = i; j < s.size(); ++j) {
            if (s[j] != s[i] || j - i + 1  > i - begin)
                break;
        }
        
        return j - i + myCountBinarySubstrings(s, i);

    }

    int countBinarySubstrings(string s) {
        return myCountBinarySubstrings(s, 0);
    }
};
