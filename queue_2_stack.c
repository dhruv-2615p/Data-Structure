#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_SIZE 10001

typedef struct Stack_t* Stack;
typedef struct Queue* Queue;

struct Stack_t{
    int top;
    int *array;
};

struct Queue{
    Stack s1, s2;
};

Queue newQueue(){
    Queue queue = (Queue) calloc(1, sizeof(struct Queue));

    queue->s1 = (Stack) calloc(1, sizeof(struct Stack_t));
    queue->s2 = (Stack) calloc(1, sizeof(struct Stack_t));

    queue->s1->top = -1;
    queue->s2->top = -1;
    queue->s1->array = (int *) calloc(MAX_SIZE, sizeof(int));
    queue->s2->array = (int *) calloc(MAX_SIZE, sizeof(int));

    return queue;
}

void enqueue(Queue queue, int data){
    if(queue->s1->top == MAX_SIZE - 1)  return ;
    else{
        queue->s1->top++;
        queue->s1->array[queue->s1->top] = data;
    }
}

int dequeue(Queue queue){
    if(queue->s1->top == -1 && queue->s2->top == -1)    return -1;
    else{
        while(queue->s1->top != -1){
            queue->s2->top++;
            queue->s2->array[queue->s2->top] = queue->s1->array[queue->s1->top];
            queue->s1->top--;
        }
    }

    return queue->s2->array[queue->s2->top--];
}

int main(){
    Queue queue = newQueue();

    int choice, value;
    while (1) {
        printf("\nMenu:\n");
        printf("1. Enqueue\n");
        printf("2. Dequeue\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the value to enqueue: ");
                scanf("%d", &value);
                enqueue(queue, value);
                break;
            case 2:
                value = dequeue(queue);
                if (value != -1)
                    printf("Dequeued value: %d\n", value);
                break;
            case 3:
                exit(-1);
            default:
                printf("Invalid choice\n");
        }
    }

    return 0;
}