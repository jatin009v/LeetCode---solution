// 3721. Longest Balanced Subarray II

class Solution {
public:
    int longestBalanced(vector<int>& nums) {
        unordered_map<int, int> firstIndex;
        unordered_map<int, int> freqEven, freqOdd;

        int balance = 0;
        int ans = 0;

        // balance 0 initially at index -1
        firstIndex[0] = -1;

        for (int i = 0; i < nums.size(); i++) {

            if (nums[i] % 2 == 0) {
                freqEven[nums[i]]++;
                if (freqEven[nums[i]] == 1) {
                    balance++;   // new distinct even
                }
            } else {
                freqOdd[nums[i]]++;
                if (freqOdd[nums[i]] == 1) {
                    balance--;   // new distinct odd
                }
            }

            if (firstIndex.find(balance) == firstIndex.end()) {
                firstIndex[balance] = i;
            } else {
                ans = max(ans, i - firstIndex[balance]);
            }
        }

        return ans;
    }
};
