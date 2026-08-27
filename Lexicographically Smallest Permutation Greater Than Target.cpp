// 3720. Lexicographically Smallest Permutation Greater Than Target

class Solution {
public:
    string lexGreaterPermutation(string s, string target) {
        int n = s.size();

        // Sort s so that remaining characters can be
        // placed in lexicographically smallest order.
        sort(s.begin(), s.end());

        // Try every position from right to left.
        for (int i = n - 1; i >= 0; i--) {
            
            // Characters before i must be exactly target[0...i-1].
            // Check whether those characters can be formed from s.
            vector<int> freq(26, 0);

            for (char c : s)
                freq[c - 'a']++;

            bool possible = true;

            for (int j = 0; j < i; j++) {
                int x = target[j] - 'a';

                if (freq[x] == 0) {
                    possible = false;
                    break;
                }

                freq[x]--;
            }

            if (!possible)
                continue;

            // At position i, choose the smallest character
            // that is strictly greater than target[i].
            int cur = target[i] - 'a';

            for (int x = cur + 1; x < 26; x++) {
                if (freq[x] > 0) {
                    string ans = target.substr(0, i);
                    ans += char('a' + x);

                    freq[x]--;

                    // Add remaining characters in sorted order.
                    for (int c = 0; c < 26; c++) {
                        ans += string(freq[c], char('a' + c));
                    }

                    return ans;
                }
            }
        }

        return "";
    }
};
