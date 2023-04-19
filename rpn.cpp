#include "rpn.h"

#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
  // prompt user for input
  string input;
  cout << "rpn> ";
  getline(cin, input);

  // parse given input by spaces
  vector<char> parsed = parse(input);
}

vector<char> parse(string input) {
  vector<char> parsed;
  for (char c : input) {
    if (c != ' ') parsed.push_back(c);
  }
  return parsed;
}
