#include <stdlib.h>
#include <stdio.h>

typedef struct hm_ {
  long val;
  int calc;
} hm;

long H(int n) {
  if (n==0)
    return 0;
  return n - H(H(H(n-1)));
}

long Hmemo(int n, hm *hmemo) {
  if (n==0) {
    hmemo[n].val  = 0;
	hmemo[n].calc = 1;
	return hmemo[n].val;
  }
  if (hmemo[n].calc==1)
    return hmemo[n].val;
  hmemo[n].val = n- Hmemo(Hmemo(Hmemo(n-1, hmemo), hmemo), hmemo);
  hmemo[n].calc = 1;
  return hmemo[n].val;
}

int main(int argc, char **argv) {
  int n = atoi(argv[1]), i;
  hm *hmemo;
  printf("approccio ricorsivo\n");
  for(i=0;i<=n;i++) printf("%ld ", H(i));
  printf("\n\n");
  printf("approccio con memoization\n");
  hmemo = calloc(n+1, sizeof(hm));
  for(i=0;i<=n;i++) Hmemo(i, hmemo);
  for(i=0;i<=n;i++) printf("%ld ", hmemo[i].val);
  printf("\n\n");
  return 0;
}
