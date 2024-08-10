void rotateList(struct Node** head, int n) {
   
   if(!*head || !(*head)->next) 
     return;

   int len = 1;
   struct Node* p = *head;
   while(p->next != NULL) {
     len++;
     p = p->next;
   }

   n = n % len;
   if(n == 0) 
     return;

   struct Node* current = *head;
   int count = 1;
   while(count < len - n) {
     current = current->next;
     count++;  
   }

   struct Node* nthNode = current;
   
   struct Node* newHead = nthNode->next;  
   nthNode->next = NULL;
   newHead->prev = NULL;

   p->next = *head;  
   (*head)->prev = p;
   *head = newHead;
}
