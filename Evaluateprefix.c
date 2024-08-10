#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_VALUE 200

struct Stack {
    int top;
    double items[MAX_VALUE];
};

struct Stack *creatStack (){
    struct Stack *stack = (struct Stack*) malloc(sizeof(struct Stack));
    stack->top = -1;

    return stack;
}

int isFull(struct Stack *stack){
    return stack->top == (MAX_VALUE - 1);
}

void push(struct Stack* stack , double value){
    if(isFull(stack)){
        printf("Stack Overflow");
        exit(EXIT_FAILURE);
    }
    
    stack->items[++stack->top] = value;
}

int isEmpty(struct Stack *stack){
    return stack->top == -1;
}

double pop (struct Stack *stack){
    if(isEmpty(stack)){
        printf("Stack Underflow");
        exit(EXIT_FAILURE);
    }

    return stack->items[stack->top--];
}

double evaluatePrefix(char str1[], int length){
    struct Stack *stack = creatStack();

    for(int i = (length - 1); i >= 0; i--){

        if(isdigit(str1[i])){
            int temp  = 0;
            while(isdigit(str1[i])){
                temp = temp * 10 + (str1[i] - '0');
                i--;
            }
            i++;
            push(stack , temp);
        }
        else if (str1[i] == ' '|| str1[i] == '\t'){
            continue;
        }
        else {
            double op1 = pop(stack);
            double op2 = pop(stack);

            switch (str1[i]){
                case '+':
                    push(stack , op1 + op2);
                    break;
                
                case '-':
                    push(stack , op1 - op2);
                    break;

                case '/':
                    push(stack , op1 / op2);
                    break;

                case '*':
                    push(stack , op1 * op2);
                    break;

                default :
                    printf("Invalid Operator.");
                    exit(EXIT_FAILURE);
            }
        }
    }
    return pop(stack);
}

int main(){
    char str1[200];
    printf("Enter string of prefix expration: ");
    fgets(str1, 200, stdin);
    str1[strcspn(str1, "\n")] = '\0';

    int length = strlen(str1);
    double result = evaluatePrefix(str1, length);
    printf("Result: %lf", result);

    return 0;
}