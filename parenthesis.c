#include<stdio.h>
#include <ctype.h>
#include<string.h>
#include<stdlib.h>

#define MAX 10000

typedef struct Stack_t* Stack; 

struct Stack_t{
    char *arr; // Type* array..
    int top;
    int capacity;
};

Stack newStack (int capacity){
    Stack stack = (Stack) calloc (1, sizeof(struct Stack_t));
    stack->arr = (char *) calloc (capacity, sizeof(int)); //inplace of int char*
    stack->capacity = capacity;
    stack->top = -1;
    return stack;
}

int isEampty (Stack stack){
    return stack->top == -1;
}

int isFull(Stack stack){
    return stack->top == stack->capacity - 1;
}


int push(Stack stack, char data){
    if(isFull(stack)) return 0;
    stack->arr[++stack->top] = data;
    return 1;
}

char pop(Stack stack){
    if(isEampty(stack)) return '0';
    return stack->arr[stack->top--];
}

char peek(Stack stack){
    if(isEampty(stack)) return '0';
    return stack->arr[stack->top];
}


int order(char x){
    if(x == '(' || x == '{' || x == '['){
        return 1;
    }else{
        return 0;
    }
}

char compliment(char m){
    if(m == ')'){
        return '(';
    }else if( m == '}'){
        return '{';
    }else if(m == ']'){
        return '[';
    }
}

int isoperator(char ch){
    switch(ch){
        case '+':
            return 1;
        case '-':
            return 1;
        case '*':
            return 1;
        case '/':
            return 1;
        default:
            return 0;
    }
    return 0;
}

int main(){
    char exp[MAX]="2+4*(5+6)-{3+4}/[4-7]";

    Stack stack = newStack(MAX);

    int length = strlen(exp);
    int i;
    for(i = 0; i < length ; i++){
        int t = order(exp[i]);
        if(t){
            push(stack , exp[i]);
        }else{
            char p = peek(stack);
            char y = compliment(exp[i]);
            if(p == y){
                char w = pop(stack);
                continue;
            }
            else if(isdigit(exp[i]) || isalpha(exp[i]) || isoperator(exp[i])){
                continue;
            }
            else{
                printf("\n%d\n",i);
                printf("invalid expression");
                break;
            }
        }
    }

    if(isEampty(stack)){
        printf("valid expression");
    }else{
        printf("invalid expression");
    }
    return 0;
}