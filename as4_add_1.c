#include <stdio.h>
#include <stdlib.h>

typedef struct Node_t* Node;
typedef int Type;

struct Node_t{
    int data;
    Node next;
};

Node newNode(Node node, int data){
    Node node = (Node) calloc (1, sizeof(struct Node_t));
    node->next = node; 
    node->data = data;

    return node;
}

Node addFirst(Node node, int data){
    return newNode(node, data);
}

void printList (Node node){
    for(; node; node = node->next){
        printf("%d ->", node->data);
    }
    printf("NULL\n");
}

Node rectifyLoop(Node node){
    if(!node){
        return NULL;
    }

    Node p = node;
    Node q = NULL;
    while(p){
        q = p->next;
        p = p->next->next;
        if(q == p){
            pritnf("loop detected");
        }
    }
    Node new = NULL;
    p = node;
    while(p->data != -1){
        node = addFirst(node, p->data);
        p->data = -1;
    }

    return new;
}

int main(){

    Node list = NULL;
    list = addFirst(list, 0);
    list = rectifyLoop(list);

    return 0;
}
