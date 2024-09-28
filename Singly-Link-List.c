/* Singly LInk List*/

#include <stdio.h>
#include <stdlib.h>

typedef int Type;
typedef struct Node_t* Node;

struct Node_t{
        Type data;
        Node next;
};

Node newNode(Node list, Type data){
        Node node = (Node) calloc (1,sizeof(struct Node_t));
        node->next = list;
        node->data = data;

        return node;
}

Node addFirst(Node node, Type data){
        return newNode(node, data);
}

int countNumber (Node node){
        int count = 0;
        for(; node; node = node->next){
                count++;
        }
        return count;
}

void printList (Node node){
        for(; node; node = node->next){
                printf("%d ->", node->data);
        }
        printf("NULL\n");
}

Node removeFirst(Node node, int *Data){
        if(!node){
                printf("List is Null");
                return ;
        }

        *Data = node->data;
        Node temp = node;
        node = node->next;
        free(temp);

        return node;
}

Node addEleLast(Node list,Type x){
        if(!list){
                printf("Your list is NULL");
                return addFirst(list, x);
        }

        Node temp = list;
        for(; temp->next; temp = temp->next)
                ;

        Node y = newNode(temp->next, x);
        temp->next = y;
        return list;
}

Node remLast(Node node){

        if(!node){
                printf("node is NULL");
                return;
        }
        Node temp = node;
        for(; temp->next->next; temp = temp->next)
                ;
        int data = (temp->next)->data;
        printf("data at last is: %d\n", data);

        Node p = temp->next;
        free(p);
        temp->next = NULL;

        return node;
}

void getEleIth(Node node,int j){
        if(node == NULL){
                printf("Node is NULL");
                return ;
        }

        Node temp = node;
        int i;
        for(i=0; i<j; i++){
                temp = temp->next;
        }
        int data = temp->data;
        printf("%dth posion's data is: %d\n",j, data);
}

Node setElePos(Node node, int index, int value){
        if(!node){
                printf("Node is NUll");
                return ;
        }

        Node temp = node;
        int i;
        for(i=0; i<index; i++){
                temp = temp->next;
        }
        temp->data = value;

        return node;
}

Node delEleIth(Node node, int position){
        if(!node){
                printf("Your node is NULL");
                return;
        }

        int i;
        if(position == 0){
                Node q = node;
                node = node->next;
                free(q);

        }
        else{
                Node temp = node;
                for(i=0 ; i<position-1 ; i++){
                        temp = temp->next;
                }
                Node q = temp->next;
                temp->next = temp->next->next;
                free(q);
        }

        return node;
}

Node addDataIth(Node node, int key, int data){
        if(!node){
                printf("Your node is empty");
                return ;
        }

        Node temp = node;
        for(; temp->next; temp = temp->next){
                if(temp->data == key)
                        break;
        }
        temp->next = newNode(temp->next, data);

        return node;
}

Node remData(Node node, int data){
        if(!node){
                printf("your node is NULL");
                return ;
        }
        Node temp = node;
        Node prevs = NULL;
        for(; temp; temp = temp->next){
                if(temp->data == data){
                        if(prevs == NULL){
                                node = temp->next;
                                free(temp);
                                return node;
                        }
                        else{
                                prevs->next = temp->next;
                                free(temp);
                                return node;
                        }
                }
                prevs = temp;
        }

        printf("Data %d not founda: ", data);
        return node;
}

void splitList(Node source, Node* fRef, Node* bRef){
        Node x = source;
        Node y = source->next;

        while(y != NULL){
                y = y->next;
                if(y != NULL){
                        x = x->next;
                        y = y->next;
                }
        }
        *fRef = source;
        *bRef = x->next;
        x->next = NULL;
}

Node mergSortList(Node a, Node b){
        Node result = NULL;

        if(a == NULL) return (b);
        else if(b == NULL) return (a);

        if(a->data <= b->data){
                result = a;
                result->next = mergSortList(a->next, b);
        }

        else{
                result = b;
                result->next = mergSortList(a, b->next);
        }

        return (result);
}

