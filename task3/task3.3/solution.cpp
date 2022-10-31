#include <algorithm>
#include <vector>

using namespace std;

class Solution {
public:
    int coinChange(const vector<int>& coins, int amount) {
        vector<int> dp(amount + 1, amount + 1);
        dp[0] = 0;
        for (size_t sum = 0; sum < amount; ++sum) {
            if (dp[sum] == amount + 1) {
                continue;
            }
            for (const auto& coin : coins) {
                if (sum + coin <= amount) {
                    dp[sum + coin] = min(dp[sum + coin], dp[sum] + 1);
                }
            }
        }
        return dp[amount] == amount + 1 ? -1 : dp[amount];
    }
};