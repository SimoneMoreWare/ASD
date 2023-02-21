#include <stdio.h>
#include <stdlib.h>
#define N 5

void triangolo(int *a);
void triangolo_ricorsione(int *a, int n);

void triangolo_inverso(int *a);
void triangolo_inverso_ricorsione(int *a, int n);

int main() {
  int a[N] = {1, 2, 3, 4, 5};

  printf("triangolo\n");
  triangolo(a);
  printf("\n");
  triangolo_inverso(a);  
  return 0;
}

void triangolo(int *a) {
  int n=N;
  triangolo_ricorsione(a, n);
  return;
}

void triangolo_ricorsione(int *a, int n) {
  int i, x, tmp[N];
  if (n < 1)
	return;

  for (i=0; i<n-1; i++) {
    x = a[i] + a[i+1];
    tmp[i] = x;
  }

  for (i=0; i<n ; i++) {
    if(i == n-1)
      printf("%d ",a[i]);
    else
      printf("%d, ",a[i]);
  }
  printf("\n");

  triangolo_ricorsione(tmp, n-1);

}

void triangolo_inverso(int *a) {
  int n=N;
  triangolo_inverso_ricorsione(a, n);
  return;
}

void triangolo_inverso_ricorsione(int *a, int n) {
  int i, x, tmp[N];
  if (n < 1)
	return;

  for (i=0; i<n-1; i++) {
    x = a[i] + a[i+1];
    tmp[i] = x;
  }

  triangolo_inverso_ricorsione(tmp, n-1);
  
  for (i=0; i<n ; i++) {
    if(i == n-1)
      printf("%d ",a[i]);
    else
      printf("%d, ",a[i]);
  }
  printf("\n");

}
