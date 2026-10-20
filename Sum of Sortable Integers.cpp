// 3886. Sum of Sortable Integers

class Solution {
public:
    long long sortableIntegers(vector<int>& nums) {
        int n = nums.size();
        long long ans = 0;

        for (int k = 1; k <= n; k++) {
            if (n % k != 0) continue;

            bool valid = true;
            int prev = -1;

            for (int i = 0; i < n && valid; i += k) {
                int drops = 0;
                int start = i;

                for (int j = i; j < i + k; j++) {
                    int next = (j + 1 == i + k) ? i : j + 1;

                    if (nums[j] > nums[next]) {
                        drops++;
                        start = next;
                    }
                }

                if (drops > 1) {
                    valid = false;
                    break;
                }

                for (int j = 0; j < k; j++) {
                    int idx = i + (start - i + j + k) % k;

                    if (prev > nums[idx]) {
                        valid = false;
                        break;
                    }

                    prev = nums[idx];
                }
            }

            if (valid) ans += k;
        }

        return ans;
    }
};
