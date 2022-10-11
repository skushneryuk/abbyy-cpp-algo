#include <algorithm>
#include <vector>
#include <string>

using namespace std;

class Solution {
    void updateResult(size_t to_open, size_t to_close, string& curr_str, vector<string>& result) {
        if (to_open == 0 && to_close == 0) {
            result.push_back(curr_str);
            return;
        }
        
        if (to_open > 0) {
            curr_str.push_back('(');
            updateResult(to_open - 1, to_close, curr_str, result);
            curr_str.pop_back();
        }
        
        if (to_close > to_open) {
            curr_str.push_back(')');
            updateResult(to_open, to_close - 1, curr_str, result);
            curr_str.pop_back();
        }
    }

public:
    vector<string> generateParenthesis(int n) {
        vector<string> result;
        string curr_str;
        updateResult(n, n, curr_str, result);
        return result;
    }
};