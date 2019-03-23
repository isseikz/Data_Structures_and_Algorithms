#include "stdio.h"
#include "stdlib.h"

void main() {
  int data = 0;
  int *data_p = &data;
  int **data_pp = &data_p;
  printf("%d\n", data_pp);
  printf("%d\n", data_p);
  printf("%d\n", &data);
  printf("%d\n", *data_p);
  printf("%d\n", *data_pp);
}
