/* Circular Doubly Link List*/

#include <stdio.h>
#include <stdlib.h>

typedef struct Node_t* Node;
typedef int Type;

struct Node_t{
        Node prev;
        Type data;
        Node next;
};

Node newNode(Node prev, Type data, Node next){

        Node new = (Node) calloc(1, sizeof(struct Node_t));
        new->prev = prev;
        new->data = data;
        new->next = next;

        return new;
}

Node addFirst(Node node, Type data){

        if(!node){
                node = newNode(NULL, data, NULL);
                node->prev = node;
                node->next = node;
                return node;
        }

        Node p = newNode(node->prev, data, node);
        p->next->prev = p;
        p->prev->next = p;

        return p;
}

Node removeFirst(Node node){
        if(!node)
                return NULL;
        if(node->next == node){
                free(node);
                return NULL;
        }

        node->next->prev = node->prev;
        node->prev->next = node->next;
        Node p = node->next;
        free(node);

        return p;
}

Node removeLast(Node node){
        if(!node)
                return NULL;

        if(node == node->next)
                return removeFirst(node);

        return removeFirst(node->prev);
}

void printList(Node node){
        if(!node){
                printf("NULL\n");
                return;
        }

        Node p = node;
        for(; p->next != node ; p = p->next)
                printf("%d -> ", p->data);

        printf("%d\n", p->data);

        for(; p != node; p = p->prev)
                printf("%d <- ", p->data);

        printf("%d\n", p->data);
}

Node addLast(Node node, Type data){
        return (addFirst(node, data)->next);
}

int countList(Node node){
        int count = 0;
        Node p = node;

        for(; p->next != node; p= p->next)
                count++;

        printf("No. of element in list is: %d\n", ++count);
        return count;
}

void getEle(Node node, int index){
        int j;
        Node p = node;
        for(j=0; j<index; j++)
                p = p->next;

        printf("Data present at the %dth position is: %d\n", index, p->data);
}

void setEle(Node node, int index, int data){
        int j;
        Node p = node;

        for(j=0; j<index; j++)
                p = p->next;

        p->data = data;
        printf("After seting data at %dth index list is: \n", index);
        printList(node);
}

Node keyInsr(Node node, int key, int data){
        if(!node){
                printf("NULL\n");
        }

        Node p = node;
        int i;

        for(; p->next !=node; p = p->next){
                if(p->data == key){
                        p = newNode(p->next->prev, data, p->next);
                        p->next->prev = p;
                        p->prev->next = p;

                        return node;
                }
        }

        if(p->data == key){
                p = newNode(p->next->prev, data, p->next);
                p->next->prev = p;
                p->prev->next = p;

                return node;
        }
        else{
                printf("Key not found");
        }
}

Node addPosion(Node node, int index, int data){
        Node p = node;

        int i;
        for(i=0; i<index; i++)
                p = p->next;

        p = newNode(p->next->prev, data, p->next);
        p->next->prev = p;
        p->prev->next = p;

        return node;
}

Node delIdx(Node node, int index){
        if(!node)
                return NULL;

        if(node == node->next)
                return removeFirst(node);

        if(index == 0)
                return removeFirst(node);

        int num = countList(node);
        if(index+1 == num)
                return removeLast(node);

        Node p = node;
        int i;
        for(i=0; i<index; i++)
                p = p->next;


        p->next->prev = p->prev;
        p->prev->next = p->next;
        free(p);

        return node;
}

Node remKey(Node node, int key){
        if(!node){
                printf("NULL");
                return;
        }

        int count = 0;
        Node p = node;
        for(; p->next != node; p = p->next){
                count++;
                if(p->data == key)
                        return delIdx(node, count-1);
        }

        if(p->data == key)
                return delIdx(node, count);

        else
                printf("Key is not found");

        return ;
}

void printRecn(Node node){

        static Node start = NULL;
        if(start == NULL)
                start = node;

        printf("%d -> ", node->data);
        if(node->next != start)
                printRecn(node->next);

        return ;
}

void printRec(Node node){
        if(!node){
                printf("NULL\n");
                return ;
        }

        Node current = node;
        printRecn(current);

        return;
}

void printRecnRev(Node node){
        static Node prev = NULL;
        if(prev == NULL)
                prev = node;

        printf("%d <- ", node->data);
        if(node->prev != prev)
                printRecnRev(node->prev);

        return;
}

void printRevRec(Node node){
        if(!node){
                printf("NULL\n");
                return ;
        }

        Node current = node;
        printRecnRev(current->prev);

}

Node mergList(Node *node1, Node *node2){
        if(!*node1)
                return *node2;

        if(!*node2)
                return *node1;

        Node p = *node1;
        Node q = *node2;
        Node r = q->prev;

        p->prev->next = q;
        q->prev = p->prev;

        p->prev = q->prev;
        r->next = p;

        return *node1;
}

Node insertSort(Node node, int data){
        if(!node)
                return addFirst(node, data);

        Node current = node;
        Node prev = NULL;

        while(current->next != node && current->data < data){
                prev = current;
                current = current->next;
        }

        if(prev == NULL){
                Node new = addFirst(node, data);
                node = new;
                return node;
        }

        if(!(current->data < data))
                return keyInsr(node, prev->data, data);

        if(current->data < data)
                return addLast(node, data);

}

