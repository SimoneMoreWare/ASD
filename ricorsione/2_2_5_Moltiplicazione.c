long int product(int *x, int *y, int n) {
  int  i, term1, term2, term3;
  int  xs[MAX/2], xd[MAX/2], ys[MAX/2], yd[MAX/2];


  if (n > 1) {
    for (i = 0; i < n/2; i++) {
      xs[i] = x[i];
      ys[i] = y[i];
    }
    for (i = 0; i < n/2; i++) {
      xd[i] = x[i + n/2];
      yd[i] = y[i + n/2];
    }
    term1 = product(xs, ys, n/2);
    term2 = product(xs, yd, n/2) + product(xd, ys, n/2);
    term3 = product(xd, yd, n/2);

    return(term1 * pow(10, n) + term2 * pow (10, n/2) + term3);
  }
  else
    return (x[n-1]*y[n-1]);
}


