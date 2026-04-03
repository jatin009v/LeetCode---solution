// Maximum Walls Destroyed by Robots

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int maxWalls(vector<int>& robots, vector<int>& distance, vector<int>& walls) {
        int n = robots.size();
        if (n == 0) return 0;

        // 1. Robots aur unke distances ko sort karein
        vector<pair<int, int>> r(n);
        for (int i = 0; i < n; ++i) {
            r[i] = {robots[i], distance[i]};
        }
        sort(r.begin(), r.end());
        
        // 2. Walls ko sort karein taaki binary search (upper_bound/lower_bound) kaam kare
        sort(walls.begin(), walls.end());

        // dp[i][0] -> Max walls destroyed up to robot i, if robot i fires LEFT
        // dp[i][1] -> Max walls destroyed up to robot i, if robot i fires RIGHT
        vector<vector<int>> dp(n, vector<int>(2, 0));

        for (int i = 0; i < n; ++i) {
            long long pos = r[i].first;
            long long dist = r[i].second;

            // --- LEFT FIRE OPTION ---
            long long left_limit = pos - dist;
            // Robot block: Bullet pichle robot se aage nahi ja sakti
            if (i > 0) {
                left_limit = max(left_limit, (long long)r[i-1].first + 1);
            }
            int walls_left = countWallsInRange(walls, left_limit, pos);
            
            if (i == 0) {
                dp[i][0] = walls_left;
            } else {
                dp[i][0] = max(dp[i-1][0], dp[i-1][1]) + walls_left;
            }

            // --- RIGHT FIRE OPTION ---
            long long right_limit = pos + dist;
            // Robot block: Bullet agle robot se aage nahi ja sakti
            if (i < n - 1) {
                right_limit = min(right_limit, (long long)r[i+1].first - 1);
            }
            int walls_right = countWallsInRange(walls, pos, right_limit);
            
            if (i == 0) {
                dp[i][1] = walls_right;
            } else {
                dp[i][1] = max(dp[i-1][0], dp[i-1][1]) + walls_right;
            }
        }

        // Dono options mein se jo maximum ho
        return max(dp[n-1][0], dp[n-1][1]);
    }

private:
    // Binary Search to find number of walls in range [L, R]
    int countWallsInRange(const vector<int>& walls, long long L, long long R) {
        if (L > R) return 0;
        auto it_start = lower_bound(walls.begin(), walls.end(), (int)L);
        auto it_end = upper_bound(walls.begin(), walls.end(), (int)R);
        return (int)distance(it_start, it_end);
    }
};
