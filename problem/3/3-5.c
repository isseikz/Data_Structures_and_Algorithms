// 問題3-2を1回の走査で解けるか

#include <stdio.h>
#include <stdlib.h>

typedef struct linked_list{
  struct linked_list *next;
  int data;
} List;

void add_data(List **node, int position, int data) {
  List *inserted_node = (List *)malloc(sizeof(List));
  inserted_node -> data = data;

  if (0 == position) {
    inserted_node -> next = *node;
    *node = inserted_node;
    return;
  }

  List *head = *node;
  int id = 0;
  while (head -> next) {
    id ++;
    if (id == position) {
      break;
    }
    head = head -> next;
  }
  inserted_node -> next = head -> next;
  head -> next = inserted_node;
  return;
}

void display_list(List *list){
  List *head = list;
  while (head) {
    printf("%d\n", head -> data);
    head = head -> next;
  }
}

void main(){
  List *list = (List *)malloc(sizeof(List));
  list -> data = 0;
  for (int i = 1; i < 10; i++) {
    add_data(&list, 5, i);
  }
  display_list(list);

  int N = 5;

  List *pNthNode = list;
  List *pTemp = list;
  int cnt = 0;
  while (pTemp) {
    pTemp = pTemp -> next;
    if (cnt > N) {
      pNthNode = pNthNode -> next;
    } else {
      cnt ++;
    }
  }
  printf("%d th node from the last is %d", N, pNthNode -> data);
  return;
}
