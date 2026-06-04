// 3751. Total Waviness of Numbers in Range I
class Solution {
public:
    int waviness(int num) {
        string s = to_string(num);
        int n = s.size();

        if (n < 3) return 0;

        int cnt = 0;

        for (int i = 1; i < n - 1; i++) {
            if (s[i] > s[i - 1] && s[i] > s[i + 1]) {
                cnt++; // Peak
            }
            else if (s[i] < s[i - 1] && s[i] < s[i + 1]) {
                cnt++; // Valley
            }
        }

        return cnt;
    }

    int totalWaviness(int num1, int num2) {
        int ans = 0;

        for (int num = num1; num <= num2; num++) {
            ans += waviness(num);
        }

        return ans;
    }
};
