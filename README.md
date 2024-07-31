# Expression Evaluator

This project is a simple mathematical expression evaluator written in C. It converts infix expressions to postfix (Reverse Polish Notation) and constructs an expression tree to evaluate the result.

## Features
- **Infix to Postfix Conversion**: Transforms infix expressions to postfix for easier computation.
- **Expression Tree Construction**: Builds a binary expression tree from the postfix expression.
- **Evaluation**: Recursively evaluates the expression tree to compute the result.

## How It Works
1. **Infix to Postfix Conversion**: The given infix expression is converted to postfix using a stack to handle operator precedence and parentheses.
2. **Tree Construction**: The postfix expression is used to construct a binary expression tree where each node represents an operator or operand.
3. **Evaluation**: The tree is recursively evaluated by performing the operations represented by the internal nodes.

## Usage
### Prerequisites
- A C compiler (e.g., GCC).

### Compilation
To compile the code, use the following command:
```sh
gcc -o expression_evaluator expression_evaluator.c

