#include <algorithm>
#include <vector>

using namespace std;

class Solution {
public:
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        auto processed_nums = nums;
        sort(processed_nums.begin(), processed_nums.end());
        vector<vector<int>> result;
        
        result.push_back(processed_nums);
        while (next_permutation(processed_nums.begin(), processed_nums.end())) {
            result.push_back(processed_nums);
        }
        
        return result;
    }
};