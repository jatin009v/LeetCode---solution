// 3739. Count Subarrays With Majority Element II

class Solution {
public:
    struct Fenwick {
        int n;
        vector<int> bit;

        Fenwick(int sz) {
            n = sz;
            bit.assign(n + 1, 0);
        }

        void update(int idx, int val) {
            while (idx <= n) {
                bit[idx] += val;
                idx += idx & -idx;
            }
        }

        int query(int idx) {
            int res = 0;
            while (idx > 0) {
                res += bit[idx];
                idx -= idx & -idx;
            }
            return res;
        }
    };

    long long countSubarrays(vector<int>& nums, int target) {
        int n = nums.size();

        int offset = n + 2;
        Fenwick bit(2 * n + 5);

        long long ans = 0;
        int prefix = 0;

        // prefix sum = 0
        bit.update(offset, 1);

        for (int x : nums) {
            if (x == target)
                prefix++;
            else
                prefix--;

            // Count previous prefix sums < current prefix
            ans += bit.query(prefix + offset - 1);

            bit.update(prefix + offset, 1);
        }

        return ans;
    }
};
