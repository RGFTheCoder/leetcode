#pragma GCC optimize("O3", "unroll-loops")
#pragma GCC option("arch=native", "tune=native")
#include <ios>
auto _ = std::ios::sync_with_stdio(false);

#include <algorithm>
#include <cstddef>
#include <iostream>
#include <vector>

struct DiagonalIter {
  std::vector<std::vector<int>> &grid;
  int width, height;

  struct Iterator {
    DiagonalIter *grid;
    int current_row, current_column;

    // Required typedefs
    typedef std::random_access_iterator_tag iterator_category;
    typedef int value_type;
    typedef ptrdiff_t difference_type;
    typedef int *pointer;
    typedef int &reference;

    // Constructor
    Iterator(DiagonalIter &grid, int initial_row = 0, int initial_column = 0)
        : grid(&grid), current_row(initial_row),
          current_column(initial_column) {}

    Iterator(const Iterator &original)
        : grid(original.grid), current_column(original.current_column),
          current_row(original.current_row) {}

    // Basic operations (input iterator)
    reference operator*() const {
      return grid->grid[current_row][current_column];
    }
    pointer operator->() const {
      return &grid->grid[current_row][current_column];
    }
    Iterator &operator++() {
      if (current_column < grid->width && current_row < grid->height) {
        current_row++;
        current_column++;
      }

      return *this;
    }
    Iterator operator++(int) {
      auto tmp = *this;
      ++*this;
      return tmp;
    }

    // Bidirectional operations
    Iterator &operator--() {
      if (current_row > 0 && current_column > 0) {
        current_column--;
        current_row--;
      }
      return *this;
    }
    Iterator operator--(int) {
      auto tmp = *this;
      --*this;
      return tmp;
    }

    // Random access operations
    Iterator &operator+=(difference_type n) {
      current_row += n;
      current_column += n;

      while (current_column > grid->width && current_row > grid->height) {
        current_row--;
        current_column--;
      }
      return *this;
    }
    Iterator operator+(difference_type n) const {
      auto copy = *this;
      copy += n;
      return copy;
    }
    Iterator &operator-=(difference_type n) {
      *this += -n;
      return *this;
    }
    Iterator operator-(difference_type n) const {
      auto copy = *this;
      copy -= n;
      return copy;
    }

    difference_type operator-(const Iterator &other) const {
      return current_row - other.current_row;
    }

    reference operator[](difference_type n) const { return *(*this + n); }

    bool operator<(const Iterator &other) const {
      return current_column < other.current_column;
    }
    bool operator>(const Iterator &other) const {
      return current_column > other.current_column;
    }
    bool operator<=(const Iterator &other) const {
      return current_column <= other.current_column;
    }
    bool operator>=(const Iterator &other) const {
      return current_column >= other.current_column;
    }

    bool operator==(const Iterator &other) const {

      return (current_column == other.current_column) ||
             (is_oob() && other.is_oob());
    }
    bool operator!=(const Iterator &other) const {
      return (current_column != other.current_column) &&
             !(is_oob() && other.is_oob());
    }

    bool is_oob() const {
      return current_column >= grid->width || (current_row >= grid->height);
    }
  };

  DiagonalIter(std::vector<std::vector<int>> &grid)
      : grid(grid), height(grid.front().size()), width(grid.size()) {}

  // This goes from 0-positive for top tri,
  // negative-0 for bottom
  int origin = 0;

  Iterator begin() {
    return Iterator(*this, origin < 0 ? -origin : 0, origin > 0 ? origin : 0);
  }
  Iterator end() {
    return Iterator(*this,
                    origin < 0 ? height : height - (origin > 0 ? origin : 0),
                    origin > 0 ? width : width - (origin < 0 ? -origin : 0));
  }
};

class Solution {
public:
  std::vector<std::vector<int>>
  sortMatrix(std::vector<std::vector<int>> &grid) {

    DiagonalIter diag{grid};

    for (diag.origin = -diag.height + 1; diag.origin <= 0; diag.origin++) {
      std::sort(diag.begin(), diag.end(), [](int a, int b) { return a > b; });
    }
    for (diag.origin = 1; diag.origin <= diag.width; diag.origin++) {
      std::sort(diag.begin(), diag.end(), [](int a, int b) { return a < b; });
    }

    return grid;
  }
};
