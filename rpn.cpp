#include "rpn.h"

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

int main() {
  // prompt user for input
  string input;
  cout << "rpn> ";
  getline(cin, input);

  // parse given input by spaces
  vector<string> parsed = parse(input);
}

vector<string> parse(string input) {
  vector<string> parsed;
  string non_space;
  istringstream iss(input);
  while (iss >> non_space) {
    parsed.push_back(non_space);
  }
  return parsed;
}
