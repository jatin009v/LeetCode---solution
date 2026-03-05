// 1758. Minimum Changes To Make Alternating Binary String

class Solution {
public:
    int minOperations(string s) {
        int change1 = 0; // pattern 0101
        int change2 = 0; // pattern 1010
        
        for(int i = 0; i < s.length(); i++) {
            
            // Pattern 0101...
            if(i % 2 == 0) {
                if(s[i] != '0') change1++;
            } else {
                if(s[i] != '1') change1++;
            }
            
            // Pattern 1010...
            if(i % 2 == 0) {
                if(s[i] != '1') change2++;
            } else {
                if(s[i] != '0') change2++;
            }
        }
        
        return min(change1, change2);
    }
};
