
#include <vector>
struct TopTri {
  std::vector<std::vector<int>> &grid;
  int width, height;

  struct Iterator {
    TopTri *grid;
    int current_row = 0, current_column = 1;

    // Required typedefs
    typedef std::random_access_iterator_tag iterator_category;
    typedef int value_type;
    typedef ptrdiff_t difference_type;
    typedef int *pointer;
    typedef int &reference;

    // Constructor
    Iterator(TopTri &grid, int initial_row = 0, int initial_column = 1)
        : grid(&grid), current_row(initial_row),
          current_column(initial_column) {}

    Iterator(const Iterator &original)
        : grid(original.grid), current_column(original.current_column),
          current_row(original.current_row) {}

    // Basic operations (input iterator)
    reference operator*() const {
      return grid->grid[current_row][current_column + current_row];
    }
    pointer operator->() const {
      return &grid->grid[current_row][current_column + current_row];
    }
    Iterator &operator++() {
      current_row++;

      if (current_column + current_row >= grid->width) {
        current_row = 0;
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
      current_row--;
      if (current_row < 0) {
        current_column--;
        current_row = grid->width - current_column - 1;
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

      while (current_column + current_row >= grid->width) {
        current_row -= grid->height - current_column - 1;
        current_column++;
      }

      while (current_row < 0) {
        current_row += grid->height - current_column + 1;
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

    size_t index() const {
      int row = current_row, column = current_column;

      while (column > 0) {
        row += grid->height - column + 1;
        column--;
      }

      return row;
    }

    difference_type operator-(const Iterator &other) const {
      return index() - other.index();
    }

    reference operator[](difference_type n) const { return *(*this + n); }

    bool operator<(const Iterator &other) const {
      return current_column < other.current_column ||
             (current_column == other.current_column &&
              current_row < other.current_row);
    }
    bool operator>(const Iterator &other) const {
      return current_column > other.current_column ||
             (current_column == other.current_column &&
              current_row > other.current_row);
    }
    bool operator<=(const Iterator &other) const {
      return current_column < other.current_column ||
             (current_column == other.current_column &&
              current_row <= other.current_row);
    }
    bool operator>=(const Iterator &other) const {
      return current_column > other.current_column ||
             (current_column == other.current_column &&
              current_row >= other.current_row);
    }

    bool operator==(const Iterator &other) const {

      return (current_column == other.current_column &&
              current_row == other.current_row) ||
             (is_oob() && other.is_oob());
    }
    bool operator!=(const Iterator &other) const {
      return (current_column != other.current_column ||
              current_row != other.current_row) &&
             !(is_oob() && other.is_oob());
    }

    bool is_oob() const {
      return current_column >= grid->width ||
             (current_column == grid->width - 1 && current_row > 0);
    }
  };

  TopTri(std::vector<std::vector<int>> &grid)
      : grid(grid), height(grid.size()), width(grid.front().size()) {}

  Iterator begin() { return Iterator(*this, 0, 1); }
  Iterator end() { return Iterator(*this, 0, width); }
};

struct DiagonalIter {
  std::vector<std::vector<int>> &grid;
  int width, height;

  struct Iterator {
    DiagonalIter *grid;
    int current_row = 0, current_column = 1;

    // Required typedefs
    typedef std::random_access_iterator_tag iterator_category;
    typedef int value_type;
    typedef ptrdiff_t difference_type;
    typedef int *pointer;
    typedef int &reference;

    // Constructor
    Iterator(DiagonalIter &grid, int initial_row = 0, int initial_column = 1)
        : grid(&grid), current_row(initial_row),
          current_column(initial_column) {}

    Iterator(const Iterator &original)
        : grid(original.grid), current_column(original.current_column),
          current_row(original.current_row) {}

    // Basic operations (input iterator)
    reference operator*() const {
      return grid->grid[current_column + current_row][current_row];
    }
    pointer operator->() const {
      return &grid->grid[current_column + current_row][current_row];
    }
    Iterator &operator++() {
      current_row++;

      if (current_column + current_row >= grid->width) {
        current_row = 0;
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
      current_row--;
      if (current_row < 0) {
        current_column--;
        current_row = grid->width - current_column - 1;
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

      while (current_column + current_row >= grid->width) {
        current_row -= grid->height - current_column - 1;
        current_column++;
      }

      while (current_row <= 0) {
        current_row += grid->height - current_column + 1;
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

    size_t index() const {
      int row = current_row, column = current_column;

      while (column > 0) {
        row += grid->height - column + 1;
        column--;
      }

      return row;
    }

    difference_type operator-(const Iterator &other) const {
      return index() - other.index();
    }

    reference operator[](difference_type n) const { return *(*this + n); }

    bool operator<(const Iterator &other) const {
      return current_column < other.current_column ||
             (current_column == other.current_column &&
              current_row < other.current_row);
    }
    bool operator>(const Iterator &other) const {
      return current_column > other.current_column ||
             (current_column == other.current_column &&
              current_row > other.current_row);
    }
    bool operator<=(const Iterator &other) const {
      return current_column < other.current_column ||
             (current_column == other.current_column &&
              current_row <= other.current_row);
    }
    bool operator>=(const Iterator &other) const {
      return current_column > other.current_column ||
             (current_column == other.current_column &&
              current_row >= other.current_row);
    }

    bool operator==(const Iterator &other) const {

      return (current_column == other.current_column &&
              current_row == other.current_row) ||
             (is_oob() && other.is_oob());
    }
    bool operator!=(const Iterator &other) const {
      return (current_column != other.current_column ||
              current_row != other.current_row) &&
             !(is_oob() && other.is_oob());
    }

    bool is_oob() const {
      return current_column >= grid->width ||
             (current_column == grid->width - 1 && current_row > 0);
    }
  };

  DiagonalIter(std::vector<std::vector<int>> &grid)
      : grid(grid), height(grid.front().size()), width(grid.size()) {}

  Iterator begin() { return Iterator(*this, 0, 0); }
  Iterator end() { return Iterator(*this, 0, width); }
};
