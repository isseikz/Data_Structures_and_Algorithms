#include <stdio.h>
#include <stdlib.h>

// 問題3-1 連結リストを使ってスタックを実装せよ
typedef struct stack {
  int data;
  struct stack *next;
} Stack;

Stack *CreateStack() {
  printf("Stack initialization\n");
  return NULL;
}

void Push(Stack **top, int data) {
  Stack *temp;
  temp = malloc(sizeof(Stack));
  if (!temp) return NULL;
  temp -> data = data;
  temp -> next = *top;
  *top = temp;
  printf("Push: %d\n", data);
}

int IsEmptyStack(Stack *top) {
  return top == NULL;
}

int Pop(Stack **top) {
  int res = 0;
  Stack *s;

  if (IsEmptyStack(*top)) return INT_MIN;
  s = *top;
  res = s -> data;
  *top = s -> next;
  return res;
}

void DispStack(Stack *top) {
  Stack *s = top;
  printf("---DispStack---\n");
  while (s) {
    printf("%d\n", s->data);
    s = s->next;
  }
  printf("---End of DispStack---\n\n");
}


void main() {
  Stack *s = CreateStack();
  printf("Shoud be INT_MIN: %d\n\n",Pop(&s));
  Push(&s, 1);
  Push(&s, 2);
  Push(&s, 3);
  Push(&s, 32);
  DispStack(s);
  int popped = Pop(&s);
  printf("Popped: %d\n", popped);
  DispStack(s);

  popped = Pop(&s);
  printf("Popped: %d\n", popped);
  DispStack(s);

  popped = Pop(&s);
  printf("Popped: %d\n", popped);
  DispStack(s);

  popped = Pop(&s);
  printf("Popped: %d\n", popped);
  DispStack(s);

  popped = Pop(&s);
  printf("Popped: %d\n", popped);
  DispStack(s);
}
