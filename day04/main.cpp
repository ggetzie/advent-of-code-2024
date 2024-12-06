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

int main(int argc, char* argv[]) {
  if (argc != 2) {
    cerr << "Usage: " << argv[0] << " <input file>" << endl;
    return 1;
  }
  ifstream inputFile(argv[1]);
  if (!inputFile) {
    cerr << "Error opening file" << endl;
    return 1;
  }
  Grid letterGrid;
  char next_c;
  string line;
  while (getline(inputFile, line)) {
    vector<char> row(line.begin(), line.end());
    letterGrid.push_back(row);
  }

  int xmasCount = 0;
  for (int i = 0; i < letterGrid.size(); i++) {
    for (int j = 0; j < letterGrid[0].size(); j++) {
      xmasCount += (checkN(letterGrid, i, j) + checkNW(letterGrid, i, j) +
                    checkW(letterGrid, i, j) + checkSW(letterGrid, i, j) +
                    checkS(letterGrid, i, j) + checkSE(letterGrid, i, j) +
                    checkE(letterGrid, i, j) + checkNE(letterGrid, i, j));
    }
  }

  cout << "XMAS count: " << xmasCount << endl;

  return 0;
}