#include <sudoku.hpp>

bool isGridSafe(int grid[N][N], int row, int col, int num) {
  return !isUsedinRow(grid, row, num) && !isUsedinCol(grid, col, num) &&
      !isUsedinBox(grid, row - row % 3, col - col % 3, num);
}

bool isEmptyLocation(int grid[N][N], int& row, int& col) {
  for (row = 0; row < N; row++)
    for (col = 0; col < N; col++)
      if (grid[row][col] == EMPTY)
        return true;
  return false;
}

bool SolveSudoku(int grid[N][N]) {
  int row, col;
  if (!isEmptyLocation(grid, row, col)) {
    return true;
  }
  for (int i = 1; i <= N; i++) {
    if (isGridSafe(grid, row, col, i)) {
      grid[row][col] = i;
      if (SolveSudoku(grid)) {
        return true;
      }
      grid[row][col] = EMPTY;
    }
  }
}

bool isUsedinRow(int grid[N][N], int prow, int num) {
  for (int col = 0; col < N; col++)
    if (grid[prow][col] == num)
      return true;
  return false;
}

bool isUsedinCol(int grid[N][N], int pcol, int num) {
  for (int row = 0; row < N; row++)
    if (grid[row][pcol] == num)
      return true;
    else
      return false;
}

bool isUsedinBox(int grid[N][N], int BeginRow, int BeginCol, int num) {
  bool tf = false;
  for (int row = 0; row < 3; row++)
    for (int col = 0; col < 3; col++)
      if (grid[row + BeginRow][col + BeginCol] == num)
        tf = true;
  return tf;
}
void printRes(int finalgrid[N][N]) {
  for (int row = 0; row < N; row++) {
    for (int col = 0; col < N; col++)
      std::cout << finalgrid[row][col] << "  ";
    std::cout << std::endl;
  }
}