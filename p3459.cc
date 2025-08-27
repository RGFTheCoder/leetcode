#include <ios>
#include <utility>
#pragma GCC optimize("O3", "unroll-loops")

#include <algorithm>
#include <iostream>
#include <vector>

inline std::pair<int, int> operator+(const std::pair<int, int> &lhs,
                                     const std::pair<int, int> &rhs) {
  return {lhs.first + rhs.first, lhs.second + rhs.second};
}

class Solution {
  constexpr static std::pair<int, int> direction_lookup[]{
      {1, -1}, {-1, -1}, {-1, 1}, {1, 1}};

  int grid_width;
  int grid_height;

  std::vector<int> memoization_table;

public:
  int lenOfVDiagonal(std::vector<std::vector<int>> &grid) {

    // Decouple stdio from iostreams.
    // Faster, but race condition occurs if you use both.
    std::ios::sync_with_stdio(false);

    grid_width = grid.size();
    grid_height = grid[0].size();

    memoization_table.assign(grid_width * grid_height * 16, -1);

    int r = 0;

    for (int x = 0; x < grid_width; x++) {
      for (int y = 0; y < grid_height; y++) {
        if (grid[x][y] == 1) {
          std::pair<int, int> pos{x, y};

          r = std::max({
              r,
              recursive_pather(grid, 0, pos + direction_lookup[0], false) + 1,
              recursive_pather(grid, 1, pos + direction_lookup[1], false) + 1,
              recursive_pather(grid, 2, pos + direction_lookup[2], false) + 1,
              recursive_pather(grid, 3, pos + direction_lookup[3], false) + 1,
          });
        }
      }
    }

    return r;
  }

  // can move and turn
  int recursive_pather(std::vector<std::vector<int>> &grid, int direction,
                       std::pair<int, int> position, bool alternating_state,
                       bool has_turned = false) {
    // Check bounds before memo since memo is flat vec
    if (position.first < 0 || position.first >= grid_width ||
        position.second < 0 || position.second >= grid_height ||
        grid[position.first][position.second] != (alternating_state ? 0 : 2))
      return 0;

    // Memo table uses lower 2^4=16 bits for non-pos state:
    // 0 - alternate state
    // 1,2 - direction
    // 3 - turned
    int memoization_index = position.first * 16 +
                            position.second * grid_width * 16 + has_turned * 8 +
                            direction * 2 + alternating_state;
    if (memoization_table[memoization_index] != -1)
      return memoization_table[memoization_index];

    int out = 1 + recursive_pather(grid, direction,
                                   position + direction_lookup[direction],
                                   !alternating_state, has_turned);

    if (!has_turned) {
      auto new_direction = (direction + 1) % 4;
      out = std::max(
          out, 1 + recursive_pather(grid, new_direction,
                                    position + direction_lookup[new_direction],
                                    !alternating_state, true));
    }

    memoization_table[memoization_index] = out;
    return out;
  }
};
