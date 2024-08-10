#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Node_t* Node;
typedef struct book_t* Book;
typedef struct student_t* Student;

struct book_t {
    int ukey; 
    char *issn;
    char *name;
};

struct student_t {
    int roll; 
    char *name; 
};

struct Node_t{
    void *data;
    Node next;
};

Node newNode(Node node, void *data){
    Node new = (Node) calloc(1, sizeof(struct Node_t));
    new->data = data;
    new->next = node;

    return new;
}

Node addFirst(Node node, void *data){
    return newNode(node, data);
}

Book addBook(int uKey, char *issNo, char *bookName){   
    Book book = (Book) calloc(1, sizeof(struct book_t));
    book->ukey = uKey;
    book->issn = (char *) calloc((strlen(issNo) + 2), sizeof(char));
    strcpy(book->issn, issNo);
    book->name = (char *) calloc((strlen(bookName) + 1), sizeof(char));
    strcpy(book->name, bookName);

    return book;
}

Student addStudents(int roll, char* name){
    Student student = (Student) calloc(1, sizeof(struct student_t));
    student->roll = roll;
    student->name = (char *) calloc((strlen(name)+1), sizeof(char));
    strcpy(student->name, name);

    return student;
}

Node addIthIndex(Node node, int index, void *data){
    if(!node || index == 0)
        return newNode(node, data);

    Node temp = node, p = NULL;
    for(int i = 0; i < index; i++){
        p = temp;
        temp = temp->next;
    }

    if(temp){
        Node new = newNode(temp->next, data);
        temp->next = new;
    }
    else{
        Node new = newNode(p->next, data);
        p->next = new;
    }

    return node;
}

Node deleteIthLoc(Node node, int index){
    if(!node)
        return NULL;

    Node p = node;
    for(int i = 0; i < index - 1; i++)
        p = p->next;

    Node q = p->next;
    p->next = q->next;
    free(q);

    return node;
}

int countList(Node node){
    if(!node)
        return 0;
    
    int count = 0;
    Node temp = node;
    for(; temp; temp = temp->next)
        count++;
    
    return count;
}

void printList(Node node, void (*printFunc)(void *)){
    if(!node)
        return;

    Node temp = node;
    for(; temp->next; temp = temp->next){
        printFunc(temp->data);
        printf("\t\t->\t\t");
    }
    
    printFunc(temp->data);
}

void printBook(void *data){
    Book book = (Book) data;
    printf("ukey: %d, ISSN: %s, Name: %s", book->ukey, book->issn, book->name);
}

void printStudent(void *data){
    Student student = (Student) data;
    printf("Roll: %d, Name: %s", student->roll, student->name);
}

void getDataIth(Node node, int index, void (*printFunction)(void *)){
    if(!node)   
        return ;
    
    Node temp = node;
    for(int i = 0; i < index; i++){
        temp = temp->next;
    }

    printFunction(temp->data);
    return ;
}

int compareBook(void* a, void* b){
    Book book1 = (Book) a;
    Book book2 = (Book) b;

    return book1->ukey - book2->ukey;
}

int compareStudent(void *a, void *b){
    Student student1 = (Student) a;
    Student student2 = (Student) b;

    return student1->roll - student2->roll;
}

int compareMemberVar(void* a, void* b, char* memberName){
    if (strcmp(memberName, "ukey") == 0) {
        return compareBook(a,b);
    } 
    else if (strcmp(memberName, "issn") == 0) {
        Book book1 = (Book) a;
        Book book2 = (Book) b;
        return strcmp(book1->issn, book2->issn);
    } 
    else if (strcmp(memberName, "name") == 0) {
        Book book1 = (Book) a;
        Book book2 = (Book) b;
        if (book1->name && book2->name) {
            return strcmp(book1->name, book2->name);
        } 
        else {
            printf("Error: Name is NULL\n");
            return 0;
        }
    } 
    else if (strcmp(memberName, "name") == 0) {
        Student student1 = (Student) a;
        Student student2 = (Student) b;
        if (student1->name && student2->name) {
            return strcmp(student1->name, student2->name);
        } 
        else {
            printf("Error: Name is NULL\n");
            return 0;
        }
    } 
    else if (strcmp(memberName, "roll") == 0) {
        return compareStudent(a,b);
    }
    else {
        printf("Invalid member variable.\n");
        return 0;
    }

}

Node insertInSorted(Node node, void* key, int (*compareFunction)(void *, void *), char* memberName){
    if(!node)
        return addFirst(node, key);

    Node temp = node;
    Node p = NULL;

    while(temp && compareMemberVar(key, temp->data, memberName) > 0){
        p = temp;
        temp = temp->next;
    }

    if(!p){ 
        return newNode(node, key);;
    }

    p->next = newNode(temp, key);
    return node;
}

Node sortList(Node node, int (*compareFunction)(void *, void *), char* memberName){
    if(!node)
        return NULL;
    
    Node temp = node;
    Node sorted = NULL;
    for(; temp; temp = temp->next)
        sorted = insertInSorted(sorted, temp->data, compareFunction, memberName);

    return sorted;
}

