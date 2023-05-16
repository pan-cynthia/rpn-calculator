# Reverse Polish Notation Calculator

[Reverse Polish notation (RPN)](https://en.wikipedia.org/wiki/Reverse_Polish_notation), also known as postfix notation, is a mathematical notation in which operators follow their operands. For example, to add 1 and 2 together, the expression is formatted as `1 2 +` rather than `1 + 2`.

## Usage

The program can be run with either no arguments or a single argument; anything else is an error.

### Regular Mode

Regular mode will only display the result of the expression provided.

To run regular mode (from the root directory), use the following command:

```
build/src/rpn
```

### List Mode

In addition to displaying the result of the expression, list mode will also display a list of the input values in the following format: `(operator operand1 operand2)`, where each operand is indented one level more than its operator and matching parentheses are indented at the same level.

In list mode, the result is printed first with the list of input values following.

To run list mode (from the root directory), use the following command:

```
build/src/rpn -l
```

### After Running

After running either mode, a prompt for user input will appear.

```
rpn>
```

At this point, you can start inputting your expression.

This program only accepts numeric characters from `0-9`, the operator characters (`+`, `-`, `*`, `/`, `**`, `<`, `>`), and spaces as valid input. Characters such as parentheses, alphabetic characters, and other special characters are not supported.

The inputted expression must be formatted with a space between every operand and operator entered. For example, `1+1` should be inputted as `1 + 1`. Note that the amount of spaces does not actually matter so long as a space is there.

### Examples

Regular Mode
```
rpn> 2 12 6 - / 5 3 + *
2.66667
```

```
rpn> 1.250000 1.000000 1.428571 1.428571 + 1.818182 * / 6.666667 ** - < >
1
```

List Mode
```
rpn> 1 1 +
2
(+
   1
   1
)
```

```
rpn> 1.250000 1.000000 1.428571 1.428571 + 1.818182 * / 6.666667 ** - < >
1
(>
   (<
      (-
         1.250000
         (**
            (/
               1.000000
               (*
                  (+
                     1.428571
                     1.428571
                  )
                  1.818182
               )
            )
            6.666667
         )
      )
   )
)
```

## Supported Operations

| operation      | operator | example       |
| -------------- | :------: | ------------- |
| addition       | `+`      | `1 2 +` = 3   |
| subtraction    | `-`      | `1 2 -` = -1  |
| multiplication | `*`      | `1 2 *` = 2   |
| division       | `/`      | `1 2 /` = 0.5 |
| exponentation  | `**`     | `2 3 **` = 8  |
| floor          | `<`      | `12.7 <` = 12 |
| ceiling        | `>`      | `12.7 >` = 13 |

## Error Handling

In the case of an error, the program will exit with code 1 and output the appropriate error message.

For the exponentiation operation, errors will occur in the following cases:
- Negative base and non-integer exponent
- Both base and exponent are 0
- Base is 0 and exponent is negative

## Tests

To run the test cases (from the root directory), use the following command:

```
build/test/runTests
```
