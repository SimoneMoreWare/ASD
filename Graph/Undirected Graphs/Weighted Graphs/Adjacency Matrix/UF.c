#include <stdlib.h>
#include "UF.h"

static int *id, *sz;
static int find(int x);

void UFinit(int N) {
  int i;
  id  = malloc(N*sizeof(int));
  sz  = malloc(N*sizeof(int));
  for(i=0; i<N; i++) {
    id[i] = i;
    sz[i] = 1;
  }
}

void UFfree() {
  free(id);
  free(sz);
}

int UFfind(int p, int q) {
  return(find(p) == find(q));
}

static int find(int x) {
  int i = x;
  while (i!= id[i])
    i = id[i];
  return i;
}

void UFunion(int p, int q) {
  int i = find(p), j = find(q);
  if (i == j)
    return;
  if (sz[i] < sz[j]) {
    id[i] = j;
    sz[j] += sz[i];
  }
  else {
    id[j] = i;
    sz[i] += sz[j];
  }
}
