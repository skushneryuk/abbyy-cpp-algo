#include <vector>
#include <algorithm>

using namespace std;

class Solution {
    int highest_bit(unsigned n) {
        int result = 1;
        while (n >>= 1) {
            result <<= 1;
        }
        return result;
    }

public:
    vector<int> singleNumber(vector<int>& nums) {
        auto xor_of_two = accumulate(nums.begin(), nums.end(), 0, [](int a, int b) { return a^b; });
        auto bit = highest_bit(xor_of_two);

        return {
            accumulate(nums.begin(), nums.end(), 0, [&bit](int a, int b) { return b & bit ? a^b : a; }),
            accumulate(nums.begin(), nums.end(), 0, [&bit](int a, int b) { return b & bit ? a : a^b; })
        };
    }
};