#include <stdio.h>

int Factorial(int n){
  if (n==0) return 1;
  if (n==1) return 1;
  else return n*Factorial(n-1);
}

int main() {
  int i, res;

  printf("Please input an integer here. ");
  scanf("%d", &i);
  res = Factorial(i);
  printf("%d! = %d",i, res);
  return 0;
}
