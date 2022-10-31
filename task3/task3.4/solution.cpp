#include <algorithm>
#include <vector>
#include <stack>

using namespace std;

class Solution {
private:
    size_t argmax(const vector<int>& height) {
        size_t ans = 0;
        size_t mx = height[0];
        for (size_t k = 1; k < height.size(); ++k) {
            if (mx < height[k]) {
                mx = height[k];
                ans = k;
            }
        }
        return ans;
    }
    
    int trap_suff(const vector<int>& height, int start) {
        if (start + 1 == height.size()) {
            return 0;
        }
        int ans = 0;
        stack<int> maxs_inds;
        maxs_inds.push(start);
        for (int k = start + 1; k < height.size(); ++k) {
            ans -= height[k];
            while (height[maxs_inds.top()] < height[k]) {
                maxs_inds.pop();
            }
            maxs_inds.push(k);
        }
        
        int curr_ind = maxs_inds.top();
        maxs_inds.pop();
        while(!maxs_inds.empty()) {
            ans += height[curr_ind] * (curr_ind - maxs_inds.top());
            curr_ind = maxs_inds.top();
            maxs_inds.pop();
        }
        
        return ans;
    }
    
    int trap_pref(const vector<int>& height, int start) {
        if (start == 0) {
            return 0;
        }
        
        int ans = 0;
        stack<int> maxs_inds;
        maxs_inds.push(start);
        
        for (int k = start - 1; k >= 0; --k) {
            ans -= height[k];
            while (height[maxs_inds.top()] < height[k]) {
                maxs_inds.pop();
            }
            maxs_inds.push(k);
        }
        
        int curr_ind = maxs_inds.top();
        maxs_inds.pop();
        while(!maxs_inds.empty()) {
            ans += height[curr_ind] * (maxs_inds.top() - curr_ind);
            curr_ind = maxs_inds.top();
            maxs_inds.pop();
        }
        
        return ans;
    }
    
public:
    int trap(vector<int>& height) {
        auto center = argmax(height);
        return trap_suff(height, center) + trap_pref(height, center);
    }
};