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

