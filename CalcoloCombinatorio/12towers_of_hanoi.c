#include <stdio.h>

void Hanoi(int n, int src, int dest);

int main() {
  int n, src, dest;

  printf("Towers of Hanoi\n");
  printf("Insert number of disks: ");
  scanf("%d" , &n);
  printf("Insert source  peg (0/1/2): ");
  scanf("%d" , &src);
  printf("Insert destination peg (0/1/2): ");
  scanf("%d" , &dest);

  Hanoi(n , src, dest );

  return 0;
}


void Hanoi(int n, int src, int dest) {
  int aux;

  aux = 3 - (src + dest);

  if (n == 1) {
    printf("src %d -> dest %d \n", src, dest);
    return;
  }

  Hanoi(n-1, src, aux);

  printf("src %d -> dest %d \n", src, dest);

  Hanoi(n-1, aux, dest);
}

