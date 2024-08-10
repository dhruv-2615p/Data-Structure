#include <stdio.h>
#include <stdlib.h>

typedef int Type;
typedef struct Node_t* Node;

struct Node_t{
    Type data;
    Node next;
};

Node newNode(Node node, Type data){
    Node new = (Node) calloc (1, sizeof(struct Node_t));
    new->data = data;
    new->next = node;

    return new;
}

Node addData (Node node, Type data, Type exist, Type k){
    Node occure[k];
    int count = 0;
    Node last = NULL;
    Node temp = node;

    for(; temp; temp = temp->next){
        if(temp->data == exist){
            occure[count++] = temp;
        }
        last = temp;
    }
    
    if(count>=k){
        Node insert = occure[k-1];
        Node new = newNode(insert->next, data);
        insert->next = new;
    }

    return node;
}

void printList (Node node){
        for(; node; node = node->next){
                printf("%d ->", node->data);
        }
        printf("NULL\n");
}

int main(){

    Node list = NULL;
    list = newNode(list, 7);
    list = newNode(list, 56);
    list = newNode(list, 7);
    list = newNode(list, 1);
    list = newNode(list, 7);
    list = newNode(list, 5);
    list = newNode(list, 2);
    list = newNode(list, 7);
    list = newNode(list, 7);
    list = newNode(list, 3);
    list = newNode(list, 7);
    printList(list);
    list = addData(list, 19, 7, 6);

    printList(list);
    return 0;

}