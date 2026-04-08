// 3653. XOR After Range Multiplication Queries I

#include <vector>
#include <iostream>

using namespace std;

class Solution {
public:
    int xorAfterQueries(vector<int>& nums, vector<vector<int>>& queries) {
        long long MOD = 1e9 + 7;
        int n = nums.size();

        // Har query ko process karein
        for (const auto& q : queries) {
            int li = q[0];
            int ri = q[1];
            int ki = q[2];
            long long vi = q[3];

            // Index li se start karke ki ke gaps mein multiply karein
            for (int idx = li; idx <= ri; idx += ki) {
                nums[idx] = (1LL * nums[idx] * vi) % MOD;
            }
        }

        // Final array ka XOR sum nikaalein
        int xor_sum = 0;
        for (int val : nums) {
            xor_sum ^= val;
        }

        return xor_sum;
    }
};
