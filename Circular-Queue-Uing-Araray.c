/*Circular Queue Uing Araray*/

#include <stdio.h>
#include <stdlib.h>

typedef struct Queue_t* Queue;
typedef int* Type;

struct Queue_t{
    Type array;
    int rear, front, size;
    unsigned int capacity;
};

Queue newQueue(unsigned int capacity){

    Queue new = (Queue) calloc (1, sizeof(struct Queue_t));

    new->array = (Type) calloc(capacity, sizeof(int));
    new->capacity = capacity;
    new->front = 0;
    new->rear = (capacity - 1);
    new->size = 0;

    return new;
}

int isFull(Queue queue){
    return queue->size == queue->capacity;
}

int enQueue (Queue queue, int data){

    if(isFull(queue)) return 0;

    queue->rear = (queue->rear + 1) % queue->capacity;
    queue->array[queue->rear] = data;
    queue->size++;

    return 1;
}

int isEmpty(Queue queue){
    return queue->size == 0;
}

int deQueu(Queue queue, int *pData){

    if(isEmpty(queue)) return 0;

    *pData = queue->array[queue->front];
    queue->front = (queue->front + 1) % queue->capacity;
    queue->size--;

    return 1;
}

int inFront(Queue queue , int *pData){
    if(isEmpty(queue)) return 0;

    *pData = queue->array[queue->front];
    return 1;
}

int inRear(Queue queue, int *pData){
    if(isFull(queue) || isEmpty(queue)) return 0;

    *pData = queue->array[queue->rear];
    return 1;
}

void printQueue(Queue queue){
    if(!queue) return ;

    int i, x;
    for(i=0; i<queue->capacity; i++){
        printf("%d ", queue->array[i]);
    }
    printf("\n");
}

int main(){

    int n;
    printf("Enter number of element for queue: ");
    scanf("%d", &n);

    Queue queue = NULL;
    queue = newQueue(n);

    int dat,status, data;
    do{
        printf("Menu\n");
        printf("1. enqueue the data in queue.\n");
        printf("2. dequeue the data from queue.\n");
        printf("3. Peek the data from front.\n");
        printf("4. Peek the data from rear.\n");
        printf("5. check queue is full or not.\n");
        printf("6. check queue is empty or not.\n");
        printf("7. Exit.\n");
        printf("Enter your choice: ");
        scanf("%d", &dat);

        switch(dat){
            case 1:
                printf("Enter elements for queue: ");
                scanf("%d", &data);
                status = enQueue(queue, data);
                printf("status: %d, enqueued data: %d\n", status, data);
                break;

            case 2:
                status = deQueu(queue, &data);
                printf("status: %d, poped data: %d\n", status, data);
                break;

            case 3:
                status = inFront(queue, &data);
                printf("status: %d, data at front: %d\n", status, data);
                break;

            case 4:
                status = inRear(queue, &data);
                printf("status: %d, data at rear: %d\n", status, data);
                break;

            case 5:
                status = isFull(queue);
                if(status) printf("queue is Full.\n");
                else printf("queue is not full.\n");
                break;

            case 6:
                status = isEmpty(queue);
                if(status) printf("queue is empty.\n");
                else printf("queue is not empty.\n");
                break;

            default:
                exit(EXIT_FAILURE);
                printf("Enter vaild number.\n");
        }
    }while(dat < 7);

    
    return 0;
}