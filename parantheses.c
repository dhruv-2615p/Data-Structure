#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

typedef struct stack* Stack;
typedef char* Type;

struct stack{
    int top;
    Type* array;
    int size;
    unsigned int capacity;
};

Stack newStack(unsigned int capacity){
    Stack stack = (Stack) calloc(1, sizeof(struct stack));
    stack->array = (Type*) calloc(capacity, sizrof(Type));
    stack->top = -1;
    stack->capacity = capacity;
    stack->size = 0;
}

int isFull(Stack stack){
    return stack->size == stack->capacity;
}

int isEmpty(Stack stack){
    return stack->top == -1;
}

void checkParentheses(char str1[]){
    int i;
    while(isdigit(str1[i]) || isalpha(str1[i])){
        i++;
    }
    while(str1[i] == '(')
}

int main(){
    char string[100];
    printf("Enter expression: ");
    fgets(string, 100, stdin);

    checkParentheses(string);
}