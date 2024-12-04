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

bool dampenedSafe(vector<int> report) {
  bool safe = isSafe(report);
  if (safe) {
    return true;
  }
  // check if the report is safe with each number removed
  for (int i = 0; i < report.size(); i++) {
    vector<int> dampenedReport;
    for (int j = 0; j < report.size(); j++) {
      if (j != i) {
        dampenedReport.push_back(report[j]);
      }
    }
    if (isSafe(dampenedReport)) {
      return true;
    }
  }
  return false;
}

void printReport(vector<int> report) {
  cout << "[";
  for (int num : report) {
    cout << num;
    if (num != report.back()) {
      cout << ", ";
    }
  }
  cout << "]";
}
int main(int argc, char **argv) {
  // get filename from args
  if (argc != 2) {
    cerr << "Usage: " << argv[0] << " <filename>" << endl;
    return 1;
  }

  vector<int> report;
  int number;
  ifstream inputFile(argv[1]);
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
      bool safe = dampenedSafe(report);
      if (safe) {
        safeReports++;
      }
      report.clear();
    }
  }
  inputFile.close();
  cout << "Number of safe reports: " << safeReports << endl;
}