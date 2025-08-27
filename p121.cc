#pragma GCC optimize("O3", "unroll-loops")
#pragma GCC option("arch=native", "tune=native")
#include <ios>
auto _ = std::ios::sync_with_stdio(false);

#include <algorithm>
#include <vector>

class Solution {
public:
  int maxProfit(std::vector<int> &prices) {
    int price_size = prices.size();

    std::vector<int> highest;
    highest.reserve(price_size - 1);
    highest.push_back(prices.back());
    for (int i = price_size - 2; i >= 0; --i) {
      highest.push_back(std::max(highest.back(), prices[i]));
    }

    int max_profit{0};

    for (int i = 0; i < price_size - 1; ++i) {
      max_profit =
          std::max(max_profit, highest[price_size - 2 - i] - prices[i]);
    }

    return max_profit;
  }
};
