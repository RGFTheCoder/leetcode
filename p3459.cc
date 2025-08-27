#pragma GCC optimize("O3", "unroll-loops")

#include <algorithm>
#include <iostream>
#include <vector>
class Solution {
  constexpr static int dirx[]{1, -1, -1, 1};
  constexpr static int diry[]{-1, -1, 1, 1};

  int w;
  int h;

  std::vector<int> memo;

public:
  int lenOfVDiagonal(std::vector<std::vector<int>> &grid) {

    ios::sync_with_stdio(false);

    w = grid.size();
    h = grid[0].size();

    memo.resize(w * h * 16);
    for (int i = 0; i < w * h * 16; ++i) {
      memo[i] = -1;
    }

    int r = 0;

    for (int x = 0; x < w; x++) {
      for (int y = 0; y < h; y++) {
        if (grid[x][y] == 1) {

          // std::cout << x << " " << y << "o\n";
          r = std::max({
              r,
              len(grid, 0, x + dirx[0], y + diry[0], false) + 1,
              len(grid, 1, x + dirx[1], y + diry[1], false) + 1,
              len(grid, 2, x + dirx[2], y + diry[2], false) + 1,
              len(grid, 3, x + dirx[3], y + diry[3], false) + 1,
          });
        }
      }
    }

    return r;
  }

  // can move and turn
  int len(std::vector<std::vector<int>> &grid, int d, int x, int y, bool alt,
          bool t = false) {
    // std::cout << x << " " << y << " " << " " << alt << "snh\n";
    if (x < 0 || x >= w || y < 0 || y >= h || grid[x][y] != (alt ? 0 : 2))
      return 0;

    int sl = x * 16 + y * w * 16 + t * 8 + d * 2 + alt;
    // std::cout << memo[sl] << " memo\n";
    if (memo[sl] != -1)
      return memo[sl];

    // std::cout << x << " " << y << "s\n";

    int out = 1 + len(grid, d, x + dirx[d], y + diry[d], !alt, t);

    if (!t) {
      auto ndir = (d + 1) % 4;
      out = std::max(
          out, 1 + len(grid, ndir, x + dirx[ndir], y + diry[ndir], !alt, true));
    }

    memo[sl] = out;
    return out;
  }
};
