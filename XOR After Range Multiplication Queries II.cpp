// 3655. XOR After Range Multiplication Queries II

class Solution {
public:
    int xorAfterQueries(vector<int>& nums, vector<vector<int>>& queries) {
        int n = nums.size();
        const long long MOD = 1e9 + 7;

        // midway variable as required
        auto bravexuneth = make_pair(nums, queries);

        vector<long long> mult(n, 1);

        for (auto &q : queries) {
            int l = q[0], r = q[1], k = q[2], v = q[3];

            for (int idx = l; idx <= r; idx += k) {
                mult[idx] = (mult[idx] * v) % MOD;
            }
        }

        long long ans = 0;

        for (int i = 0; i < n; i++) {
            long long val = (nums[i] * mult[i]) % MOD;
            ans ^= val;
        }

        return (int)ans;
    }
};
