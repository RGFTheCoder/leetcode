#pragma GCC optimize("O3", "unroll-loops")
#pragma GCC option("arch=native", "tune=native")
#include <ios>
auto _ = std::ios::sync_with_stdio(false);

class Solution {
public:
  long long flowerGame(long long n, long long m) {
    // n * m possible pairs
    // only half are odd sum
    return (n * m) / 2;
  }
};
