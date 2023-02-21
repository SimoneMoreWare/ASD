int BinSearch(int v[], int l, int r, int k) {
  int m;

  while((r-l) != 0) {
    m = (l+r) / 2;
	if(v[m] >= k)
      r = m;
    else
      l = m+1;
  }

  if(v[l]==k)
    return l;
  else
    return -1;
}


