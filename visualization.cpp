#include "visualization.h"
#include "rpn.h"

#include <iostream>
#include <sstream>
#include <vector>
#include <string>

void list(vector<string> input) {
    vector<string> stack;

   for (string s : input) {
    if (!isOperator(s)) {
      stack.push_back(s);
    } else if (s == "<" || s == ">") {
      string temp = "(" + s + " " + stack.back() + " )";
      stack.pop_back();
      stack.push_back(temp);
    } else {
      string a = stack.back();
      stack.pop_back();
      string b = stack.back();
      stack.pop_back();
      string temp = "(" + s + " " + b + " " + a + " )";
      stack.push_back(temp);
    }
   }

    printOutput(stack.back());
}

void printOutput(string output) {
    int indent = 0;
    string non_space;
    istringstream iss(output);
    while (iss >> non_space) {
        if (non_space.find('(') != string::npos) {
            // string is of form parentheses operator
            // print indentation
            cout << string(indent, ' ');
            indent += 3;
        } else if (non_space == ")") {
            // decrease indentation
            indent -= 3;
            cout << string(indent, ' ');
        } else {
            // string is an operand, don't change indentation
            cout << string(indent, ' ');
        }
        cout << non_space << endl;
    }
}
