// 3660. Jump Game IX

#include <vector>
#include <algorithm>
#include <stack>
#include <queue>

using namespace std;

class Solution {
public:
    vector<int> maxValue(vector<int>& nums) {
        int n = nums.size();
        vector<int> ans(n);
        vector<vector<int>> adj(n);

        // 1. Monotonic Stack to find valid jumps (Edges in our graph)
        stack<int> s1, s2;
        for (int i = 0; i < n; i++) {
            // Forward Jump: Nearest smaller to the right
            while (!s1.empty() && nums[s1.top()] > nums[i]) {
                adj[s1.top()].push_back(i);
                s1.pop();
            }
            s1.push(i);
        }
        
        stack<int> s3;
        for (int i = n - 1; i >= 0; i--) {
            // Backward Jump: Nearest larger to the left
            while (!s3.empty() && nums[s3.top()] < nums[i]) {
                adj[s3.top()].push_back(i);
                s3.pop();
            }
            s3.push(i);
        }

        // 2. Since we want the MAXIMUM value reachable, and it's a reachability problem
        // we can use a BFS-like approach starting from the largest elements.
        // Or simply realize: the result for index i is the max of nums[i] and any reachable node's value.
        
        // We sort indices by their values to process larger values first
        vector<int> indices(n);
        for(int i=0; i<n; ++i) indices[i] = i;
        sort(indices.begin(), indices.end(), [&](int a, int b) {
            return nums[a] > nums[b];
        });

        for(int i=0; i<n; i++) ans[i] = nums[i];

        // Process in decreasing order of values
        for(int idx : indices) {
            for(int neighbor : adj[idx]) {
                ans[idx] = max(ans[idx], ans[neighbor]);
            }
        }
        
        // Final pass: Since backward jumps can reach larger numbers, 
        // we need to ensure the values are fully propagated.
        // Sorting and 2-3 passes or a simple BFS is safer.
        for(int iterations = 0; iterations < 2; iterations++) {
            for(int i = 0; i < n; i++) {
                for(int neighbor : adj[i]) {
                    ans[i] = max(ans[i], ans[neighbor]);
                }
            }
            for(int i = n - 1; i >= 0; i--) {
                for(int neighbor : adj[i]) {
                    ans[i] = max(ans[i], ans[neighbor]);
                }
            }
        }

        return ans;
    }
};
