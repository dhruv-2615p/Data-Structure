#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct stack* Stack;
#define MAX 200 

struct stack{
    int top;
    int* array;
    int capacity;
};

Stack newStack(int capacity){
    Stack stack = (Stack) calloc(1, sizeof(struct stack));
    assert(stack);

    stack->array = (int *) calloc (capacity, sizeof(int));
    assert(stack->array);

    stack->top = -1;
    stack->capacity = capacity;

    return stack;
}

int isFull(Stack stack){
    return stack->top == stack->capacity - 1;
}

int isEmpty(Stack stack){
    return stack->top == -1;
}

void push(Stack stack, char data){
    if(isFull(stack)) return ;
    stack->array[++stack->top] = data;
}

char pop(Stack stack){
    if(isEmpty(stack)) return '@';
    return stack->array[stack->top--];
}

int presedence(char op){
    switch(op){
        case '+':
            return 1;
        case '-':
            return 1;
        case '*':
            return 2;
        case '/':
            return 2;
        default:
            return 0;
    }
}

void infixToPostfix(char *str, char *postFix){
    
    Stack stack = newStack(strlen(str));
    assert(stack);
    int j = 0;
    char token, poped;

    for(int i = 0; str[i]; i++){
        token = str[i];

        if(isalpha(token) || isdigit(token)){
            postFix[j++] = str[i];
        }
        
        else if(token == '('){
            push(stack, token);
        }

        else if(token == ')'){
            while((poped = pop(stack)) != '('){
                postFix[j++] = poped;
            }
        }

        else{
            while(stack->top != -1 && presedence(stack->array[stack->top]) >= presedence(token)){
                postFix[j++] = pop(stack);
            }
            push(stack, token);
        }
    }
    while(!isEmpty(stack)){
            postFix[j++] = pop(stack);
    }
    postFix[j] = '\0';

}

int main(){

    char str[MAX];
    printf("Enter infix expression: ");
    fgets(str, sizeof(str), stdin);
    
    printf("infix expression: %s\n", str);

    char postfix[MAX];

    infixToPostfix(str, postfix);
    printf("Postfix expression: %s\n", postfix);

    return 0;
}