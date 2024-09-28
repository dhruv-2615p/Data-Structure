/*Doubly Link List*/

#include <stdio.h>
#include <stdlib.h>

typedef struct Node_t* Node;
typedef int Type;

struct Node_t{
    Node prev;
    Type data;
    Node next;
};

Node head = NULL;
Node tail = NULL;

void addFirst(int data){
    Node new = (Node) calloc(1, sizeof(struct Node_t));
    new->prev = NULL;
    new->data = data;
    new->next = head;
    
    if(head){
        head->prev = new;
    }
    else{
        tail = new;
    }
    head = new;
}

void removeFirst(int *pData){
    if(!head){
        return ;
    }

    *pData = head->data;
    Node p = head;
    head = head->next;

    if(head){
        head->prev = NULL;
    }
    else{
        tail = NULL;
    }
    free(p);
}

void addLast(int data){
    Node new = (Node) calloc(1, sizeof(struct Node_t));
    new->prev = tail;
    new->data = data;
    new->next = NULL;

    if(tail){
        tail->next = new;
    }
    else{
        head = new;
    }
    tail = new;
}

void removeLast(int *pData){
    if(!head){
        return ;
    }

    *pData = tail->data;
    Node p = tail;
    tail = tail->prev;

    if(tail){
        tail->next = NULL;
    }
    else{
        head = NULL;
    }
    free(p);
}

int countList(){
    if(!head){
        return 0;
    }
    Node p = head;
    int count = 0;
    for(; p; p = p->next){
        count++;
    }
    
    return count;
}

void addIth(int index, int data){
    if(!head){
        return ;
    }

    if(index == 0){
        addFirst(data);
        return ;
    }
    else if(index + 1 == countList()){
        addLast(data);
        return ;
    }
    else{
        Node p = head;
        int i, count = 0;
        for(i=0; i<index; i++){
            count++;
            p = p->next;
        }
        Node temp = p->next;
        Node new = (Node) calloc(1, sizeof(struct Node_t));
        new->prev = p;
        new->data = data;
        new->next = temp;

        p->next = new;
        temp->prev = new;
        return ;
    }
    printf("Index not found.");
}

void keyInsert(int key, int data){
    if(!head){
        return ;
    }

    Node p = head;
    int count = 0;

    for(; p ; p = p->next){
        count++;
        if(p->data == key){
            addIth(count - 1, data);
            return ;
        }
    }

    printf("Key not found.");
}

int removeIth(int index){
    if(!head){
        return 0;
    }

    Node p = head;
    int i, data;

    if(index == 0){
        removeFirst(&data);
        return data;
    }
    else if(index + 1 == countList()){
        removeLast(&data);
        return data;
    }
    else{

        for(i=0; i<index - 1; i++){
            p = p->next;
        }

        Node q = p->next;
        data = q->data;
        Node temp = q->next;

        p->next = temp;
        temp->prev = p;

        free(q);
        return data;
    }
    printf("Index not found.");
}

int keyRemove(int key){
    if(!head){
        return 0;
    }

    int count = 0, data;
    Node p = head;

    for(; p; p = p->next){
        count++;
        if(p->data == key){
            data = removeIth(count - 1);
            return data;
        }
    }

    printf("Key not found.");
}

void reverseList(){
    if(!head){
        return ;
    }

    Node p = head;
    Node q = NULL, next = NULL;

    while(p){
        next = p->next;
        p->next = q;
        p->prev = next;
        q = p;
        p = next;
    }
    tail = head;
    head = q;
}

void printForward(Node head){
    if(!head){
        return ;
    }

    Node p = head;
    for(; p->next; p = p->next){
        printf("%d -> ", p->data);
    }
    printf("%d\n", p->data);
}

void printForwardRecursion(Node head){

    if(!head){
        return ;
    }
    
    
    printf("%d -> ", head->data);
    head = head->next;
    printForwardRecursion(head);

    return;
}

void printBackwardRecursion(Node tail){
    static Node p = NULL;
    if(!p){
        p = tail;
    }

    if(!p->prev){
        printf("%d\n", tail->data);
        return ;
    }

    printf("%d <- ", tail->data);
    p = p->prev;
    printBackwardRecursion(p);

    return;
}

void printBackward(Node tail){
    if(!head){
        return ;
    }

    Node p = tail;
    for(; p->prev; p = p->prev){
        printf("%d <- ", p->data);
    }
    printf("%d\n", p->data);
}

