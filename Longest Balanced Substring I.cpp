// 3713. Longest Balanced Substring I

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int longestBalanced(string s) {
        int n = s.length();
        int ans = 1;  // single character is always balanced

        for (int i = 0; i < n; i++) {
            unordered_map<char, int> freq;

            for (int j = i; j < n; j++) {
                freq[s[j]]++;

                int mn = INT_MAX, mx = INT_MIN;
                for (auto &p : freq) {
                    mn = min(mn, p.second);
                    mx = max(mx, p.second);
                }

                if (mn == mx) {
                    ans = max(ans, j - i + 1);
                }
            }
        }
        return ans;
    }
};
