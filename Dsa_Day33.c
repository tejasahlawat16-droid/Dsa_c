/* Problem: Convert an infix expression to postfix notation using stack.

Input:
- Single line: infix expression (operands are single characters)

Output:
- Print the postfix expression

Example:
Input:
A+B*C

Output:
ABC*+

Explanation:
Operator precedence: * > +
Use stack to handle operator precedence and associativity
*/
#include <stdio.h>
#include <ctype.h>

#define MAX 100

char stack[MAX];
int top = -1;

// Push into stack
void push(char c) {
    stack[++top] = c;
}

// Pop from stack
char pop() {
    return stack[top--];
}

// Check precedence
int precedence(char c) {
    if (c == '+' || c == '-')
        return 1;
    if (c == '*' || c == '/')
        return 2;
    return 0;
}

int main() {
    char infix[MAX], postfix[MAX];
    int i = 0, k = 0;

    scanf("%s", infix);

    while (infix[i] != '\0') {
        char ch = infix[i];

        // If operand, add to postfix
        if (isalnum(ch)) {
            postfix[k++] = ch;
        }
        // If '(' push to stack
        else if (ch == '(') {
            push(ch);
        }
        // If ')', pop until '('
        else if (ch == ')') {
            while (top != -1 && stack[top] != '(') {
                postfix[k++] = pop();
            }
            pop(); // remove '('
        }
        // If operator
        else {
            while (top != -1 && precedence(stack[top]) >= precedence(ch)) {
                postfix[k++] = pop();
            }
            push(ch);
        }
        i++;
    }

    // Pop remaining operators
    while (top != -1) {
        postfix[k++] = pop();
    }

    postfix[k] = '\0';

    printf("%s\n", postfix);

    return 0;
}