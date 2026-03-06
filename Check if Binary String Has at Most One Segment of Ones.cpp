// 1784. Check if Binary String Has at Most One Segment of Ones

class Solution {
 public:
  bool checkOnesSegment(string s) {
    return s.find("01") == string::npos;
  }
};
