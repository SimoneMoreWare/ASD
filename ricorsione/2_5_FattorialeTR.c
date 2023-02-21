long fact_tr(int n, long f) {
  if(n == 0) 
    return f;
  return fact_tr(n-1, n*f);
}
