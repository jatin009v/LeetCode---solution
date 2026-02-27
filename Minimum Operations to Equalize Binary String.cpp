// 3666. Minimum Operations to Equalize Binary String

class Solution {
public:
    int minOperations(string s, int k) {
        int n = s.length();
        int Z = 0;

        for(char c : s) {
            if(c == '0')
                Z++;
        }

        if(Z == 0)
            return 0;

        if(k > n)
            return -1;

        long long x = (Z + k - 1) / k;

        for(int i = 0; i < 2; i++) {
            if(x * k >= Z && ((x * k - Z) % 2 == 0))
                return x;
            x++;
        }

        return -1;
    }
};
