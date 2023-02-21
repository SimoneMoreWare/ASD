long fact(int n) {
  long tot = 1;
  int i;

  for (i = 2; i <= n; i++)
    tot = tot * i;

  return(tot);
}

long fib(int n) {
  long f1p = 1, f2p = 0, f;
  int i;

  if(n == 0 || n == 1)
    return(n);

  f = f1p + f2p; /* n==2 */

  for (i = 3; i <= n; i++) {
    f2p = f1p;
    f1p = f;
    f = f1p+f2p;
  }
  return(f);
}

int BinSearch(int *v, int a, int b, int k) {
  int c;

  while (b-a != 0) {
    c = (a + b) / 2;
	if(v[c] >= k)
      b = c;
    else
      a = c + 1;
  }

  if (v[a] == k)
    return a;
  else
    return -1;
}



