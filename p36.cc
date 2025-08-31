#include <span>
#pragma GCC optimize("O3", "unroll-loops")
#pragma GCC option("arch=native", "tune=native")
#include <ios>
auto _ = std::ios::sync_with_stdio(false);

#include <cstddef>
#include <vector>

template <class T> struct Grid {
  std::vector<T> data;
  int height, width;

  Grid(std::vector<std::vector<T>> &nums) {
    height = nums.size();
    width = nums.front().size();

    nums.reserve(width * height);
    for (size_t y = 0; y < height; y++) {
      for (size_t x = 0; x < width; x++) {
        data.push_back(nums[y][x]);
      }
    }
  }

  std::span<T> operator[](size_t y) {
    return std::span{data.begin() + y * 9, 9};
  }
};

class Solution {
public:
  bool isValidSudoku(std::vector<std::vector<char>> &b) {
    Grid<char> board{b};
    bool has_number[9];

    for (int i = 0; i < 9; i++)
      has_number[i] = false;

    for (int row = 0; row < 9; row++) {
      for (int column = 0; column < 9; column++) {
        if (board[row][column] != '.') {
          if (has_number[board[row][column] - '1'])
            return false;
          has_number[board[row][column] - '1'] = true;
        }
      }
      for (int i = 0; i < 9; i++)
        has_number[i] = false;
    }

    for (int column = 0; column < 9; column++) {
      for (int row = 0; row < 9; row++) {
        if (board[row][column] != '.') {
          if (has_number[board[row][column] - '1'])
            return false;
          has_number[board[row][column] - '1'] = true;
        }
      }
      for (int i = 0; i < 9; i++)
        has_number[i] = false;
    }

    for (int outer_square = 0; outer_square < 9; outer_square++) {
      int outer_row = (outer_square % 3) * 3;
      int outer_column = (outer_square / 3) * 3;
      for (int k = 0; k < 9; k++) {
        int inner_row = k % 3;
        int inner_col = k / 3;
        if (board[outer_row + inner_row][outer_column + inner_col] != '.') {
          if (has_number[board[outer_row + inner_row]
                              [outer_column + inner_col] -
                         '1'])
            return false;
          has_number[board[outer_row + inner_row][outer_column + inner_col] -
                     '1'] = true;
        }
      }
      for (int i = 0; i < 9; i++)
        has_number[i] = false;
    }

    return true;
  }
};
