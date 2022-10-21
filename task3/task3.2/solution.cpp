#include <algorithm>
#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    bool isInterleave(string s1, string s2, string s3) {
        if (s1.size() + s2.size() != s3.size()) {
            return false;
        }
        
        if (s1.size() == 0 || s2.size() == 0) {
            return s1 == s3 || s2 == s3;
        }
        
        vector<char> dp(s2.size(), 1);
        bool s1_prefix = true; 
        
        // инициализация
        for (size_t i2 = 0; i2 < s2.size(); ++i2) {
            dp[i2] = ((i2 == 0 || dp[i2 - 1] == 1) && s2[i2] == s3[i2]) ? 1 : 0;
        }
        
        // пересчет
        for (size_t i1 = 0; i1 < s1.size(); ++i1) {
            s1_prefix = (s1_prefix && s1[i1] == s3[i1]);
            dp[0] = (dp[0] && s1[i1] == s3[i1 + 1]) || (s1_prefix && s2[0] == s3[i1 + 1]);
            for (size_t i2 = 1; i2 < s2.size(); ++i2) {
                dp[i2] = (dp[i2] && s1[i1] == s3[i1 + i2 + 1]) || (dp[i2 - 1] && s2[i2] == s3[i1 + i2 + 1]);
            }
        }
        return dp[s2.size() - 1];
    }
};