#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

typedef vector<vector<char>> Grid;

void printGrid(const Grid& grid) {
  for (const auto& row : grid) {
    for (int i = 0; i < row.size(); i++) {
      cout << row[i];
    }
    cout << endl;
  }
}

int checkN(const Grid& grid, int row, int col) {
  // check if we can spell XMAS going up from row, col
  if (row - 3 < 0) {
    return 0;
  }
  for (int i = 0; i < 4; i++) {
    if (grid[row - i][col] != "XMAS"[i]) {
      return 0;
    }
  }
  return 1;
}

int checkNW(const Grid& grid, int row, int col) {
  // check if we can spell XMAS going up and to the left from row, col
  if (row - 3 < 0 || col - 3 < 0) {
    return 0;
  }
  for (int i = 0; i < 4; i++) {
    if (grid[row - i][col - i] != "XMAS"[i]) {
      return 0;
    }
  }
  return 1;
}

int checkW(const Grid& grid, int row, int col) {
  // check if we can spell XMAS going to the left from row, col
  if (col - 3 < 0) {
    return 0;
  }
  for (int i = 0; i < 4; i++) {
    if (grid[row][col - i] != "XMAS"[i]) {
      return 0;
    }
  }
  return 1;
}

int checkSW(const Grid& grid, int row, int col) {
  // check if we can spell XMAS going down and to the left from row, col
  if (row + 3 >= grid.size() || col - 3 < 0) {
    return 0;
  }
  for (int i = 0; i < 4; i++) {
    if (grid[row + i][col - i] != "XMAS"[i]) {
      return 0;
    }
  }
  return 1;
}

int checkS(const Grid& grid, int row, int col) {
  // check if we can spell XMAS going down from row, col
  if (row + 3 >= grid.size()) {
    return 0;
  }
  for (int i = 0; i < 4; i++) {
    if (grid[row + i][col] != "XMAS"[i]) {
      return 0;
    }
  }
  return 1;
}

int checkSE(const Grid& grid, int row, int col) {
  // check if we can spell XMAS going down and to the right from row, col
  if (row + 3 >= grid.size() || col + 3 >= grid[0].size()) {
    return 0;
  }
  for (int i = 0; i < 4; i++) {
    if (grid[row + i][col + i] != "XMAS"[i]) {
      return 0;
    }
  }
  return 1;
}

int checkE(const Grid& grid, int row, int col) {
  // check if we can spell XMAS going to the right from row, col
  if (col + 3 >= grid[0].size()) {
    return 0;
  }
  for (int i = 0; i < 4; i++) {
    if (grid[row][col + i] != "XMAS"[i]) {
      return 0;
    }
  }
  return 1;
}

int checkNE(const Grid& grid, int row, int col) {
  // check if we can spell XMAS going up and to the right from row, col
  if (row - 3 < 0 || col + 3 >= grid[0].size()) {
    return 0;
  }
  for (int i = 0; i < 4; i++) {
    if (grid[row - i][col + i] != "XMAS"[i]) {
      return 0;
    }
  }
  return 1;
}

int countXmas(const Grid& grid) {
  int xmasCount = 0;
  for (int i = 0; i < grid.size(); i++) {
    for (int j = 0; j < grid[0].size(); j++) {
      xmasCount +=
          (checkN(grid, i, j) + checkNW(grid, i, j) + checkW(grid, i, j) +
           checkSW(grid, i, j) + checkS(grid, i, j) + checkSE(grid, i, j) +
           checkE(grid, i, j) + checkNE(grid, i, j));
    }
  }
  return xmasCount;
}

int checkX_Mas(const Grid& grid, int row, int col) {
  // check if there is M A S in an X form going right and down from row, col
  // can also be reversed so
  // M M       S S     M S     S M
  //  A   and   A  and  A  and  A   are all valid
  // S S       M M     M S     S M
  if (row + 2 >= grid.size() || col + 2 >= grid[0].size()) {
    return 0;
  }

  char middle = grid[row + 1][col + 1];
  if (middle != 'A') {
    return 0;
  }
  char topLeft = grid[row][col];
  char topRight = grid[row][col + 2];
  char bottomLeft = grid[row + 2][col];
  char bottomRight = grid[row + 2][col + 2];

  bool upright = topLeft == 'M' && topRight == 'M' && bottomLeft == 'S' &&
                 bottomRight == 'S';
  bool flipped = topLeft == 'S' && topRight == 'S' && bottomLeft == 'M' &&
                 bottomRight == 'M';
  bool left = topLeft == 'M' && bottomLeft == 'M' && topRight == 'S' &&
              bottomRight == 'S';
  bool right = topLeft == 'S' && bottomLeft == 'S' && topRight == 'M' &&
               bottomRight == 'M';
  return int(upright || flipped || left || right);
}

int countX_Mas(const Grid& grid) {
  int X_MasCount = 0;
  for (int i = 0; i < grid.size(); i++) {
    for (int j = 0; j < grid[0].size(); j++) {
      X_MasCount += checkX_Mas(grid, i, j);
    }
  }
  return X_MasCount;
}

int main(int argc, char* argv[]) {
  if (argc != 2) {
    cerr << "Usage: " << argv[0] << " <input file>" << endl;
    return 1;
  }
  ifstream inputFile(argv[1]);
  if (!inputFile.is_open()) {
    cerr << "Error opening file: " << argv[1] << endl;
    return 1;
  }
  Grid letterGrid;
  char next_c;
  string line;
  while (getline(inputFile, line)) {
    vector<char> row(line.begin(), line.end());
    letterGrid.push_back(row);
  }

  int xmasCount = countXmas(letterGrid);
  int X_MasCount = countX_Mas(letterGrid);

  cout << "XMAS count: " << xmasCount << endl;
  cout << "X_Mas count: " << X_MasCount << endl;

  return 0;
}