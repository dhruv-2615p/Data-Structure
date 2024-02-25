/* Stack With Using Array */

#include <stdio.h>
#include <stdlib.h>

typedef struct Stack_t* Stack;
typedef int* Type;

struct Stack_t{
    Type array;
    int top;
    unsigned int capacity;
};

Stack newStack (unsigned int capacity){
    Stack stack = (Stack) calloc (1, sizeof(struct Stack_t));
    stack->array = (Type) calloc (capacity, sizeof(int));
    stack->capacity = capacity;
    stack->top = -1;
}

int isEampty (Stack stack){
    return stack->top == -1;
}

int isFull(Stack stack){
    return stack->top == stack->capacity - 1;
}

int push(Stack stack, int data){
    if(isFull(stack)) return 0;
    stack->array[++stack->top] = data;
    return 1;
}

int pop(Stack stack, int *pData){
    if(isEampty(stack)) return 0;
    *pData = stack->array[stack->top--];
    return 1;
}

int peek(Stack stack, int *pData){
    if(isEampty(stack)) return 0;
    *pData = stack->array[stack->top];
    return 1;
}

int main (){

    int n;
    printf("Enter number of elements for stack: ");//work for 5 elements
    scanf("%d", &n);

    Stack stack = newStack(n);

    int dat,status, data;
    do{
        printf("Menu\n");
        printf("1. Push the data in stack.\n");
        printf("2. Pop the data from stack.\n");
        printf("3. Peek the data from stack.\n");
        printf("4. check stack is full or not.\n");
        printf("5. check stack is empty or not.\n");
        printf("6. Exit.\n");
        printf("Enter your choice: ");
        scanf("%d", &dat);

        switch(dat){
            case 1:
                printf("Enter elements for stack: ");
                scanf("%d", &data);
                status = push(stack, data);
                printf("status: %d, pushed data: %d\n", status, data);
                break;

            case 2:
                status = pop(stack, &data);
                printf("status: %d, poped data: %d\n", status, data);
                break;

            case 3:
                status = peek(stack, &data);
                printf("status: %d, peeked data: %d\n", status, data);
                break;

            case 4:
                status = isFull(stack);
                if(status) printf("Stack is Overflow.\n");
                else printf("Stack is not Overflow.\n");
                break;

            case 5:
                status = isEampty(stack);
                if(status) printf("Stack is empty.\n");
                else printf("Stack is not empty.\n");
                break;

            default:
                exit(EXIT_FAILURE);
                printf("Enter vaild number.\n");
        }
    }while(dat < 6);

    return 0;

}