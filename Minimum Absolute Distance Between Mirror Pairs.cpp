// 3761. Minimum Absolute Distance Between Mirror Pairs

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int reverseNum(int x) {
        int rev = 0;
        while (x > 0) {
            rev = rev * 10 + (x % 10);
            x /= 10;
        }
        return rev;
    }

    int minMirrorPairDistance(vector<int>& nums) {
        unordered_map<int, int> mp;
        int ans = INT_MAX;

        for (int i = 0; i < nums.size(); i++) {
            // check if current number exists as reverse of some previous
            if (mp.find(nums[i]) != mp.end()) {
                ans = min(ans, i - mp[nums[i]]);
            }

            // store reverse of current number
            int rev = reverseNum(nums[i]);
            mp[rev] = i;
        }

        return (ans == INT_MAX) ? -1 : ans;
    }
};
