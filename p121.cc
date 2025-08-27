#pragma GCC optimize("O3", "unroll-loops")
#pragma GCC option("arch=native", "tune=native")
#include <ios>
// auto _ = std::ios::sync_with_stdio(false);

#include <algorithm>
#include <vector>

class Solution {
public:
  int maxProfit(std::vector<int> &prices) {
    int price_size = prices.size();

    int lower_buy = 0;
    int profit = 0;

    for (int i = 1; i < price_size; ++i) {
      if (prices[lower_buy] >= prices[i])
        lower_buy = i;
      else
        profit = std::max(profit, prices[i] - prices[lower_buy]);
    }

    return profit;
  }
};
