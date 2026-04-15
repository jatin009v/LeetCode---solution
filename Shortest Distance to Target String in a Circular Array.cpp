// 2515. Shortest Distance to Target String in a Circular Array

class Solution {
 public:
  int closestTarget(vector<string>& words, string target, int startIndex) {
    const int n = words.size();

    for (int i = 0; i < n; ++i) {
      if (words[(startIndex + i) % n] == target)
        return i;
      if (words[(startIndex - i + n) % n] == target)
        return i;
    }

    return -1;
  }
};