Node sortList(Node node){
        if(!node)
                return NULL;

        if(node->next == node)
                return node;

        Node p = node;
        Node next = NULL;
        for(; p->next != node; p = p->next)
                next = insertSort(next, p->data);

        next = insertSort(next, p->data);

        return next;
}

Node mergSortList(Node node1, Node node2){

        Node p = node1;
        Node q = node2;
        Node next = NULL;

        for(; q->next != node2; q = q->next)
                next = insertSort(node1, q->data);

        next = insertSort(node1, q->data);

        return node1;
}

Node reversListAnother(Node node){
        if(!node)
                return ;

        Node p = node;
        Node temp = NULL;

        for(; p->next != node; p = p->next)
                temp = addFirst(temp, p->data);

        temp = addFirst(temp, p->data);

        return temp;
}

Node reversList(Node node){
        if(!node || node->next == node)
                return ;

        Node prev = node->prev;
        Node temp = node;
        Node next;

        while(temp != prev){
                next = temp->next;
                temp->next = temp->prev;
                temp->prev = next;
                temp = temp->prev;
        }

        temp->next = temp->prev;
        temp->prev = node;

        Node p = node;
        node = prev;

        return node;
}

Node reversRec(Node node){

        if(!node)
                return;

        if(node->next == node)
                return node;

        //static Node prev = NULL;
        //if(prev == NULL)
        //prev = node;

        Node temp =  reversRec(node->next);
        node->next->prev = node->next->next;
        node->next->next = node;
        node->prev = temp;

        return temp;
}


int main(){
        Node list = NULL;

        int n;
        printf("Enter number of elements for list: ");
        scanf("%d", &n);

        printf("Enter data element for list: \n");
        int i, temp;
        for(i=0; i<n; i++){
                scanf("%d", &temp);
                list = addFirst(list, temp);
        }
        printList(list);

        printf("Your sorted list: \n");
        list = sortList(list);
        printList(list);

        int data0;
        printf("Enter data that you want to insert at last: ");
        scanf("%d", &data0);
        list = addLast(list, data0);
        printf("After inserting data at last: \n");
        printList(list);
        int count = countList(list);

        list = removeFirst(list);
        printf("After removing element from first: \n");
        printList(list);

        printf("After removing element from last: \n");
        list = removeLast(list);
        printList(list);

        int index;
        printf("Enter index of which data you want: ");
        scanf("%d", &index);
        getEle(list, index);

        int index2;
        printf("Enter index of which data you want to set: ");
        scanf("%d", &index2);
        int data1;
        printf("Enter data thet you want to set: ");
        scanf("%d", &data1);
        setEle(list, index2, data1);

        int index3;
        printf("Enter index after you want to insert data: ");
        scanf("%d", &index3);
        int data2;
        printf("Enter data thet you want to insert: ");
        scanf("%d", &data2);
        list = addPosion(list, index3, data2);
        printList(list);

        int key;
        printf("Enter key value after which you want to insert data: ");
        scanf("%d", &key);
        int data4;
        printf("Enter data thet you want to insert: ");
        scanf("%d", &data4);
        list = keyInsr(list, key, data4);
        printList (list);

        int index4;
        printf("Enter index whose data you want to remove: ");
        scanf("%d", &index4);
        list = delIdx(list, index4);
        printList(list);

        printf("Using recurtion printing the forward list: \n");
        printRec(list);

        printf("\nUsing recurtion printing the reverse order list: \n");
        printRevRec(list);

        int key2;
        printf("\nEnter key value that you want to delet: ");
        scanf("%d", &key2);
        list = remKey(list, key2);
        printList(list);

        int n1;
        printf("Enter number of elements for list1: ");
        scanf("%d", &n1);

        Node node1 = NULL;
        printf("Enter data elemnt for list1: \n");
        for(i=0; i<n1; i++){
                scanf("%d", &temp);
                node1 = addFirst(node1, temp);
        }
        printList(node1);

        int n2;
        printf("Enter number of elements for list2: ");
        scanf("%d", &n2);

        Node node2 = NULL;
        printf("Enter data element for list2: \n");
        for(i=0; i<n2; i++){
                scanf("%d", &temp);
                node2 = addFirst(node2, temp);
        }
        printList(node2);

        printf("After merging lists: \n");
        Node node3 = mergList(&node1, &node2);
        printList(node3);

        printf("After the sorting of merged list: \n");
        Node nex = sortList(node3);
        printList(nex);

        Node list2 = NULL;

        int n4;
        printf("Enter number of elements for sorted list: ");
        scanf("%d", &n4);

        printf("Enter data element for ""sorted"" list: \n");
        for(i=0; i<n4; i++){
                scanf("%d", &temp);
                list2 = addFirst(list2, temp);
        }
        printList(list2);
        int data5;
        printf("Enter data that you want to insert in ""sorted"" list: ");
        scanf("%d", &data5);
        list2 = insertSort(list2, data5);
        printList(list2);

        // printf("Your sorted list: \n");
        // list = sortList(list);
        // printList(list);

        printf("Reversed list using another list: \n");
        list = reversListAnother(list);
        printList(list);

        printf("Reversed list without using another list: \n");
        list = reversList(list);
        printList(list);

        printf("Reversed list using recursion list: \n");
        list = reversList(list);
        printList(list);

        return 0;
}
