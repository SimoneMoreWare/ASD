int BinSearch(int *v, int a, int b, int k) {
  int c;

  if ((b-a) == 0)
    if (v[a]==k)
      return a;
	else
      return -1;

  c = (a+b) / 2;

  if(v[c] >= k)
    return(BinSearch(v, a, c, k));
  else
    return(BinSearch(v, c+1, b, k));
}
