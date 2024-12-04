#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <vector>
using namespace std;

int main() {
  vector<int> loc1, loc2;
  map<int, int> loc2Counts;
  int number;
  int totalDistance = 0;
  int similarity = 0;
  ifstream inputFile("input.txt");
  if (!inputFile) {
    cerr << "Could not open the file!" << endl;
    return 1;
  }
  while (inputFile >> number) {
    loc1.push_back(number);
    inputFile >> number;
    loc2.push_back(number);
    loc2Counts[number]++;
  }
  inputFile.close();
  sort(loc1.begin(), loc1.end());
  sort(loc2.begin(), loc2.end());
  for (int i = 0; i < loc1.size(); i++) {
    totalDistance += abs(loc1[i] - loc2[i]);
    similarity += loc2Counts[loc1[i]] * loc1[i];
  }
  cout << "Total distance: " << totalDistance << endl;
  cout << "Similarity: " << similarity << endl;
  return 0;
}