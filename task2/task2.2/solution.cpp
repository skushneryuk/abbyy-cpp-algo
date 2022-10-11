#include <algorithm>
#include <vector>
#include <map>

using namespace std;

class Solution {
    vector<pair<int, int>> unionDuplicates(const vector<int>& nums) {
        map<int, int> counts;
        for (const auto& num : nums) {
            counts[num] += 1;
        }
        return vector<pair<int, int>>(counts.begin(), counts.end());
    }
    
    void updateResult(const vector<pair<int, int>>& unique_nums, vector<int>& curr_set, size_t curr, vector<vector<int>>& result) {
        if (curr == unique_nums.size()) {
            result.push_back(curr_set);
            return;
        }
        
        updateResult(unique_nums, curr_set, curr + 1, result);
        for (int k = 0; k < unique_nums[curr].second; ++k) {
            curr_set.push_back(unique_nums[curr].first);
            updateResult(unique_nums, curr_set, curr + 1, result);
        }
        
        for (int k = 0; k < unique_nums[curr].second; ++k) {
            curr_set.pop_back();
        }
    }

public:
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        auto unique_nums = unionDuplicates(nums);
        vector<vector<int>> result;
        vector<int> curr_set;
        updateResult(unique_nums, curr_set, 0, result);
        return result;
    }
};