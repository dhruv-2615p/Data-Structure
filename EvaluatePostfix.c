#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

typedef struct stack* Stack;

struct stack{
    int top;
    unsigned capacity;
    int *array;
};

Stack createStack(unsigned capacity){
    Stack stack = (struct stack *)malloc(sizeof(struct stack));

    if (!stack)
        return NULL;

    stack->top = -1;
    stack->capacity = capacity;
    
    stack->array = (int *)malloc(stack->capacity * sizeof(int));

    if (!stack->array)
        return NULL;

    return stack;
}

int isEmpty(Stack stack)
{
    return stack->top == -1;
}

char pop(Stack stack)
{
    if (!isEmpty(stack))
        return stack->array[stack->top--];
    return '$';
}

void push(Stack stack, char op)
{
    stack->array[++stack->top] = op;
}

int evaluatePostfix(char *exp)
{

    Stack stack = createStack(strlen(exp));
    int i;

    if (!stack)
        return -1;

    for (i = 0; exp[i]; ++i)
    {
        if (isdigit(exp[i]))
            push(stack, exp[i] - '0');

        else
        {
            int val1 = pop(stack);
            int val2 = pop(stack);
            switch (exp[i])
            {
            case '+':
                push(stack, val2 + val1);
                break;
            case '-':
                push(stack, val2 - val1);
                break;
            case '*':
                push(stack, val2 * val1);
                break;
            case '/':
                push(stack, val2 / val1);
                break;
            }
        }
    }
    return pop(stack);
}

int main()
{

    char *exp = "34+75-*";  
      
    printf("infix expression: %s\n", exp);
    printf("Result is %d", evaluatePostfix(exp));

    return 0;
}
