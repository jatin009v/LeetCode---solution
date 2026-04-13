// 1848. Minimum Distance to the Target Element
class Solution {
 public:
  int getMinDistance(vector<int>& nums, int target, int start) {
    int ans = INT_MAX;

    for (int i = 0; i < nums.size(); ++i)
      if (nums[i] == target)
        ans = min(ans, abs(i - start));

    return ans;
  }
};
