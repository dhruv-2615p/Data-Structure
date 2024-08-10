#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_SIZE 101

struct Stack {
    int top;
    int items[MAX_SIZE];
};

struct Queue {
    struct Stack s1, s2;
};

void initQueue(struct Queue *q) {
    q->s1.top = -1;
    q->s2.top = -1;
}

void enqueue(struct Queue *q, int item) {
    if(q->s1.top == MAX_SIZE-1)
        printf("Queue is Full\n");
    else {
        q->s1.top++;
        q->s1.items[q->s1.top] = item;
    }
}

int dequeue(struct Queue *q) {
    int item;
    if(q->s1.top == -1 && q->s2.top == -1) {
        printf("Queue is Empty\n");
        return INT_MIN;
    }
    if(q->s2.top == -1) {
        while(q->s1.top != -1) {
            q->s2.top++;
            q->s2.items[q->s2.top] = q->s1.items[q->s1.top];
            q->s1.top--;
        }
    }
    item = q->s2.items[q->s2.top];
    q->s2.top--;
    return item;
}

int main() {
    struct Queue q;
    int choice, value;
    initQueue(&q);

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
                enqueue(&q, value);
                break;
            case 2:
                value = dequeue(&q);
                if (value != INT_MIN)
                    printf("Dequeued value: %d\n", value);
                break;
            case 3:
                exit(0);
            default:
                printf("Invalid choice\n");
        }
    }

    return 0;
}