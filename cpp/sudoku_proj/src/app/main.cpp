#include <sudoku.hpp>

int main() {
  int grid[N][N] = {
      {0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 3, 0, 8, 5},
      {0, 0, 1, 0, 2, 0, 0, 0, 0},
      {0, 0, 0, 5, 0, 7, 0, 0, 0},
      {0, 0, 4, 0, 0, 0, 1, 0, 0},
      {0, 9, 0, 0, 0, 0, 0, 0, 0},
      {5, 0, 0, 0, 0, 0, 0, 7, 3},
      {0, 0, 2, 0, 1, 0, 0, 0, 0},
      {0, 0, 0, 0, 4, 0, 0, 0, 9}};
  if (SolveSudoku(grid) == true)
    printRes(grid);
  else
    std::cout << "No solution found" << std::endl;
  return 0;
}