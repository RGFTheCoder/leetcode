#pragma GCC optimize("O3", "unroll-loops")
#pragma GCC option("arch=native", "tune=native")
#include <ios>
auto _ = std::ios::sync_with_stdio(false);

#include <vector>

class Solution {
public:
  std::vector<int> findDiagonalOrder(std::vector<std::vector<int>> &mat) {
    std::vector<int> out;
    int width = mat.size();
    int height = mat.front().size();

    for (int i = 0; i < width + height; i += 2) {
      // Do one iteration going SW
      for (int j = i; j >= 0; j--) {
        int x = j;
        int y = i - j;
        // Bounds check for easier looping
        if (x >= 0 && x < width && y >= 0 && y < height) {
          out.push_back(mat[x][y]);
        }
      }
      // And one going NE
      for (int j = i + 1; j >= 0; j--) {
        int y = j;
        int x = i + 1 - j;
        if (x >= 0 && x < width && y >= 0 && y < height) {
          out.push_back(mat[x][y]);
        }
      }
    }

    return out;
  }
};
