// 3942. Minimum Operations to Sort a Permutation
class Solution {
public:
    int minOperations(vector<int>& nums) {
        int n = nums.size();

        for (int k = 0; k < n; k++) {
            bool ok = true;

            for (int i = 0; i < n; i++) {
                if (nums[(i + k) % n] != i) {
                    ok = false;
                    break;
                }
            }

            if (ok) return k;
        }

        vector<int> rev = nums;
        reverse(rev.begin(), rev.end());

        for (int k = 0; k < n; k++) {
            bool ok = true;

            for (int i = 0; i < n; i++) {
                if (rev[(i + k) % n] != i) {
                    ok = false;
                    break;
                }
            }

            if (ok) return k + 1;
        }

        return -1;
    }
};
