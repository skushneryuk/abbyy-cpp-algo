#include <algorithm>
#include <vector>

using namespace std;

class Solution {
public:
    int trap(vector<int>& height) {
        vector<int> left_max(height.size()), right_max(height.size());
        
        int ans = 0;
        for (int k = 1; k < height.size(); ++k) {
            left_max[k] = max(left_max[k - 1], height[k - 1]);
        }
        
        for (int k = height.size() - 2; k >= 0; --k) {
            right_max[k] = max(right_max[k + 1], height[k + 1]);
        }
        
        for (int k = 0; k < height.size(); ++k) {
            ans += max(0, min(left_max[k], right_max[k]) - height[k]);
        }
        return ans;
    }
};