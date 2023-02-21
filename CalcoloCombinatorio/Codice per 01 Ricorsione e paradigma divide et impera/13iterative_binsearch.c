int BinSearch(int v[], int N, int k) {
  int m, found= 0, l=0, r=N-1;

  while(l <= r && found == 0){
    m = (l+r)/2;
    if(v[m] == k)
      found = 1;
    if(v[m] < k)
      l = m+1;
    else
      r = m-1;
  }
  if (found == 0)
    return -1;
  return m;
}

