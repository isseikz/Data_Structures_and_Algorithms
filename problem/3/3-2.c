#include "stdio.h"
#include "stdlib.h"

// 連結リストの最後からn番目のノードを見つける

typedef struct linked_list {
  int data;
  struct linked_list *next;
} LinkedList;

int len(LinkedList *head) {
  int cnt = 0;
  while (head) {
    cnt ++;
    head = head -> next;
  }
  return cnt;
}

void push(LinkedList **head, int data) {
  LinkedList *list = malloc(sizeof(LinkedList));
  list -> data = data;

  if (*head == NULL) {
    list -> next = NULL;
  } else {
    list -> next = *head;
  }
  *head = list;
  return;
}

void disp_list(LinkedList *head) {
  LinkedList *list = head;
  while (list) {
    printf("%d\n", list -> data);
    list = list -> next;
  }
}

LinkedList *find_nth_node_from_last(int n, LinkedList *list) {
  int length = 0;
  length = len(list);
  int nth = length - n - 1;
  if (nth > 0) {
    for (size_t i = 0; i < nth; i++) {
      list = list -> next;
    }
    return list;
  } else {
    return NULL;
  }
}

void main(){
  LinkedList *node = NULL;
  // printf("%d\n", *node);
  push(&node, 1);
  push(&node, 2);
  push(&node, 0);
  printf("%d\n", node -> data);
  printf("%d\n", len(node));

  LinkedList *nth_node = NULL;
  nth_node = find_nth_node_from_last(2, node);
  printf("%d\n", nth_node -> data);
  return;
  // push(&list, 2);
  // push(&list, 3);
  // int l = len(list);
  // disp_list(list);
  // printf("%d\n", l);
}
