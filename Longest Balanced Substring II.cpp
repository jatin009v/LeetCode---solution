3714. Longest Balanced Substring II

class Solution {
public:
    int longestBalanced(string s) {
        int n = s.size();
        int ans = 0;

        // try all possible frequencies
        for (int k = 1; k <= n; k++) {

            int cnt[3] = {0, 0, 0};
            int distinct = 0;
            int left = 0;

            for (int right = 0; right < n; right++) {
                int r = s[right] - 'a';
                if (cnt[r] == 0) distinct++;
                cnt[r]++;

                // shrink window if any count > k
                while (cnt[r] > k) {
                    int l = s[left] - 'a';
                    cnt[l]--;
                    if (cnt[l] == 0) distinct--;
                    left++;
                }

                // check balanced condition
                bool ok = true;
                for (int i = 0; i < 3; i++) {
                    if (cnt[i] != 0 && cnt[i] != k) {
                        ok = false;
                        break;
                    }
                }

                if (ok) {
                    ans = max(ans, right - left + 1);
                }
            }
        }
        return ans;
    }
};
