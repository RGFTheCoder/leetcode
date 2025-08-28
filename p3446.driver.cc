#include "p3446.cc"
#include <iostream>
#include <vector>

int main() {
  Solution sol;

  std::vector<std::vector<int>> v = {
      {1, 7, 3}, //
      {9, 8, 2}, //
      {4, 5, 6}  //
  };
  sol.sortMatrix(v);

  for (auto &l : v) {
    for (auto &i : l)
      std::cout << i << " ";
    std::cout << "\n";
  }
}
