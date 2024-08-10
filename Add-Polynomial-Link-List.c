#include <stdio.h>
#include <stdlib.h>

typedef struct Node_t* Node;

struct Node_t{
    int coeff;
    int expo;
    Node next;
};

Node newNode(Node next, int coeff, int expo){
    Node new = (Node) calloc(1, sizeof(struct Node_t));
    new->coeff = coeff;
    new->expo = expo;
    
    if(!next)
        new->next = NULL;

    else
        new->next = next;

    return new;
}

Node addFirst(Node node, int coeff, int expo){
    return newNode(node, coeff, expo);
}

Node addLast(Node node, int coeff, int expo){
    if(!node){
        return addFirst(node, coeff, expo);
    }

    Node p = node;
    for(; p->next; p = p->next)
        ;
    
    Node new = (Node) calloc(1, sizeof(struct Node_t));
    new->coeff = coeff;
    new->expo = expo;
    new->next = NULL;

    p->next = new;

    return node;
}

void printPoly(Node node){
    if(!node) return ;

    Node p = node;
    for(; p->next; p = p->next)
        printf("%d(x^%d) + ", p->coeff, p->expo);
    
    printf("%d(x^%d)\n", p->coeff, p->expo);
}

Node addPoly(Node poly1, Node poly2){
    Node temp1 = poly1, temp2 = poly2;
    Node p = NULL;
    while((temp1) && (temp2)){
        if(temp1->expo > temp2->expo){
            p = addLast(p, temp1->coeff, temp1->expo);
            temp1 = temp1->next;
        }

        else if(temp1->expo < temp2->expo){
            p = addLast(p, temp2->coeff, temp2->expo);
            temp2 = temp2->next;
        }

        else{
            p = addLast(p, temp1->coeff + temp2->coeff, temp1->expo);
            temp1 = temp1->next;
            temp2 = temp2->next;
        }
    }

    while(temp1){
        p = addLast(p, temp1->coeff, temp1->expo);
        temp1 = temp1->next;
    }

    while(temp2){
        p = addLast(p, temp2->coeff, temp2->expo);
        temp2 = temp2->next;
    }

    return p;
}

int main(){

    Node poly1 = NULL;
    Node poly2 = NULL;

    int t1, temp1, temp2;
    printf("Enter number of terms for polynomial 1: ");
    scanf("%d", &t1);

    for(int i = 0; i < t1; i++){
        printf("Enter %dth coefficent for polynomial 1: ", i+1);
        scanf("%d", &temp1);

        printf("Enter %dth exponent for polynomial 1: ", i+1);
        scanf("%d", &temp2);

        poly1 = addLast(poly1, temp1, temp2);
    }
    printPoly(poly1);

    int t2;
    printf("Enter number of terms for polynomial 2: ");
    scanf("%d", &t2);

    for(int i = 0; i < t2; i++){
        printf("Enter %dth coefficent for polynomial 2: ", i+1);
        scanf("%d", &temp1);

        printf("Enter %dth exponent for polynomial 2: ", i+1);
        scanf("%d", &temp2);

        poly2 = addLast(poly2, temp1, temp2);
    }
    printPoly(poly2);

    Node poly3 = NULL;
    poly3 = addPoly(poly1, poly2);
    printPoly(poly3);

    return 0;
}
