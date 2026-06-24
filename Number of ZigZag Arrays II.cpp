// 3700. Number of ZigZag Arrays II


class Solution {
public:
    static const long long MOD = 1000000007LL;

    using Matrix = vector<vector<long long>>;

    Matrix multiply(const Matrix& A, const Matrix& B) {
        int n = A.size();
        Matrix C(n, vector<long long>(n, 0));

        for (int i = 0; i < n; i++) {
            for (int k = 0; k < n; k++) {
                if (A[i][k] == 0) continue;

                long long aik = A[i][k];

                for (int j = 0; j < n; j++) {
                    C[i][j] = (C[i][j] + aik * B[k][j]) % MOD;
                }
            }
        }
        return C;
    }

    vector<long long> matVec(const Matrix& A,
                             const vector<long long>& v) {
        int n = A.size();
        vector<long long> res(n, 0);

        for (int i = 0; i < n; i++) {
            long long cur = 0;

            for (int j = 0; j < n; j++) {
                cur = (cur + A[i][j] * v[j]) % MOD;
            }

            res[i] = cur;
        }

        return res;
    }

    vector<long long> applyPower(Matrix M,
                                 long long exp,
                                 vector<long long> vec) {
        while (exp > 0) {
            if (exp & 1) {
                vec = matVec(M, vec);
            }

            M = multiply(M, M);
            exp >>= 1;
        }

        return vec;
    }

    int zigZagArrays(int n, int l, int r) {
        int m = r - l + 1;

        Matrix C(m, vector<long long>(m, 0));

        // C(i,j) = min(i,j) - 1  (1-indexed)
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < m; j++) {
                C[i][j] = min(i, j); // because indices are 0-based
            }
        }

        vector<long long> base;
        long long exp;

        if (n % 2 == 0) {
            // V_even
            base.resize(m);
            for (int i = 0; i < m; i++) {
                base[i] = i; // i = (value-1)
            }

            exp = n / 2 - 1;
        } else {
            // V_odd
            base.resize(m);

            for (int i = 0; i < m; i++) {
                long long a = i; // value-1

                base[i] =
                    (a * m - a * (a + 1) / 2) % MOD;
            }

            exp = (n - 3) / 2;
        }

        vector<long long> res = applyPower(C, exp, base);

        long long ans = 0;
        for (long long x : res) {
            ans = (ans + x) % MOD;
        }

        ans = (2 * ans) % MOD; // symmetry: up + down

        return (int)ans;
    }
};
