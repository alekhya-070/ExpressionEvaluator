#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

// TreeNode structure for expression tree
typedef struct TreeNode {
    char value;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

// Function to create a new tree node
TreeNode* newNode(char v) {
    TreeNode* temp = (TreeNode*)malloc(sizeof(TreeNode));
    temp->value = v;
    temp->left = temp->right = NULL;
    return temp;
}

// Function to check if a given character is an operator
int isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

// Utility function to perform the corresponding operation
int applyOperator(int a, int b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return a / b;
    }
    return 0;
}

// Function to evaluate the expression tree
int evaluate(TreeNode* root) {
    // Base case: empty tree
    if (!root)
        return 0;

    // If the node is a leaf node, return its value
    if (!root->left && !root->right)
        return root->value - '0';

    // Evaluate the left subtree
    int leftVal = evaluate(root->left);

    // Evaluate the right subtree
    int rightVal = evaluate(root->right);

    // Apply the operator on the left and right subtree values
    return applyOperator(leftVal, rightVal, root->value);
}

// Function to construct the expression tree from postfix expression
TreeNode* constructTree(char* postfix) {
    TreeNode* t, * t1, * t2;
    int n = strlen(postfix);

    // Stack to hold tree nodes
    TreeNode* stack[n];
    int top = -1;

    // Traverse through every character of the postfix expression
    for (int i = 0; i < n; i++) {
        // If operand, create a new tree node and push it to the stack
        if (!isOperator(postfix[i])) {
            t = newNode(postfix[i]);
            stack[++top] = t;
        } else { // Operator
            t = newNode(postfix[i]);

            // Pop two top nodes from stack
            t1 = stack[top--]; // Store top
            t2 = stack[top--];

            // Make them children
            t->right = t1;
            t->left = t2;

            // Add this subexpression to the stack
            stack[++top] = t;
        }
    }

    // Only element will be the root of the expression tree
    t = stack[top--];

    return t;
}

// Function to convert infix expression to postfix expression
int precedence(char op) {
    if (op == '+' || op == '-')
        return 1;
    if (op == '*' || op == '/')
        return 2;
    return 0;
}

void infixToPostfix(const char* infix, char* postfix) {
    int n = strlen(infix);
    char stack[n];
    int top = -1;
    int k = 0;

    for (int i = 0; i < n; i++) {
        if (isdigit(infix[i])) {
            postfix[k++] = infix[i];
        } else if (infix[i] == '(') {
            stack[++top] = infix[i];
        } else if (infix[i] == ')') {
            while (top != -1 && stack[top] != '(') {
                postfix[k++] = stack[top--];
            }
            top--; // Remove '(' from stack
        } else {
            while (top != -1 && precedence(stack[top]) >= precedence(infix[i])) {
                postfix[k++] = stack[top--];
            }
            stack[++top] = infix[i];
        }
    }

    while (top != -1) {
        postfix[k++] = stack[top--];
    }

    postfix[k] = '\0';
}

int main() {
    // Test case 1: (5+((8+2)*2))
    char expression1[] = "(5+((8+2)*2))";
    char postfix1[50];
    infixToPostfix(expression1, postfix1);
    TreeNode* root1 = constructTree(postfix1);
    int result1 = evaluate(root1);
    printf("%s = %d\n", expression1, result1);

    // Test case 2: ((6*(2+1))*(3+(3+1)))
    char expression2[] = "((6*(2+1))*(3+(3+1)))";
    char postfix2[50];
    infixToPostfix(expression2, postfix2);
    TreeNode* root2 = constructTree(postfix2);
    int result2 = evaluate(root2);
    printf("%s = %d\n", expression2, result2);

    // User input
    char expression[50];
    printf("Enter the mathematical expression: ");
    scanf("%s", expression);
    char postfix[50];
    infixToPostfix(expression, postfix);
    TreeNode* root = constructTree(postfix);
    int result = evaluate(root);
    printf("Result: %d\n", result);

    return 0;
}
