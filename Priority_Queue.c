#include <stdio.h>
#include <stdlib.h>

#define parent(i) ((i) / 2)
#define left(i) (2*(i) + 1)
#define right(i) (2*(i) + 2)

typedef struct Node_t* Node;
struct Node_t{
    int priority;
    int key;
};

typedef struct priority_Queue* PQ;
struct priority_Queue{
    Node* heap;
    int size;
};

PQ newPQ(){
    PQ pq = (PQ) calloc(1, sizeof(struct priority_Queue));
    pq->heap = (Node *) calloc(100, sizeof(Node));
    pq->size = 0;

    return pq;
}

Node insertNode(int priority, int key){
    Node new = (Node) calloc(1, sizeof(struct Node_t));
    new->key = key;
    new->priority = priority;

    return new;
}

void max_heapify(PQ pq, int i){
    int l = left(i);
    int r = right(i);

    int largest;
    if(l < pq->size && pq->heap[l]->priority > pq->heap[i]->priority)   largest = l;
    else    largest = i;

    if(r < pq->size && pq->heap[r]->priority > pq->heap[largest]->priority) largest = r;

    if(largest != i){
        Node temp = pq->heap[i];
        pq->heap[i] = pq->heap[largest];
        pq->heap[largest] = temp;

        max_heapify(pq, largest);
    }

}

void max_Heap_Increase_priority(PQ pq, int index, int newPriority){
    if(newPriority < pq->heap[index]->priority){
        printf("New priority is smaller.\n");
        return ;
    }

    pq->heap[index]->priority = newPriority;

    while(index > 0 && pq->heap[(index - 1) / 2]->priority < pq->heap[index]->priority){
        Node temp = pq->heap[index];
        pq->heap[index] = pq->heap[(index - 1)/ 2];
        pq->heap[(index - 1)/ 2] = temp;

        index = index - 1;
    }
}

void max_Heap_Insert(PQ pq, int priority, int key){
    if(pq->size == 100){
        printf("Queue is full\n");
        return ;
    }

    pq->heap[pq->size] = insertNode(priority, key);
    pq->size++;

    int i = pq->size - 1;
    while(i > 0 && pq->heap[(i - 1) / 2]->priority < pq->heap[i]->priority){
        Node temp = pq->heap[i];
        pq->heap[i] = pq->heap[parent(i)];
        pq->heap[parent(i)] = temp;

        i = parent(i);
    }

}

Node max_Heap_Maximum(PQ pq){
    if(!pq->size){
        printf("Queue is empty.\n");
        exit(0);
    }

    return pq->heap[0];
}

Node max_Heap_Extact_Max(PQ pq){
    if(!pq->size){
        printf("Queue is empty\n");
        Node empty;
        empty->priority = -1;
        empty->key = -1;

        return empty;
    }

    Node root = pq->heap[0];
    pq->heap[0] = pq->heap[pq->size - 1];
    pq->size--;
    max_heapify(pq, 0);

    return root;
}

void showPriorityQueue(PQ pq){
    printf("Showing queue: \n");
    for(int i = 0; i < pq->size; i++){
        printf("priority: %d\t key: %d\n", pq->heap[i]->priority, pq->heap[i]->key);
    }
}

int main(){
    PQ pq = newPQ();

    int choice, priority, value, index, newPriority;

    do{
        printf("\nPriority Queue Menu:\n");
        printf("1. Insert into priority queue.\n");
        printf("2. Extract maximmum from priority queue.\n");
        printf("3. Increase Priority.\n");
        printf("4. Maximum in priority queue.\n");
        printf("5. Show priority queue.\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter priority and value: ");
                scanf("%d %d", &priority, &value);
                max_Heap_Insert(pq, priority, value);
                break;

            case 2:
                if (pq->size > 0) {
                    Node dequeued = max_Heap_Extact_Max(pq);
                    printf("Extracted element: {%d, %d}\n", dequeued->priority, dequeued->key);
                }
                break;

            case 3:
                printf("Enter the index of the element: ");
                scanf("%d", &index);
                printf("Enter the new priority: ");
                scanf("%d", &newPriority);
                max_Heap_Increase_priority(pq, index, newPriority);
                break;

            case 4: 
                printf("Maximum priority elemnt in priority queue is: \n");
                Node maximum = max_Heap_Maximum(pq);
                printf("Maximum element: {%d , %d}\n", maximum->key, maximum->priority);
                break;

            case 5:
                showPriorityQueue(pq);
                break;

            case 6:
                printf("Exiting...\n");
                return 0;

            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
        
    }while(choice != 6);

    return 0;
}
