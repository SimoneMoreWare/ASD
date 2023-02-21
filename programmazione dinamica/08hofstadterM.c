#include <stdlib.h>
#include <stdio.h>

typedef struct hm_ {
	int val, calc;
} hm;

int H(int n) {
  if (n == 0)
    return 0;
  return n - H(H(H(n-1)));
}

int Hmemo(int n, hm *hmemo) {
  if (n == 0) {
	hmemo[n].val  = 0;
	hmemo[n].calc = 1;
	return hmemo[n].val;
  }
  if (hmemo[n].calc == 1)
    return hmemo[n].val;
  hmemo[n].val = n- Hmemo(Hmemo(Hmemo(n-1, hmemo), hmemo), hmemo);
  hmemo[n].calc = 1;
  return hmemo[n].val;
}

int main() {
  int n, i;
  hm* hmemo;

  printf("Input n: ");
  scanf("%d", &n);

  printf("Hofstadter numbers: recursive version\n");
  for(i=0;i<=n;i++)
    printf("%d ", H(i));
  printf("\n\n");

  printf("Hofstadter numbers: version with memoization\n");
	hmemo = calloc(n+1, sizeof(hm));
	for(i=0;i<=n;i++)
      Hmemo(i, hmemo);
	for(i=0;i<=n;i++)
	  printf("%d ", hmemo[i].val);
	return 0;
}
