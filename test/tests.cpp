#include "gtest/gtest.h"
#include "rpn.h"

TEST(Input, Parsing) {
  string input;
  vector<string> expected;
  vector<string> actual;

  input = "1 2 +";
  expected = {"1", "2", "+"};
  actual = parse(input);
  EXPECT_EQ(expected, actual);

  input = "          1       2        +  ";
  expected = {"1", "2", "+"};
  actual = parse(input);
  EXPECT_EQ(expected, actual);

  input = "10 + 3.58";
  expected = {"10", "+", "3.58"};
  actual = parse(input);
  EXPECT_EQ(expected, actual);

  input = "25*4+10";
  expected = {"25*4+10"};
  actual = parse(input);
  EXPECT_EQ(expected, actual);

  input = "(a + b)/c";
  expected = {"(a", "+", "b)/c"};
  actual = parse(input);
  EXPECT_EQ(expected, actual);
}

TEST(Calculations, Addition) {
  vector<string> input;
  double expected;
  double actual;

  input = {"1", "1", "+"};
  expected = 2;
  actual = rpn(input);
  EXPECT_EQ(expected, actual);

  input = {"2", "10", "3", "+", "5", "+", "+"};
  expected = 20;
  actual = rpn(input);
  EXPECT_EQ(expected, actual);

  input = {"-2", "-10", "-3", "+", "-5", "+", "+"};
  expected = -20;
  actual = rpn(input);
  EXPECT_EQ(expected, actual);

  input = {"10", "-5", "5", "+", "+", "-9", "+"};
  expected = 1;
  actual = rpn(input);
  EXPECT_EQ(expected, actual);

  input = {"3.456789", "5.324895", "+", "-6.712893", "+"};
  expected = 2.068791;
  actual = rpn(input);
  EXPECT_EQ(expected, actual);
}

TEST(Calculations, Subtraction) {
  vector<string> input;
  double expected;
  double actual;

  input = {"1", "1", "-"};
  expected = 0;
  actual = rpn(input);
  EXPECT_EQ(expected, actual);

  input = {"3", "10", "-", "0", "-"};
  expected = -7;
  actual = rpn(input);
  EXPECT_EQ(expected, actual);

  input = {"-8", "-3", "-4", "-", "-"};
  expected = -9;
  actual = rpn(input);
  EXPECT_EQ(expected, actual);

  input = {"-10", "3", "-", "24", "-", "-27", "-"};
  expected = -10;
  actual = rpn(input);
  EXPECT_EQ(expected, actual);

  input = {"5.000000", "-3.333334", "-10.234567", "-", "-"};
  expected = -1.901233;
  actual = rpn(input);
  EXPECT_NEAR(expected, actual, 4);
}

TEST(Calculations, Multiplication) {
  vector<string> input;
  double expected;
  double actual;

  input = {"1", "0", "*"};
  expected = 0;
  actual = rpn(input);
  EXPECT_EQ(expected, actual);

  input = {"-2", "-3", "*", "-1", "*"};
  expected = -6;
  actual = rpn(input);
  EXPECT_EQ(expected, actual);

  input = {"30.000000", "0.500000", "*", "3", "*", "-1", "*"};
  expected = -45;
  actual = rpn(input);
  EXPECT_EQ(expected, actual);

  input = {"-3.982093", "1", "*", "-2", "*"};
  expected = 7.964186;
  actual = rpn(input);
  EXPECT_EQ(expected, actual);

  input = {"-3.000000", "2000", "5.12", "*", "*", "-0.18", "*", "2.43", "*"};
  expected = 13436.928;
  actual = rpn(input);
  EXPECT_EQ(expected, actual);
}

TEST(Calculations, Division) {
  vector<string> input;
  double expected;
  double actual;

  input = {"100", "10", "/"};
  expected = 10;
  actual = rpn(input);
  EXPECT_EQ(expected, actual);

  input = {"6", "0.5", "/", "2", "/"};
  expected = 6;
  actual = rpn(input);
  EXPECT_EQ(expected, actual);

  input = {"-88", "-8", "/", "2", "/"};
  expected = 5.5;
  actual = rpn(input);
  EXPECT_EQ(expected, actual);

  input = {"1.500000", "0.300000", "-9", "/", "/"};
  expected = -45;
  actual = rpn(input);
  EXPECT_EQ(expected, actual);

  input = {"8.888999", "4.222222", "/", "1.234567", "/"};
  expected = 1.70529;
  actual = rpn(input);
  EXPECT_NEAR(expected, actual, 4);
}

TEST(Calculations, Floor) {
  EXPECT_EQ(21, rpn({"21.568", "<"}));
  EXPECT_EQ(-22, rpn({"-21.568", "<"}));
}

TEST(Calculations, Ceiling) {
  EXPECT_EQ(22, rpn({"21.568", ">"}));
  EXPECT_EQ(-21, rpn({"-21.568", ">"}));
}