void insertSorted (){
    int n;
    printf("Enter number for link list: ");
    scanf("%d", &n);

    int i,temp;
    Node head1 = NULL;
    Node tail1 = NULL;
    printf("Enter data for sorted link-list: \n");
    for(i=0; i<n; i++){
        scanf("%d", &temp);
        Node new = (Node) calloc(1, sizeof(struct Node_t));
        new->prev = NULL;
        new->data = temp;
        new->next = head1;
        
        if(head1){
            head1->prev = new;
        }
        else{
            tail1 = new;
        }
        head1 = new;
    }
    printForward(head1);
    printBackward(tail1);

    int data, count = 0;
    printf("Enter data that you want to insert in sorted list: ");
    scanf("%d", &data);

    Node p = head1;
    Node q = NULL;
    while(p && p->data < data){
        q = p;
        p = p->next;
    }
    if(!q){
        Node new = (Node) calloc (1, sizeof(struct Node_t));
        new->data = data;
        new->next = p;
        new->prev = NULL;
        head1 = new;
        printForward(head1);
        return ;
    }
    if((!p)){
        Node new = (Node) calloc (1, sizeof(struct Node_t));
        new->data = data;
        new->next = NULL;
        new->prev = q;
        q->next =  new;
        tail1 = new;
        printForward(head1);
        return ;
    }
    else{
        Node new = (Node) calloc (1, sizeof(struct Node_t));
        new->data = data;
        new->next = p;
        new->prev = q;
        q->next = new;
        p = new;
        printForward(head1);
        return ;
    }

}

void mergeList(){
    int n;
    printf("Enter number for link list: ");
    scanf("%d", &n);

    int i,temp;
    Node head1 = NULL;
    Node tail1 = NULL;
    printf("Enter data for link-list: \n");
    for(i=0; i<n; i++){
        scanf("%d", &temp);
        Node new = (Node) calloc(1, sizeof(struct Node_t));
        new->prev = NULL;
        new->data = temp;
        new->next = head1;
        
        if(head1){
            head1->prev = new;
        }
        else{
            tail1 = new;
        }
        head1 = new;
    }
    printForward(head1);
    printBackward(tail1);

    tail->next = head1;
    head1->prev = tail;

    Node temp1 = head1;
    while(temp1->next != NULL) {
        temp1 = temp1->next;  
    }
    tail = temp1;
    
}

int getElement(int index){
    if(!head){
        return 0;
    }

    Node p = head;
    int i, data;
    for(i=0; i<index; i++){
        p = p->next;
    }
    data = p->data;
    return data;
}

void sortList() {

    Node current = head; 
    Node index = NULL;

    if (current == NULL) {
    return;
    }

    while (current != NULL) {

    index = current->next;  

    while (index != NULL) {
        if (current->data > index->data) {
        int temp = current->data;
        current->data = index->data;
        index->data = temp;
        }

        index = index->next;
    }
    current = current->next;
    }
}

void reverseListRecursion(Node head) {
   
    if (head == NULL || head->next == NULL) {
        return; 
    }
    reverseListRecursion(head->next);

    Node temp = head->next;  
    head->next = head->prev;   
    head->prev = temp;           

    head = head->prev;         
}

int main(){

    int n;
    printf("Enter number for link list: ");
    scanf("%d", &n);

    int i,temp;
    printf("Enter data for link-list: \n");
    for(i=0; i<n; i++){
        scanf("%d", &temp);
        addFirst(temp);
    }
    
    printf("Link - List: \n");
    printForward(head);
    printBackward(tail);
    
    int data;
    printf("Enter data that you want to insert at last: ");
    scanf("%d", &data);

    addLast(data);
    printForward(head);
    printBackward(tail);
    
    int data1;
    removeFirst(&data1);
    printf("After removing data %d from beginning: \n", data1);
    printForward(head);
    printBackward(tail);
    
    removeLast(&data1);
    printf("After removing data %d from last: \n", data1);
    printForward(head);
    printBackward(tail);

    printf("Number of node in list are %d\n", countList());

    int index;
    printf("Enter index after which you want to insert data: ");
    scanf("%d", &index);

    int data2;
    printf("Enter data that you want to insert: ");
    scanf("%d", &data2);

    addIth(index, data2);
    printForward(head);
    printBackward(tail);

    int index2;
    printf("Enter index which you want to delet: ");
    scanf("%d", &index2);

    printf("Data present at %dth position is %d: \n", index2, removeIth(index2));
    printForward(head);
    printBackward(tail);

    int key;
    printf("Enter key value after which you want to insert data: ");
    scanf("%d", &key);

    printf("Enter data that you want to insert: ");
    scanf("%d", &data);

    keyInsert(key, data);
    printForward(head);
    printBackward(tail);

    printf("Enter key value which you want to delet: ");
    scanf("%d", &key);

    printf("Data present is %d. \n", keyRemove(key));
    printForward(head);
    printBackward(tail);

    printf("Reverse the list: \n");
    reverseList();
    printForward(head);
    printBackward(tail);

    insertSorted();
    
    mergeList();
    printf("After merging list: \n");
    printForward(head);
    printBackward(tail);
    
    printf("After sorting the list: \n");
    sortList();
    printForward(head);
    printBackward(tail);

    int index3;
    printf("Enter index whose data you want: ");
    scanf("%d", &index3);

    printf("Data present at %dth position is %d: \n", index3, getElement(index3));
    
    printf("Using recursion printing list: \n");
    printForward(head);
    printBackward(tail);

    printf("Using recursion reverse the list: \n");
    printBackward(tail);
    printForward(head);

    // printf("Using recursion printing list: ");
    // printForwardRecursion(head);
    // printBackwardRecursion(tail);

    // reverseListRecursion(head);
    // printForward(head);
    // printBackward(tail);

    return 0;
}
