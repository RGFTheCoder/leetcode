#pragma GCC optimize("O3", "unroll-loops")
#pragma GCC option("arch=native", "tune=native")
#include <ios>
auto _ = std::ios::sync_with_stdio(false);

#include <utility>
#include <vector>

class Solution {
public:
  int areaOfMaxDiagonal(std::vector<std::vector<int>> &dimensions) {
    std::pair<int, int> max{0, 0};

    for (const auto &rectangle : dimensions) {
      int diagonal_squared =
          rectangle[0] * rectangle[0] + rectangle[1] * rectangle[1];
      if (max.first < diagonal_squared) {
        max = {diagonal_squared, rectangle[0] * rectangle[1]};
      } else if (max.first == diagonal_squared) {
        int area = rectangle[0] * rectangle[1];
        if (max.second < area)
          max = {diagonal_squared, area};
      }
    }

    return max.second;
  }
};
