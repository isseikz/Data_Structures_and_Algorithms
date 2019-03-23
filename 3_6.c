#include <stdio.h>
#include <stdlib.h>

struct ListNode{
  int data;
  struct ListNode *next;
};

int ListLength(struct ListNode *head) {
  struct ListNode *current = head;
  int count = 0;
  while (current != NULL){
    count++;
    current = current -> next;
  }
  return count;
}

void InsertInLinkedList (struct ListNode **head, int data, int position) {
  int k = 1;
  struct ListNode *p, *q, *newNode;
  newNode = malloc(sizeof(struct ListNode));
  if (!newNode) {
    printf("MemoryError\n");
    return;
  }
  newNode -> data = data;
  p = *head;

  if (position == 1 || p==NULL) {
    newNode -> next = p;
    *head = newNode;
  }
  else {
    while ((p != NULL) && (k<position)) {
      k++;
      q = p;
      p = p -> next;
    }
    q -> next = newNode;
    newNode -> next = p;
  }
}

void ShowLinkedList (struct ListNode *head) {
  struct ListNode *current = head;
  printf("---Show linked list---\n");
  while (current!=NULL) {
    printf("%d\n", current -> data);
    current = current -> next;
  }
}

void DeleteNodeFromLinkedList(struct ListNode **head, int position) {
  int k = 1;
  struct ListNode *p, *q;
  if (*head == NULL) {
    printf("ListEmpty\n");
    return;
  }
  p = *head; //引数に指定された連結リストを示すポインタ
  if (position == 1) {
    *head = (*head) -> next;
    free(p);
    return;
  }
  else {
    while ((p != NULL) && (k < position)){
      k++;
      q = p;
      p = p -> next;
    }
    if (p == NULL) {
      printf("Position does not exist\n");
    }
    else {
      q -> next = p -> next;
      free(p);
    }
  }
}

void DeleteLinkedList(struct ListNode **head) {
  struct ListNode *auxilaryNode, *iterator;
  iterator = *head;
  while (iterator) {
    auxilaryNode = iterator -> next;
    free(iterator);
    iterator = auxilaryNode;
  }
  *head = NULL;
}

void main() {
  int ans;
  struct ListNode node0 = {0}; //構造体の内容をバイナリの0で初期化(数値：0, ポインタ:NULL)
  struct ListNode node1 = {1, &node0};
  ans = ListLength(&node1);
  printf("%d\n", ans);

  struct ListNode *head = NULL;
  InsertInLinkedList(&head, 3, 1);
  InsertInLinkedList(&head, 4, 1);
  InsertInLinkedList(&head, 5, 1);
  ShowLinkedList(head);
  InsertInLinkedList(&head, 5, 2);
  InsertInLinkedList(&head, 5, 3);
  ShowLinkedList(head);

  DeleteNodeFromLinkedList(&head, 1);
  DeleteNodeFromLinkedList(&head, 1);
  DeleteNodeFromLinkedList(&head, 1);
  ShowLinkedList(head);

  DeleteLinkedList(&head);
  ShowLinkedList(head);

}
