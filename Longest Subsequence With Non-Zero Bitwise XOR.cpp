// 3702. Longest Subsequence With Non-Zero Bitwise XOR

class Solution {
public:
    int longestSubsequence(vector<int>& nums) {
        int n = nums.size();
        int xr = 0;
        bool hasNonZero = false;

        for (int x : nums) {
            xr ^= x;
            if (x != 0) {
                hasNonZero = true;
            }
        }

        if (xr != 0) {
            return n;
        }

        return hasNonZero ? n - 1 : 0;
    }
};
