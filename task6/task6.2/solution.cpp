#include <vector>
#include <cmath>

using namespace std;

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int min_price = prices[0];
        int max_profit = 0;

        for (int i = 0; i < prices.size(); ++i) {
            if (prices[i] - min_price > max_profit) {
                max_profit = prices[i] - min_price;
            }
            min_price = min(min_price, prices[i]);
        }
        return max_profit;
    }
};