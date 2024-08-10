#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_SIZE 100

char stack[MAX_SIZE];
int top = -1;

char *reverse(char *str) {
    int i, j;
    char temp;
    for (i = 0, j = strlen(str) - 1; i < j; i++, j--) {
        temp = str[i];
        str[i] = str[j];
        str[j] = temp;
    }
    return str;
}

void push(char op) {
    if (top == MAX_SIZE - 1) {
        printf("Stack Overflow\n");
        exit(1);
    }
    stack[++top] = op;
}

char pop() {
    if (top == -1) {
        printf("Stack Underflow\n");
        exit(1);
    }
    return stack[top--];
}

int isOperator(char ch) {
    return (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^');
}

int precedence(char ch) {
    switch (ch) {
        case '^':
            return 3;
        case '*':
        case '/':
            return 2;
        case '+':
        case '-':
            return 1;
        default:
            return -1;
    }
}

void infixToPrefix(char *infix, char *prefix) {
    int i, j;
    char ch, popped;

    infix = reverse(infix);

    for (i = 0, j = 0; infix[i] != '\0'; i++) {
        ch = infix[i];
        if (isalnum(ch)) {
            prefix[j++] = ch;
        } else if (ch == ')') {
            push(ch);
        } else if (ch == '(') {
            while ((popped = pop()) != ')') {
                prefix[j++] = popped;
            }
        } else if (isOperator(ch)) {
            while (top != -1 && precedence(stack[top]) >= precedence(ch)) {
                prefix[j++] = pop();
            }
            push(ch);
        }
    }

    while (top != -1) {
        prefix[j++] = pop();
    }

    prefix[j] = '\0';
    prefix = reverse(prefix);
}

int main() {
    char infix[MAX_SIZE], prefix[MAX_SIZE];

    printf("Enter the infix expression: ");
    fgets(infix, MAX_SIZE, stdin);
    infix[strcspn(infix , "\n")] = '\0';

    infixToPrefix(infix, prefix);

    printf("Prefix expression: %s", prefix);

    return 0;
}
