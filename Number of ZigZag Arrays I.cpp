// 3699. Number of ZigZag Arrays I

class Solution {
public:
    static const int MOD = 1000000007;

    int zigZagArrays(int n, int l, int r) {
        int m = r - l + 1;

        vector<long long> up(m + 1, 0), down(m + 1, 0);

        // Length = 2 initialization
        for (int v = 1; v <= m; v++) {
            up[v] = v - 1;      // previous value smaller than v
            down[v] = m - v;    // previous value greater than v
        }

        if (n == 2) {
            long long ans = 0;
            for (int v = 1; v <= m; v++) {
                ans = (ans + up[v] + down[v]) % MOD;
            }
            return (int)ans;
        }

        for (int len = 3; len <= n; len++) {
            vector<long long> newUp(m + 1, 0), newDown(m + 1, 0);

            vector<long long> prefDown(m + 1, 0);
            vector<long long> prefUp(m + 1, 0);

            for (int i = 1; i <= m; i++) {
                prefDown[i] = (prefDown[i - 1] + down[i]) % MOD;
                prefUp[i] = (prefUp[i - 1] + up[i]) % MOD;
            }

            long long totalUp = prefUp[m];

            for (int v = 1; v <= m; v++) {
                // Last move becomes UP => previous move must be DOWN
                newUp[v] = prefDown[v - 1];

                // Last move becomes DOWN => previous move must be UP
                newDown[v] = (totalUp - prefUp[v] + MOD) % MOD;
            }

            up.swap(newUp);
            down.swap(newDown);
        }

        long long ans = 0;
        for (int v = 1; v <= m; v++) {
            ans = (ans + up[v] + down[v]) % MOD;
        }

        return (int)ans;
    }
};
