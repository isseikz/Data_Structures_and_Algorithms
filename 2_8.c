#include <stdio.h>

int TowersOfHanoi(int n, char from, char to, char aux){
  if (n==1) {
    printf("Move disk 1 from peg %c to peg %c\n", from, to);
    return 0;
  }

  TowersOfHanoi(n-1, from, aux, to);

  printf("Move disk %d from peg %c to peg %c\n", n, from, to);

  TowersOfHanoi(n-1, aux, to, from);
}

int main(int argc, char const *argv[]) {
  int i;
  printf("Please input the number of disks. \n");
  scanf("%d", &i);

  char from = 'a';
  char to = 'b';
  char aux = 'c';

  TowersOfHanoi(i, from, to, aux);
  return 0;
}
