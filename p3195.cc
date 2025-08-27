#pragma GCC optimize("O3", "unroll-loops")
#pragma GCC option("arch=native", "tune=native")
#include <ios>
auto _ = std::ios::sync_with_stdio(false);

#include <algorithm>
#include <iostream>
#include <vector>

class Solution {
public:
  int minimumArea(std::vector<std::vector<int>> &grid) {
    std::ios_base::sync_with_stdio(false);

    int dim0_size = grid.size();
    int dim1_size = grid[0].size();

    int rect_dim0_min = INT_MAX;
    int rect_dim0_max = 0;
    int rect_dim1_min = INT_MAX;
    int rect_dim1_max = 0;

    for (int dim0 = 0; dim0 < dim0_size; dim0++) {
      for (int dim1 = 0; dim1 < dim1_size; dim1++) {
        if (grid[dim0][dim1] == 1) {
          rect_dim0_min = std::min(rect_dim0_min, dim0);
          rect_dim0_max = std::max(rect_dim0_max, dim0);
          rect_dim1_min = std::min(rect_dim1_min, dim1);
          rect_dim1_max = std::max(rect_dim1_max, dim1);
        }
      }
    }

    // Calculate area with difference plus one
    // A 1x1 square will have the same min and max,
    // so add 1 for left vs right edge.
    return (rect_dim0_max - rect_dim0_min + 1) *
           (rect_dim1_max - rect_dim1_min + 1);
  }
};
