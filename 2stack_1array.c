#include <stdio.h>
#include <stdlib.h>

#define Max_Size 1000
typedef struct Stack_t* Stack;

struct Stack_t{
    int array[Max_Size];
    int top1;
    int top2;
};

Stack cerateStack(){
    Stack stack = (Stack) calloc(1, sizeof(struct Stack_t));
    stack->top1 = -1;
    stack->top2 = Max_Size;

    return stack;
}

void push1(Stack stack, int data){
    if(stack->top1 < stack->top2 - 1){
        stack->array[++stack->top1] = data;
    }else{
        printf("Stack Overflow");
    }    
}

void push2(Stack stack, int data){
    if(stack->top1 < stack->top2 - 1){
        stack->array[--stack->top2] = data;
    }else{
        printf("Stack Overflow");
    }
}

int pop1(Stack stack){
    if(stack->top1 >= 0){
        return stack->array[stack->top1--];
    }else{
        printf("Stack Undeflow");
        return -1;
    }
}

int pop2(Stack stack){
    if(stack->top2 < Max_Size){
        return stack->array[stack->top2++];
    }else{
        printf("Stack Underflow");
        return -1;
    }
}

int main(){
    Stack stack = cerateStack();

    int choice, value;

    while (1) {
        printf("\nMenu:\n");
        printf("1. Push to Stack 1\n");
        printf("2. Push to Stack 2\n");
        printf("3. Pop from Stack 1\n");
        printf("4. Pop from Stack 2\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the value to push: ");
                scanf("%d", &value);
                push1(stack, value);
                break;
            case 2:
                printf("Enter the value to push: ");
                scanf("%d", &value);
                push2(stack, value);
                break;
            case 3:
                value = pop1(stack);
                if (value != -1)
                    printf("Popped value from Stack 1: %d\n", value);
                break;
            case 4:
                value = pop2(stack);
                if (value != -1)
                    printf("Popped value from Stack 2: %d\n", value);
                break;
            case 5:
                exit(0);
            default:
                printf("Invalid choice\n");
        }
    }

    return 0;
}
