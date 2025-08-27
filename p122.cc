#include <vector>
#pragma GCC optimize("O3", "unroll-loops")
#pragma GCC option("arch=native", "tune=native")
#include <ios>
auto _ = std::ios::sync_with_stdio(false);

class Solution {
public:
  int maxProfit(std::vector<int> &prices) {
    int profits = 0;
    int s = prices.size() - 1;

    for (int i = 0; i < s; ++i) {
      if (prices[i] < prices[i + 1])
        profits += prices[i + 1] - prices[i];
    }

    return profits;
  }
};
