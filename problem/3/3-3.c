// 問題3-2の計算量を改善できるか
// 連結リストの最後からn番目のノードを見つける

#include <stdio.h>
#include <stdlib.h>

typedef struct list {
  struct list *next;
  int data;
} List;

void add_value(List **list, int position, int value) {
  printf("add value %d into %d th node.\n", value, position);
  if (position == 0) {
    List *new_list = (List *)malloc(sizeof(List));
    new_list -> next = *list;
    new_list -> data = value;
    *list = new_list;
    return;
  }

  int id = 0;
  List *head = *list;
  while (head -> next) {
    id = id + 1;
    if (id == position) {
      break;
    }
    head = head -> next;
  }

  List *inserted_node = (List *)malloc(sizeof(List));
  inserted_node -> next = head -> next;
  inserted_node -> data = value;
  head -> next = inserted_node;
  return;
}

int len(List *node){
  int cnt = 0;
  while(node){
    cnt ++;
    node = node -> next;
  }
  printf("length of the list is %d\n", cnt);
  return cnt;
}

void display_list(List *node){
  printf("--- display_list ---\n");
  List *head = node;
  while (head != NULL) {
    printf("%d\n", head -> data);
    head = head -> next;
  }
}

void main() {
  // create linked list
  List *my_list = (List *)malloc(sizeof(List));
  my_list -> next = NULL;
  my_list -> data = 0;

  display_list(my_list);
  add_value(&my_list, 1, 1);
  add_value(&my_list, 100, 2);
  add_value(&my_list, 1, 3);
  add_value(&my_list, 100, 4);
  for (int i = 5; i < 11; i++) {
    add_value(&my_list, 100, i);
  }
  display_list(my_list);

  // create hash table
  const int l = len(my_list);
  List *hash[l];
  List *head = my_list;
  for (int i = 0; i < l; i++) {
    hash[i] = head;
    head = head -> next;
  }

  // get nth element from the last
  int N = 3;
  int length = sizeof(hash) / sizeof(List *);
  int ans = hash[length - N -1] -> data;
  printf("%d th element from the last is %d\n", N, ans);
  return;
}
