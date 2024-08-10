
struct Node {
  int data;
  struct Node* next;
  struct Node* prev;
};

void rectifyCircularList(struct Node* head) {

  if(head == NULL)
    return;

  struct Node *current = head;
  
  do {
    current->next->prev = current;  
    current = current->next; 
  } while(current->next != head);

  current->next = head;

  head->prev = current;

  current = head;
  do {
    current = current->prev;
  } while(current->prev != head);
  
  head = current;
}

