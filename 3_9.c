#include "stdio.h"
#include "stdlib.h"

typedef struct ListNode {
  int data;
  struct ListNode *ptrdiff;
} LIST_NODE;

void disp_list_node(LIST_NODE **head){
  if (head = NULL) {
    printf("Empty List");
  }
  LIST_NODE *current = *head;
  LIST_NODE *prev = NULL;
  while (current -> ptrdiff != NULL) {
    printf("%d", current -> data);
    current = prev ^ (current->ptrdiff);
    prev = current;
  }
}

void add_node(LIST_NODE **head, LIST_NODE **added_node){
  if (*head == NULL) {
    return;
  }
  LIST_NODE *current = *head;
  LIST_NODE *prev = NULL;
  while (current -> ptrdiff != NULL) {
    prev = current;
    current = current -> ptrdiff ^ prev;
  }
  current -> ptrdiff = *added_node;
  return;
}

// LIST_NODE nth_node(int n, LIST_NODE **head){
//   if (n == 0) {
//     return head;
//   }
//
//   LIST_NODE *current = *head->ptrdiff ^ NULL;
//   LIST_NODE *prev = *head;
//   for (size_t i = 1; i < n; i++) {
//     current = current -> ptrdiff ^ prev;
//   }
//   return current
// }

int main(int argc, char const *argv[]) {
  LIST_NODE node = {0};
  LIST_NODE *addr = &node;
  disp_list_node(&node);
  add_node(*addr, node);
  disp_list_node(&node);

  return 0;
}
