#pragma once

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>

#define EMPTY 0
#define N 9

bool isGridSafe(int grid[N][N], int row, int col, int num);
bool isEmptyLocation(int grid[N][N], int& row, int& col);
bool SolveSudoku(int grid[N][N]);
bool isUsedinRow(int grid[N][N], int prow, int num);
bool isUsedinCol(int grid[N][N], int pcol, int num);
bool isUsedinBox(int grid[N][N], int BeginRow, int BeginCol, int num);
void printRes(int finalgrid[N][N]);