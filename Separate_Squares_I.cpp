// 3453. Separate Squares I

class Solution {
public:
    double separateSquares(vector<vector<int>>& squares) {
        double totalArea = 0.0;
        for (auto &s : squares) {
            totalArea += 1.0 * s[2] * s[2];
        }

        double low = 0.0, high = 1e9;
        double half = totalArea / 2.0;

        for (int iter = 0; iter < 100; iter++) {
            double mid = (low + high) / 2.0;
            double below = 0.0;

            for (auto &s : squares) {
                double y = s[1];
                double l = s[2];
                if (mid <= y) {
                    continue;
                } else if (mid >= y + l) {
                    below += l * l;
                } else {
                    below += l * (mid - y);
                }
            }

            if (below < half)
                low = mid;
            else
                high = mid;
        }

        return low;
    }
};
