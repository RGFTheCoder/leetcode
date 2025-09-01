#include <cstddef>
#include <iostream>
#pragma GCC optimize("O3", "unroll-loops")
#pragma GCC option("arch=native", "tune=native")
#include <ios>
auto _ = std::ios::sync_with_stdio(false);

#include <span>
#include <vector>

template <class T> struct Grid {
  std::vector<T> data;
  int height, width;

  Grid(std::vector<std::vector<T>> &nums) {
    height = nums.size();
    width = nums.front().size();

    data.reserve(width * height);
    for (size_t y = 0; y < height; y++) {
      for (size_t x = 0; x < width; x++) {
        data.push_back(nums[y][x]);
      }
    }
  }

  template <class J, class C>
  inline Grid(std::vector<std::vector<C>> &nums, J cb) {
    height = nums.size();
    width = nums.front().size();

    data.reserve(width * height);
    for (size_t y = 0; y < height; y++) {
      for (size_t x = 0; x < width; x++) {
        data.push_back(cb(nums[y][x]));
      }
    }
  }

  template <class J, class C> inline Grid(Grid<C> &nums, J cb) {
    width = nums.width;
    height = nums.height;

    data.reserve(nums.width * nums.height);
    for (size_t x = 0; x < nums.width * nums.height; x++) {
      data.push_back(cb(nums.data[x]));
    }
  }

  Grid() {}

  std::span<T> operator[](size_t y) {
    return std::span{data.begin() + y * width, static_cast<size_t>(width)};
  }
};

class Solution {
public:
  void solveSudoku(std::vector<std::vector<char>> &b) {
    Grid<int> board{b,
                    [](char og) { return og == '.' ? -1 : (int)(og - '1'); }};
    Grid<bool> board_og{board, [](int v) { return v == -1; }};

    int i = 0;
    while (!board_og.data[i])
      ++i;

    // std::cout << i << "test\n";
    while (i < 81 && i >= 0) {
      for (board.data[i] += 1; board.data[i] < 9; board.data[i]++) {
        // std::cout << board.data[i] << "chk\n";
        if (checkPos(board, i % 9, i / 9)) {
          // std::cout << "succ\n";
          do {
            ++i;
          } while (!board_og.data[i]);

          break;
        }
      }

      if (board.data[i] == 9) {
        board.data[i] = -1;
        do {
          --i;
        } while (i >= 0 && !board_og.data[i]);
      }
    }

    for (int y = 0; y < 9; y++) {
      for (int x = 0; x < 9; x++) {
        b[y][x] = '1' + board[y][x];
      }
    }
  }

  bool checkPos(Grid<int> &board, int y, int x) {
    bool has_number[9];

    for (int i = 0; i < 9; i++)
      has_number[i] = false;

    for (int column = 0; column < 9; column++) {
      if (board[y][column] != -1) {
        if (has_number[board[y][column]])
          return false;
        has_number[board[y][column]] = true;
      }
    }
    for (int i = 0; i < 9; i++)
      has_number[i] = false;

    for (int row = 0; row < 9; row++) {
      if (board[row][x] != -1) {
        if (has_number[board[row][x]])
          return false;
        has_number[board[row][x]] = true;
      }
    }
    for (int i = 0; i < 9; i++)
      has_number[i] = false;

    int outer_row = (y / 3) * 3;
    int outer_column = (x / 3) * 3;
    for (int k = 0; k < 9; k++) {
      int inner_row = k % 3;
      int inner_col = k / 3;
      if (board[outer_row + inner_row][outer_column + inner_col] != -1) {
        if (has_number[board[outer_row + inner_row][outer_column + inner_col]])
          return false;
        has_number[board[outer_row + inner_row][outer_column + inner_col]] =
            true;
      }
    }

    return true;
  }
};
