#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

typedef struct stack* Stack;

struct stack {
    int top;
    unsigned capacity;
    int* array;
};

Stack creatStack (unsigned capacity){
    Stack stack = (Stack) calloc(1, sizeof(struct stack));

    assert(stack);

    stack->top = -1;
    stack->capacity = capacity;

    stack->array = (int*) calloc(capacity, sizeof(int));

    assert(stack->array);

    return stack;
}

int isEmpty(Stack stack){
    return stack->top == -1;
}

int isFull(Stack stack){
    return stack->top == stack->capacity - 1;
}

void push(Stack stack, char data){
    stack->array[++stack->top] = data;
}

char pop(Stack stack){
    if(isEmpty(stack)) return '0';

    return stack->array[stack->top--];
}

int evaluatePostfix(char *exp){
    Stack stack = creatStack(strlen(exp));
    assert(stack);

    int i;
    for(i = 0; exp[i]; ++i){

        if(isdigit(exp[i])){
            push(stack, exp[i] - '0');
        }
        else{
            int op1 = pop(stack);
            int op2 = pop(stack);

            switch(exp[i]){
                case '+':
                    push(stack, op1 + op2);
                    break;
                
                case '-':
                    push(stack, op2 - op1);
                    break;
                
                case '*':
                    push(stack, op2 * op1);
                    break;

                case'/':
                    push(stack, op2 / op1);
                    break;
            }
        }
    }

    return pop(stack);
}

int main(){
    char *exp = "34+75-*";

    printf("Entered expression is: %s", exp);
    printf("\nResult is: %d", evaluatePostfix(exp));

    return 0;
}