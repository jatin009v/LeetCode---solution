// 3753. Total Waviness of Numbers in Range II

class Solution {
public:
    struct Node {
        long long cnt;   // number of valid numbers
        long long wav;   // total waviness
    };

    string s;
    Node dp[20][2][11][11];
    bool vis[20][2][11][11];

    Node dfs(int pos, int started, int prev2, int prev1, bool tight) {
        if (pos == (int)s.size()) {
            return {1, 0};
        }

        if (!tight && vis[pos][started][prev2][prev1]) {
            return dp[pos][started][prev2][prev1];
        }

        int limit = tight ? (s[pos] - '0') : 9;

        Node res = {0, 0};

        for (int d = 0; d <= limit; d++) {
            bool ntight = tight && (d == limit);

            if (!started) {
                if (d == 0) {
                    Node nxt = dfs(pos + 1, 0, 10, 10, ntight);
                    res.cnt += nxt.cnt;
                    res.wav += nxt.wav;
                } else {
                    Node nxt = dfs(pos + 1, 1, 10, d, ntight);
                    res.cnt += nxt.cnt;
                    res.wav += nxt.wav;
                }
            } else {
                long long add = 0;

                if (prev2 != 10) {
                    bool peak = (prev1 > prev2 && prev1 > d);
                    bool valley = (prev1 < prev2 && prev1 < d);

                    if (peak || valley) add = 1;
                }

                Node nxt = dfs(pos + 1, 1, prev1, d, ntight);

                res.cnt += nxt.cnt;
                res.wav += nxt.wav + add * nxt.cnt;
            }
        }

        if (!tight) {
            vis[pos][started][prev2][prev1] = true;
            dp[pos][started][prev2][prev1] = res;
        }

        return res;
    }

    long long solve(long long n) {
        if (n <= 0) return 0;

        s = to_string(n);
        memset(vis, 0, sizeof(vis));

        Node ans = dfs(0, 0, 10, 10, true);
        return ans.wav;
    }

    long long totalWaviness(long long num1, long long num2) {
        return solve(num2) - solve(num1 - 1);
    }
};
