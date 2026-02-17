// 401. Binary Watch

class Solution {
public:
    vector<string> readBinaryWatch(int turnedOn) {
        vector<string> result;
        for (int h = 0; h < 12; ++h) {
            for (int m = 0; m < 60; ++m) {
                if (__builtin_popcount(h) + __builtin_popcount(m) == turnedOn) {
                    // Format minutes with 2 digits
                    char time[6];
                    sprintf(time, "%d:%02d", h, m);
                    result.push_back(string(time));
                }
            }
        }
        return result;
    }
};

