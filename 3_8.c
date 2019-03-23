#include <stdio.h>
#include <stdlib.h>

typedef struct CLLNode {
  int data;
  struct CLLNode *next;
};

int CircularListLength(struct CLLNode *head) {
  struct CLLNode *current = head;
  int count = 0;
  if (head == NULL) {
    return 0;
  }

  do {
    current = current -> next;
    count ++;
  } while((current != NULL) && current != head);
  return count;
}

int DisplayCLL(struct CLLNode *head) {
  struct CLLNode *current = head;
  int count = 0;
  if (head == NULL) {
    return 0;
  }

  do {
    printf("%d\n", current -> data);
    current = current -> next;
  } while((current != NULL) && current != head);
  return count;
}

int DisplayCLL_n(struct CLLNode *head, int number) {
  struct CLLNode *current = head;
  int count = 0;
  if (head == NULL) {
    return 0;
  }

  int k = 0;
  do {
    printf("%d\n", current -> data);
    current = current -> next;
    k ++;
  } while((current != NULL) && k < number);
  return count;
}

void InsertAtEndInCLL(struct CLLNode **head, int data) {
  struct CLLNode *newNode, *current;
  current = *head;
  newNode = (malloc(sizeof(struct CLLNode)));
  if (!newNode) {
    printf("Memory error\n");
    return;
  }
  newNode -> data = data;

  while ((current -> next != NULL) && (current -> next != *head)) {
    current = current -> next;
  }
  newNode -> next = *head;
  current -> next = newNode;
  return;
}

void DeleteLastNodeFromCLL(struct CLLNode **head) {
  struct CLLNode *temp = *head;
  struct CLLNode *current = *head;
  if (*head == NULL) {
    printf("List Empty.");
    return;
  }
  while (current -> next != *head) {
    temp = current;
    current = current -> next;
  }
  temp -> next = current -> next;
  free(current);
  return;
}

void DeleteFrontNodeFromCLL(struct CLLNode **head) {
  struct CLLNode *temp = *head;
  struct CLLNode *current = *head;
  if (*head = NULL) {
    printf("List Empty.");
    return;
  }

  while (current -> next == *head) {
    current = current -> next;
  }
  current -> next = *head -> next;
  *head = *head -> next;
  free(temp);
  return;
}

void main() {
  struct CLLNode node = {0};
  node.data = 1;
  printf("%d\n", node.data);

  int len = CircularListLength(&node);
  printf("length: %d\n", len);

  struct CLLNode *addr = &node;
  InsertAtEndInCLL(&addr, 3);
  InsertAtEndInCLL(&addr, 4);
  DisplayCLL_n(addr, 10);
  return;
}
