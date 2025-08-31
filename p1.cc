#pragma GCC optimize("O3", "unroll-loops")
#pragma GCC option("arch=native", "tune=native")
#include <ios>
auto _ = std::ios::sync_with_stdio(false);

#include <unordered_map>
#include <vector>

class Solution {
public:
  std::vector<int> twoSum(std::vector<int> &nums, int target) {
    std::unordered_map<int, int> difference_map{};

    for (int j = 0; j < nums.size(); j++) {
      int n2 = nums[j];
      if (difference_map.find(target - n2) != difference_map.end())
        return {difference_map[target - n2], j};

      difference_map[n2] = j;
    }

    __builtin_unreachable();
  }
};
