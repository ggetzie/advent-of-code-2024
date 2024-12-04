#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

bool isSafe(vector<int> report) {
  // calculate the differences between the numbers

  int difference = report[1] - report[0];
  bool increasing = difference > 0;
  if (abs(difference) > 3 || abs(difference) == 0) {
    return false;
  }
  for (int i = 2; i < report.size(); i++) {
    difference = report[i] - report[i - 1];
    if (difference > 0 != increasing) {
      return false;
    }
    if (abs(difference) > 3 || abs(difference) == 0) {
      return false;
    }
  }
  return true;
}
void printReport(vector<int> report) {
  cout << "[";
  for (int num : report) {
    cout << num << " ";
  }
  cout << "]";
}
int main() {
  vector<int> report;
  int number;
  ifstream inputFile("input.txt");
  if (!inputFile) {
    cerr << "Could not open the file!" << endl;
    return 1;
  }
  int safeReports = 0;
  // each line of the input file contains one report
  // read a line and check if it is safe
  while (inputFile >> number) {
    report.push_back(number);
    if (inputFile.peek() == '\n') {
      // cout << "Report: ";
      // printReport(report);
      bool safe = isSafe(report);
      // cout << " is " << (safe ? "safe" : "unsafe") << endl;
      if (safe) {
        safeReports++;
      }
      report.clear();
    }
  }
  inputFile.close();
  cout << "Number of safe reports: " << safeReports << endl;
}