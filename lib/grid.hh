
#include <span>
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
