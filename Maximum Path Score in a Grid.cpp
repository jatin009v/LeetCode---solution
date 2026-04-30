3742. Maximum Path Score in a Grid

class Solution {
public:
    int maxPathScore(vector<vector<int>>& grid, int k) {
        int m = grid.size(), n = grid[0].size();
        
        vector<vector<int>> dp(n, vector<int>(k + 1, -1));
        dp[0][0] = 0;
        
        for (int i = 0; i < m; i++) {
            vector<vector<int>> new_dp(n, vector<int>(k + 1, -1));
            
            for (int j = 0; j < n; j++) {
                for (int c = 0; c <= k; c++) {
                    
                    if (i > 0 && dp[j][c] != -1) {
                        int cost = (grid[i][j] != 0);
                        int newCost = c + cost;
                        
                        if (newCost <= k) {
                            int score = dp[j][c] + grid[i][j];
                            new_dp[j][newCost] = max(new_dp[j][newCost], score);
                        }
                    }
                    
                    if (j > 0 && new_dp[j - 1][c] != -1) {
                        int cost = (grid[i][j] != 0);
                        int newCost = c + cost;
                        
                        if (newCost <= k) {
                            int score = new_dp[j - 1][c] + grid[i][j];
                            new_dp[j][newCost] = max(new_dp[j][newCost], score);
                        }
                    }
                    
                    if (i == 0 && j == 0 && c == 0) {
                        new_dp[0][0] = 0;
                    }
                }
            }
            
            dp = new_dp;
        }
        
        int ans = -1;
        for (int c = 0; c <= k; c++) {
            ans = max(ans, dp[n - 1][c]);
        }
        
        return ans;
    }
};
