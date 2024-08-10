#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_SIZE 100

typedef struct {
    char data;
} StackElement;

typedef struct {
    StackElement elements[MAX_SIZE];
    int top;
} Stack;

void initializeStack(Stack *stack) {
    stack->top = -1;
}

int isEmpty(Stack *stack) {
    return stack->top == -1;
}

void push(Stack *stack, char data) {
    if (stack->top == MAX_SIZE - 1) {
        printf("Stack overflow\n");
        exit(1); 
    }
    stack->elements[++stack->top].data = data;
}

char pop(Stack *stack) {
    if (isEmpty(stack)) {
        printf("Stack underflow\n");
        exit(1); 
    }
    return stack->elements[stack->top--].data;
}

int isMatchingPair(char open, char close) {
    if (open == '(' && close == ')') return 1;
    if (open == '{' && close == '}') return 1;
    if (open == '[' && close == ']') return 1;
    return 0;
}

int isBalanced(char *expression) {
    Stack stack;
    initializeStack(&stack);

    int i;
    for (i = 0; expression[i] != '\0'; i++) {
        char ch = expression[i];
        if (ch == '(' || ch == '{' || ch == '[') {
            push(&stack, ch);
        } else if (ch == ')' || ch == '}' || ch == ']') {
            if (isEmpty(&stack) || !isMatchingPair(pop(&stack), ch)) {
                return 0; 
            }
        } else if (!isspace(ch)) { 
            printf("Invalid character in expression: %c\n", ch);
            return 0; 
        }
    }

    return isEmpty(&stack);
}

int main() {
    char expression[MAX_SIZE];

    printf("Enter an expression: ");
    fgets(expression, MAX_SIZE, stdin);

    if (isBalanced(expression)) {
        printf("Expression is balanced\n");
    } else {
        printf("Expression is not balanced\n");
    }

    return 0;
}
