// 3499. Maximize Active Section with Trade I

class Solution {
public:
    int maxActiveSectionsAfterTrade(string s) {
        int initialOnes = 0;
        for (char c : s) {
            if (c == '1') initialOnes++;
        }

        string t = "1" + s + "1";

        // Run-length encoding: {character, length}
        vector<pair<char, int>> runs;
        for (int i = 0; i < (int)t.size();) {
            int j = i;
            while (j < (int)t.size() && t[j] == t[i]) j++;
            runs.push_back({t[i], j - i});
            i = j;
        }

        vector<int> zeroLens;
        unordered_map<int, int> zeroOrder; // run index -> zero run order

        for (int i = 0; i < (int)runs.size(); i++) {
            if (runs[i].first == '0') {
                zeroOrder[i] = zeroLens.size();
                zeroLens.push_back(runs[i].second);
            }
        }

        int best = initialOnes;

        int m = zeroLens.size();
        vector<int> pref(m + 1, 0), suff(m + 1, 0);

        for (int i = 0; i < m; i++)
            pref[i + 1] = max(pref[i], zeroLens[i]);

        for (int i = m - 1; i >= 0; i--)
            suff[i] = max(suff[i + 1], zeroLens[i]);

        // Try removing every interior 1-block
        for (int i = 1; i + 1 < (int)runs.size(); i++) {
            if (runs[i].first != '1') continue;

            int oneLen = runs[i].second;
            int leftZero = runs[i - 1].second;
            int rightZero = runs[i + 1].second;

            int z = zeroOrder[i - 1];

            // Largest zero block not adjacent to this 1-block
            int otherZero = max(pref[z], suff[z + 2]);

            int gain = max(leftZero + rightZero, otherZero - oneLen);

            best = max(best, initialOnes + gain);
        }

        return best;
    }
};
