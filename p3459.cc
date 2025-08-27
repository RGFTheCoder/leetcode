#pragma GCC optimize("O3", "unroll-loops")
#pragma GCC option("arch=native", "tune=native")
#include <ios>
auto _ = std::ios::sync_with_stdio(false);

#include <algorithm>
#include <iostream>
#include <numeric>
#include <utility>
#include <vector>

inline std::pair<int, int> operator+(const std::pair<int, int> &lhs,
                                     const std::pair<int, int> &rhs) {
  return {lhs.first + rhs.first, lhs.second + rhs.second};
}

struct Grid {
  int width;
  int height;

  std::vector<int> data;

  Grid() {};

  Grid(const std::vector<std::vector<int>> &grid)
      : width(grid.size()), height(grid.front().size()) {
    data.reserve(width * height);

    data =
        std::accumulate(grid.begin(), grid.end(), data,
                        [](std::vector<int> acc, const std::vector<int> &vec) {
                          acc.insert(acc.end(), vec.begin(), vec.end());
                          return acc;
                        });
  }

  int operator[](std::pair<int, int> pos) const {
    return data[pos.first * height + pos.second];
  }
};

class Solution {
  constexpr static std::pair<int, int> direction_lookup[]{
      {1, -1}, {-1, -1}, {-1, 1}, {1, 1}};

  std::vector<int> memoization_table;
  Grid grid;

public:
  int lenOfVDiagonal(std::vector<std::vector<int>> &grid_nested) {
    grid = Grid(grid_nested);

    memoization_table.assign(grid.width * grid.height * 16, -1);

    int r = 0;

    for (int x = 0; x < grid.width; x++) {
      for (int y = 0; y < grid.height; y++) {
        std::pair<int, int> pos{x, y};
        if (grid[pos] == 1) {

          r = std::max({
              r,
              recursive_pather(0, pos + direction_lookup[0], false) + 1,
              recursive_pather(1, pos + direction_lookup[1], false) + 1,
              recursive_pather(2, pos + direction_lookup[2], false) + 1,
              recursive_pather(3, pos + direction_lookup[3], false) + 1,
          });
        }
      }
    }

    return r;
  }

  // can move and turn
  int recursive_pather(int direction, std::pair<int, int> position,
                       bool alternating_state, bool has_turned = false) {
    // Check bounds before memo since memo is flat vec
    if (position.first < 0 || position.first >= grid.width ||
        position.second < 0 || position.second >= grid.height ||
        grid[position] != (alternating_state ? 0 : 2))
      return 0;

    // Memo table uses lower 2^4=16 bits for non-pos state:
    // 0 - alternate state
    // 1,2 - direction
    // 3 - turned
    int memoization_index = position.first * 16 +
                            position.second * grid.width * 16 + has_turned * 8 +
                            direction * 2 + alternating_state;
    if (memoization_table[memoization_index] != -1)
      return memoization_table[memoization_index];

    int out =
        1 + recursive_pather(direction, position + direction_lookup[direction],
                             !alternating_state, has_turned);

    if (!has_turned) {
      auto new_direction = (direction + 1) % 4;
      out = std::max(
          out, 1 + recursive_pather(new_direction,
                                    position + direction_lookup[new_direction],
                                    !alternating_state, true));
    }

    memoization_table[memoization_index] = out;
    return out;
  }
};