int main(){
    Node bookList = NULL;
    Node studentList = NULL;

    int choice, numBook, numStudents;
    char bookName[100], studentName[100], issn[20];

    printf("Enter number of books: ");
    scanf("%d", &numBook);

    for(int i = 0; i < numBook; i++){
        printf("\nEnter details for Book %d: \n", i + 1);
        printf("Unique Key: ");
        scanf("%d", &choice);

        printf("ISSn: ");
        scanf("%S", issn);

        printf("Name: ");
        scanf("%s", bookName);

        bookList = addIthIndex(bookList, i, addBook(choice, issn, bookName));
    }

    printf("Enter number of students: ");
    scanf("%d", &numStudents);

    for(int i = 0; i < numStudents; i++){
        printf("\nEnter details for Students %d:\n", i+1);
        printf("Roll: ");
        scanf("%d", &choice);

        printf("Name: ");
        scanf("%s", studentName);

        studentList = addIthIndex(studentList, i, addStudents(choice, studentName));
    }

    int index;
    do{
        printf("\nOperations:\n");
        printf("1. Insert Book/Student\n");
        printf("2. Delete Book/Student\n");
        printf("3. Get Book/Student\n");
        printf("4. Print Book List\n");
        printf("5. Print Student List\n");
        printf("6. Sort Book List\n");
        printf("7. Sort Student List\n");
        printf("8. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice){
            case 1:
                printf("Insert Book(1) or Student(2) ? ");
                scanf("%d", &choice);

                if(choice == 1){
                    printf("Enter Unique Key: ");
                    scanf("%d", &choice);

                    printf("Enter ISSN: ");
                    scanf("%S", issn);

                    printf("Enter Name: ");
                    scanf("%s", bookName);

                    printf("Enter index to insert: ");
                    scanf("%d", &index);
                    bookList = addIthIndex(bookList, index, addBook(choice, issn, bookName));
                }
                else if(choice == 2){
                    printf("Enter Roll: ");
                    scanf("%d", &choice);

                    printf("Enter Name: ");
                    scanf("%s", studentName);

                    printf("Enter index to insert: ");
                    scanf("%d", &index);
                    studentList = addIthIndex(studentList, index, addStudents(choice, studentName));
                }
                else{
                    printf("Invalid choice!\n");
                }
                break;
            
            case 2:
                printf("Delete Book(1) or Student(2) ? ");
                scanf("%d", &choice);

                if(choice == 1){
                    printf("Enter index to delete: ");
                    scanf("%d", &index);

                    bookList = deleteIthLoc(bookList, index);
                }
                else if(choice == 2){
                    printf("Enter index to delete: ");
                    scanf("%d", &index);

                    studentList = deleteIthLoc(studentList, index);
                }
                else{
                    printf("Invalid choice!\n");
                }
                break;
            
            case 3:
                printf("Get Book (1) or Student (2)? ");
                scanf("%d", &choice);

                if(choice == 1){
                    printf("Enter index: ");
                    scanf("%d", &index);

                    getDataIth(bookList, index, printBook);
                }
                else if(choice == 2){
                    printf("Enter index: ");
                    scanf("%d", &index);

                    getDataIth(studentList, index, printStudent);
                }
                else{
                    printf("Invalid choice!\n");
                }
                break;
            
            case 4:
                printf("Book List:\n");
                printList(bookList, printBook);
                break;
            
            case 5:
                printf("Studet list:\n");
                printList(studentList, printStudent);
                break;
            
            case 6:
                printf("Sort Book List by:\n");
                printf("1. ukey\n");
                printf("2. issn\n");
                printf("3. name\n");
                printf("Enter your choice: ");
                scanf("%d", &choice);

                switch(choice){
                    case 1:{
                        Node list2 = sortList(bookList, compareBook, "ukey");
                        printf("Book List (sorted by ukey):\n");
                        printList(list2, printBook);
                        break;
                    }

                    case 2:{
                        Node list2 = sortList(bookList, compareMemberVar, "issn");
                        printf("Book List (sorted by issn):\n");
                        printList(list2, printBook);
                        break;
                    }

                    case 3:{
                        Node list2 = sortList(bookList, compareMemberVar, "name");
                        printf("Book List (sorted by name):\n");
                        printList(list2, printBook);
                        break;
                    }

                    default:
                        printf("Invalid choice!\n");
                }
                break;

            case 7:
                printf("Sort Student List by:\n");
                printf("1. roll\n");
                printf("2. name\n");
                printf("Enter your choice: ");
                scanf("%d", &choice);

                switch (choice) {
                    case 1:{
                        Node list3 = sortList(studentList, compareStudent, "roll");
                        printf("Student List (sorted by roll):\n");
                        printList(list3, printStudent);
                        break;
                    }

                    case 2:{
                        Node list3 = sortList(studentList, compareMemberVar, "name");
                        printf("Student List (sorted by name):\n");
                        printList(list3, printStudent);
                        break;
                    }

                    default:
                        printf("Invalid choice!\n");
                }
                break;

            case 8:
                printf("Exiting...\n");
                break;
            
            default:
                printf("Invalid choice!\n");
        }
    }while(choice != 8);

    return 0;
}