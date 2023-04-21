#ifndef RPNCALCULATOR_RPN_H
#define RPNCALCULATOR_RPN_H

#include <string>
#include <vector>

using namespace std;

// function that splits input string by spaces into an array
vector<string> parse(string input);

// function that calculates result of input expression
double rpn(vector<string> input);

bool isOperator(string op);
bool isOperand(string op);

double operation(double a, double b, string op);

#endif // RPNCALCULATOR_RPN_H
