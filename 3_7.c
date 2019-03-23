#include <stdio.h>
#include <stdlib.h>

struct DLLNode {
  int data;
  struct DLLNode *next;
  struct DLLNode *prev;
};  //struct 型の指定には";"が必要

void DLLInsert(struct DLLNode **head, int data, int position) {
  int k = 1;
  struct DLLNode *temp, *newNode;
  newNode = malloc(sizeof (struct DLLNode));
  if (!newNode) {
    printf("Memory Error\n"); return;
  }
  newNode -> data = data;
  if (position == 1) {
    newNode -> next = *head;
    newNode -> prev = NULL;
    if (*head) (*head) -> prev = newNode;
    *head = newNode;
    return;
  }


  temp = *head;
  while (( k < position-1) && temp -> next != NULL) {
    temp = temp -> next;
    k++;
  }
  if (k != position-1) {
    printf("Desired position does not exist\n");
  }

  newNode -> next = temp -> next;
  newNode -> prev = temp;
  if (temp -> next) {
    temp -> next -> prev = newNode;
    temp -> next = newNode;
  }
  return;

}

void DLLDelete(struct DLLNode **head, int position) {
  struct DLLNode *temp, *temp2;
  temp = *head;
  int k = 1;
  if (*head == NULL) {
    printf("List is empty\n");
    return;
  }

  if (position == 1) {
    *head = (*head) -> next;
    if (*head != NULL) {
      (*head) -> prev = NULL;
      free(temp);
      return;
    }
  }

  while ((k < position -1 ) && temp -> next != NULL) {
    temp = temp -> next;
    k++;
  }
  if (k != position -1 ) {
    printf("Desired position does not exist.\n");
  }

  temp2 = temp -> next;
  temp -> next = temp -> next -> next;
  if (temp -> next != NULL) {
    temp -> next -> prev = temp;
  }
  free(temp2);

  return;
}

void main() {
  struct DLLNode node0 = {0};
  node0.data = 1;
  struct DLLNode *addr = &node0;
  DLLInsert(&addr, 2, 1);
  DLLInsert(&addr, 3, 2);
  DLLInsert(&addr, 4, 2);

  struct DLLNode *current = addr;
  while (current) {
    printf("%d\n", current -> data);
    current = current -> next;
  }

  DLLDelete(&addr, 2);
  current = addr;
  while (current) {
    printf("%d\n", current -> data);
    current = current -> next;
  }


  return;
}