TEST(Calculations, Exponentiation) {
  vector<string> input;
  double expected;
  double actual;

  input = {"2", "6", "**"};
  expected = 64;
  actual = rpn(input);
  EXPECT_EQ(expected, actual);

  input = {"2", "-3", "**"};
  expected = 0.125;
  actual = rpn(input);
  EXPECT_EQ(expected, actual);

  input = {"-3", "-4", "**"};
  expected = 0.012345679;
  actual = rpn(input);
  EXPECT_NEAR(expected, actual, 4);

  input = {"4", "3", "**", "0", "**"};
  expected = 1;
  actual = rpn(input);
  EXPECT_EQ(expected, actual);

  input = {"7", "-0", "**"};
  expected = 1;
  actual = rpn(input);
  EXPECT_EQ(expected, actual);

  input = {"-7", "-0", "**"};
  expected = 1;
  actual = rpn(input);
  EXPECT_EQ(expected, actual);

  input = {"-0.5", "4", "**"};
  expected = 0.0625;
  actual = rpn(input);
  EXPECT_EQ(expected, actual);

  input = {"0.5", "4", "**"};
  expected = 0.0625;
  actual = rpn(input);
  EXPECT_EQ(expected, actual);

  input = {"0.5", "-4", "**"};
  expected = 16;
  actual = rpn(input);
  EXPECT_EQ(expected, actual);
}

TEST(Calculations, MultipleOperators) {
  vector<string> input;
  double expected;
  double actual;

  input = {"-1.250000", "-6.666667", "+", "1.428571", "-6.666667", "*", "1.176471", "-", "<", "-4.000000", "**", "/", ">"};
  expected = -115907;
  actual = rpn(input);
  EXPECT_EQ(expected, actual);

  input = {"1.333333", "1.111111", ">", "/", "<", "1.052632", "1.052632", "-2.857143", "-1.538462", "*", "**", "-", "+"};
  expected = -0.200276;
  actual = rpn(input);
  EXPECT_NEAR(expected, actual, 4);
  
  input = {"1.250000", "1.000000", "1.428571", "1.428571", "+", "1.818182", "*", "/", "6.666667", "**", "-", "<", ">"};
  expected = 1;
  actual = rpn(input);
  EXPECT_EQ(expected, actual);

  input = {"20", "-10", "<", "5.000000", "-1.428571", "+", "-1.428571", "*", ">", "**", "/", "6.666667", "-"};
  expected = -2.00001e+06;
  actual = rpn(input);
  EXPECT_NEAR(expected, actual, 4);

  input = {"-1.428571", "<", "-5.000000", "2.222222", "*", "-1.000000", ">", "-", "/", "-6.666667", "+"};
  expected = -6.468865;
  actual = rpn(input);
  EXPECT_NEAR(expected, actual, 4);
}

TEST(InvalidInput, InsufficientOperands) {
  vector<string> input;
  string error_msg = "error: invalid postfix expression";

  input = {"-1.818182", "*", "1.538462", "+", "-1.818182", "-3.333333", "**", "-1.052632", ">", "-", "<", "/", "-1.428571"};
  EXPECT_EXIT(rpn(input), testing::ExitedWithCode(1), error_msg);

  input = {"-1.250000", ">", "2.000000", "-6.666667", "<", "-", "**", "+", "1.538462", "-2.500000", "1.111111", "*", "/"};
  EXPECT_EXIT(rpn(input), testing::ExitedWithCode(1), error_msg);

  input = {"-10.000000", "1.538462", "+", "/", "-", "6.666667", "1.000000", "-2.222222", "-3.333333", "*", "<", "**", ">"};
  EXPECT_EXIT(rpn(input), testing::ExitedWithCode(1), error_msg);

  input = {"10.000000", "**", "6.666667", "-1.538462", "/", ">", "-2.500000", "-", "-1.111111", "+", "*", "<", "-2.000000"};
  EXPECT_EXIT(rpn(input), testing::ExitedWithCode(1), error_msg);
}

TEST(InvalidInput, ExcessiveNumbers) {
  vector<string> input;
  string error_msg = "error: incomplete postfix expression, missing operators/operands";
  
  input = {"20", "-10", "<", "5.000000", "-1.428571", "+", "-1.428571", "*", ">", "**", "/", "6.666667", "-10.000000", "-"};
  EXPECT_EXIT(rpn(input), testing::ExitedWithCode(1), error_msg);
}

TEST(InvalidInput, DivisionByZero) {
  vector<string> input;
  string error_msg = "error: division by 0";

  input = {"2", "0", "/"};
  EXPECT_EXIT(rpn(input), testing::ExitedWithCode(1), error_msg);

  input = {"-6.2", "0", "/"};
  EXPECT_EXIT(rpn(input), testing::ExitedWithCode(1), error_msg);
}

TEST(InvalidInput, Exponentiation) {
  vector<string> input;

  input = {"-1.333333", "-1.111111", ">", "/", "<", "-1.052632", "-1.052632", "-2.857143", "-1.538462", "*", "**", "-", "+"};
  EXPECT_EXIT(rpn(input), testing::ExitedWithCode(1), "error: undefined, negative base and non-integer exponent");

  input = {"-3", "2.689", "**"};
  EXPECT_EXIT(rpn(input), testing::ExitedWithCode(1), "error: undefined, negative base and non-integer exponent");

  input = {"0", "0", "**"};
  EXPECT_EXIT(rpn(input), testing::ExitedWithCode(1), "error: undefined, base and exponent are both 0");
  
  input = {"0", "-7", "**"};
  EXPECT_EXIT(rpn(input), testing::ExitedWithCode(1), "error: undefined, base is 0 and exponent is negative");
}

TEST(InvalidInput, NonSupportedCharacters) {
  vector<string> input;
  string error_msg = "invalid input";

  input = {"x", "y", "z"};
  EXPECT_EXIT(rpn(input), testing::ExitedWithCode(1), error_msg);
  
  input = {"(", "-1", ")", "2", "**"};
  EXPECT_EXIT(rpn(input), testing::ExitedWithCode(1), error_msg);
}