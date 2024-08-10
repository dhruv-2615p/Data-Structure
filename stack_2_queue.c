#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

typedef struct {
    int arr[MAX_SIZE];
    int top;
} Stack;

void initStack(Stack *s);
int isStackEmpty(Stack s);
int isStackFull(Stack s);
void push(Stack *s, int data);
int pop(Stack *s);

typedef struct {
    Stack s1, s2;
} Queue;

void initQueue(Queue *q);
int isQueueEmpty(Queue q);
void enqueue(Queue *q, int data);
int dequeue(Queue *q);

int main() {
    Queue q;
    initQueue(&q);

    int choice, data;

    do {
        printf("\nQueue Operations:\n");
        printf("1. Enqueue\n");
        printf("2. Dequeue\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the element to enqueue: ");
                scanf("%d", &data);
                enqueue(&q, data);
                break;
            case 2:
                if (isQueueEmpty(q)) {
                    printf("Queue is empty\n");
                } else {
                    data = dequeue(&q);
                    printf("Dequeued element: %d\n", data);
                }
                break;
            case 3:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice\n");
        }
    } while (choice != 3);

    return 0;
}

void initStack(Stack *s) {
    s->top = -1;
}

int isStackEmpty(Stack s) {
    return s.top == -1;
}

int isStackFull(Stack s) {
    return s.top == MAX_SIZE - 1;
}

void push(Stack *s, int data) {
    if (isStackFull(*s)) {
        printf("Error: Stack is full\n");
        return;
    }
    s->arr[++s->top] = data;
}

int pop(Stack *s) {
    if (isStackEmpty(*s)) {
        printf("Error: Stack is empty\n");
        return -1;
    }
    return s->arr[s->top--];
}

void initQueue(Queue *q) {
    initStack(&q->s1);
    initStack(&q->s2);
}

int isQueueEmpty(Queue q) {
    return isStackEmpty(q.s1) && isStackEmpty(q.s2);
}

void enqueue(Queue *q, int data) {
    push(&q->s1, data);
}

int dequeue(Queue *q) {
    int data;
    if (isStackEmpty(q->s2)) {
        while (!isStackEmpty(q->s1)) {
            push(&q->s2, pop(&q->s1));
        }
    }
    data = pop(&q->s2);

    return data;
}