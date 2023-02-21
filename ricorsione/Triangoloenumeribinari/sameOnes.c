#include <stdio.h>
#include <stdlib.h>

int cnt(int *a, int l, int r) {
  int i, count=0;
  for (i=l; i<=r; i++)
    if (a[i]==1)
      count++;
  return count;
}

int check(int *a, int k) {
  int l=0, r=k-1, m= (l+r)/2, cnt1, cnt2;

  if ((k%2)==0){
    cnt1 = cnt(a, l, m);
    cnt2 = cnt(a, m+1, r);
  }
  else {
    cnt1 = cnt(a, l, m-1);
    cnt2 = cnt(a, m+1, r);
  }
  if (cnt1 == cnt2)
    return 1;
  else
    return 0;

}

void oneCntR(int *a, int pos, int k) {
  int j;
  if (pos >= k) {
    if (check(a, k) ==1) {
      printf("{ \t");
      for (j=0; j<k; j++)
        printf("%d \t", a[j]);
      printf("} \n");
    }
    return;
  }

  a[pos] = 0;
  oneCntR(a, pos+1, k);
  a[pos] = 1;
  oneCntR(a, pos+1, k);
  return;
}


void oneCnt(int N) {
  int *a;
  a = malloc(N*sizeof(int));
  oneCntR(a, 0, N);
  free(a);
}


int main() {
  int N;

  printf("Input N: ");
  scanf("%d", &N);

  oneCnt(N);

  return 0;
}
