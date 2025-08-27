#pragma GCC optimize("O3", "unroll-loops")
#pragma GCC option("arch=native", "tune=native")
#include <ios>
auto _ = std::ios::sync_with_stdio(false);

class Solution {
public:
  std::string decodeCiphertext(std::string encodedText, int rows) {
    long columns = encodedText.size() / rows;

    std::string out{};

    long encoded_size = rows * columns;

    long lim = rows == 1 ? columns * 2 : columns * (rows);

    // cutoff logic, works by overflowing and wrapping
    // the index for the cipher string repeatedly.
    for (long i = 0; i != lim; i += columns + 1) {
      if (i > encoded_size)
        i -= (columns * rows) + rows - 1;

      if (i < encoded_size)
        out += encodedText[i % encoded_size];
    }

    out.erase(out.find_last_not_of(" ") + 1);

    return out;
  }
};
