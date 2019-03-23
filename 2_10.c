#include <stdio.h>

char A[1000];

void Binary(int n){
  if (n < 1) {
    printf("%s\n", A);
  } else {
    A[n-1] = '0';
    Binary(n - 1);
    A[n-1] = '1';
    Binary(n - 1);
  }
}

void k_string(int n, int k){
  if (n < 1) {
    printf("%s\n", A);
  } else {
    for (int i = 0; i < k; i++) {
      A[n-1] = '1' + i;
      k_string(n-1, k);
    }
  }
}

int main() {
  int n;

  scanf("%d", &n);

  printf("Binary strings:\n");
  Binary(n);
  printf("kstrings:\n");
  k_string(n, n);
  return 0;
}