void sortedList(Node* node){
        Node current = *node;
        Node a;
        Node b;

        if((current == NULL) || (current->next == NULL)) return ;
        splitList(current, &a, &b);
        sortedList(&a);
        sortedList(&b);
        *node = mergSortList(a,b);

}

void printListRec(Node node){
        if(node == NULL){
                printf("NULL\n");
                return ;
        }

        printf("%d ->", node->data);
        node = node->next;
        printListRec(node);
}

void printListRevers(Node node){
        if(node == NULL){
                printf("NULL");
                return ;
        }

        printListRevers(node->next);
        printf("<- %d",node->data);
}

void reverseEle (Node node){
        int array[1000];
        int count = 0;
        Node current = node;

        while(current != NULL){
                array[count++] = current->data;
                current = current->next;
        }

        current = node;
        int i;
        for(i=count-1; i>=0; i--){
                current->data = array[i];
                current = current->next;
        }
}

Node revRecurs(Node node){

        if(node == NULL || node->next == NULL) return node;

        Node revers = revRecurs(node->next);
        node->next->next = node;
        node->next = NULL;

        return revers;
}

void insertSortedList(Node* node, int data){
        Node new = newNode(NULL, data);
        Node current = *node;
        Node prevs = NULL;

        while(current != NULL && current->data < data){
                prevs = current;
                current = current->next;
        }

        if(prevs == NULL){
                new->next = *node;
                *node = new;
        }
        else{
                new->next = current;
                prevs->next = new;
        }
}

int main(){


        int n;
        printf("Enter number of element in linked-list: ");
        scanf("%d", &n);

        Node list = NULL;

        int i, x;
        printf("Enter numbers for linked-list: \n");
        for(i=0; i<n; i++){
                scanf("%d", &x);
                list = addFirst(list, x);
        }

        printList(list);
        printf("Number of list is: %d\n", countNumber(list));

        int Data = 0;
        list = removeFirst(list, &Data);
        printf("list after first element removed\n");
        printf("Returend data: %d\n",Data);
        printList(list);

        int y;
        printf("Enter data that you want to insert at last: ");
        scanf("%d", &y);
        list = addEleLast(list, y);
        printf("After insterting data at the end \n");
        printList(list);

        printf("After removing last element of link-list: \n");
        list = remLast(list);
        printList(list);

        printf("Enter position whose data you want: ");
        int s;
        scanf("%d", &s);
        getEleIth(list, s);

        int idx;
        printf("Enter index whose data you want to set: ");
        scanf("%d", &idx);
        int val;
        printf("Enter data: ");
        scanf("%d", &val);
        list = setElePos(list,idx, val);
        printf("After set the value %d at %dth position\n", val, idx);
        printList(list);

        int posion;
        printf("Enter postion whose data you want to delet: ");
        scanf("%d", &posion);
        list = delEleIth(list, posion);
        printList(list);

        int key;
        printf("Enter key value after which you want to insert data: ");
        scanf("%d", &key);
        int data1;
        printf("Enter data that you want to enter: ");
        scanf("%d", &data1);
        list = addDataIth(list,key, data1);
        printList(list);

        int data2;
        printf("Enter data that you want to delet: ");
        scanf("%d", &data2);
        list = remData(list, data2);
        printList(list);

        sortedList(&list);
        printf("After sorting the list: \n");
        printList(list);

        int insert;
        printf("Enter data that you want to insert in sorted list: ");
        scanf("%d", &insert);
        printf("List after insertion data in sorted \n");
        insertSortedList(&list, insert);
        printList (list);

        printf("After reversing the list: \n");
        reverseEle(list);
        printList(list);

        printf("Using recursion printing of list: \n");
        printListRec(list);
        printf("Using recursion print reverse list: \n");
        printListRevers(list);
        printf("\n");

        printf("After reversing the list: \n");
        reverseEle(list);
        printList(list);

        printf("After reversing using recursion the list: \n");
        list = revRecurs(list);
        printList(list);

        return 0;
}
