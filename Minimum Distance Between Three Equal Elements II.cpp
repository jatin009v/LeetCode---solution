// 3741. Minimum Distance Between Three Equal Elements II
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <climits>

using namespace std;

class Solution {
public:
    int minimumDistance(vector<int>& nums) {
        int n = nums.size();
        // Har number ke indices store karne ke liye map
        unordered_map<int, vector<int>> indexMap;
        
        for (int i = 0; i < n; i++) {
            indexMap[nums[i]].push_back(i);
        }
        
        long long minDistance = LLONG_MAX;
        bool found = false;
        
        // Har unique number ke indices ko check karenge
        for (auto& entry : indexMap) {
            vector<int>& indices = entry.second;
            
            // Agar number 3 baar ya usse zyada aaya hai
            if (indices.size() >= 3) {
                found = true;
                // Teen lagatar indices (i, j, k) check karein
                // Distance = 2 * (indices[k] - indices[i])
                for (int i = 0; i <= indices.size() - 3; i++) {
                    int first = indices[i];
                    int third = indices[i + 2];
                    
                    long long currentDist = 2LL * (third - first);
                    minDistance = min(minDistance, currentDist);
                }
            }
        }
        
        return found ? (int)minDistance : -1;
    }
};
