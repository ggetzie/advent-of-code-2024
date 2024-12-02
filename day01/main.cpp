#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

int main() {
  // read two columns of numbers from input.txt
  // open the file input.txt and read the numbers

  vector<int> loc1, loc2;
  int number;
  int total_distance = 0;
  ifstream inputFile("input.txt");
  if (!inputFile) {
    cerr << "Could not open the file!" << std::endl;
    return 1;
  }
  // split the line  on a space to get the two numbers
  while (inputFile >> number) {
    loc1.push_back(number);
    inputFile >> number;
    loc2.push_back(number);
  }
  inputFile.close();
  // sort the two vectors
  sort(loc1.begin(), loc1.end());
  sort(loc2.begin(), loc2.end());
  for (int i = 0; i < loc1.size(); i++) {
    total_distance += abs(loc1[i] - loc2[i]);
  }

  cout << "Total distance: " << total_distance << endl;

  return 0;
}