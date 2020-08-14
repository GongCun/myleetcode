class Solution {
  public:
    char pair(char c) {
        switch (c) {
        case ')':
            return '(';
        case ']':
            return '[';
        default:
            return '{';
        }
    }

    bool isValid(string s) {
        if (!s.empty() && s.length() % 2 == 1) return false;
        stack<char> left;

        for (char c: s) {
            if (c == '(' || c == '[' || c == '{')
                left.push(c);
            else {
                if (!left.empty() && pair(c) == left.top())
                    left.pop();
                else
                    return false;
            }
        }

        return left.empty();
    }
};
