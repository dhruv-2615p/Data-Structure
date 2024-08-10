
struct Node {
  int data;
  struct Node* next;
  struct Node* prev;
};

void rectifyList(struct Node* head) {
  
  struct Node *current = head;
  
  if(head == NULL) {
    return; 
  }

  while(current->next != NULL) {
    struct Node* next = current->next;
    next->prev = current;
    current = next;
  }

  current->next = NULL; 
   
  current = head;
  
  while(current->prev != NULL) {
    current = current->prev;
  }
  
  current->prev = NULL;

  if(current != head) {
    head = current; 
  }
}

