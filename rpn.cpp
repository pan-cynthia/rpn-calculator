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

  // calculate result
  double result = rpn(parsed);
  cout << result << endl;
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

double rpn(vector<string> input) {
  // stack will store operands for use when an operator is encountered
  vector<double> stack;

  for (string s : input) {
    if (isOperator(s)) {
      // check that there are at least two operands on the stack
      if (stack.size() < 2) {
        cout << "error: invalid postfix expression" << endl;
        exit(1);
      }
      // pop two operands off of the stack
      double a = stack.back();
      stack.pop_back();
      double b = stack.back();
      stack.pop_back();

      // perform operation and push result back onto stack
      stack.push_back(operation(a, b, s));
    } else if (isOperand(s)) {
      // element is an operand, push it onto the stack
      stack.push_back(stod(s));
    } else {
      cout << "invalid input" << endl;
      exit(1);
    }
  }

  if (stack.size() > 1) {
    cout << "error: incomplete postfix expression, missing operators/operands" << endl;
    exit(1);
  }

  return stack.back();
}

bool isOperator(string op) {
  return op == "+" || op == "-" || op == "*" || op == "/";
}

bool isOperand(string op) {
  for (int i = 0; i < op.length(); ++i) {
    // check if operand is a digit (0-9), a decimal symbol, or a negative symbol
    if (!isdigit(op[i]) && op[i] != '.' && op[i] != '-') return false;
  }
  return true;
}

double operation(double a, double b, string op) {
  if (op == "+") {
    return b + a;
  } else if (op == "-") { 
    return b - a;
  } else if (op == "*") {
    return b * a;
  } else if (op == "/") {
    if (a == 0) {
      cout << "error: division by 0" << endl;
      exit(1);
    }
    return b / a;
  }
  return -1;
}
