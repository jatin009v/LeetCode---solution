// 3754. Concatenate Non-Zero Digits and Multiply by Sum I

class Solution {
public:
    int sumAndMultiply(int n) {
        int x = 0, sum = 0;

        string s = to_string(n);

        for (char c : s) {
            if (c != '0') {
                x = x * 10 + (c - '0');
                sum += c - '0';
            }
        }

        return x * sum;
    }
};
