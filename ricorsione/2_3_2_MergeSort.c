void Merge(int *val, int l, int q, int r) {
  int i, j, k, len, *B;

  len = r - l +1;
  B = malloc(len *sizeof(int));
  i = l;
  j = q+1;

  for (k = l; k <= r; k++)
    if (i > q)
      B[k] = val[j++];
    else if (j > r)
      B[k] = val[i++];
    else if (( val[i] < val[j]) || (val[i] == val[j]))
      B[k] = val[i++];
    else
      B[k] = val[j++];
  for (k = l; k <= r; k++)
    val[k] = B[k];
  return;
}

void MergeSort(int *val, int l, int r) {
  int q, i;

  if (r <= l)
    return;

  q = (l + r)/2;
  MergeSort(val, l, q);
  MergeSort(val, q+1, r);
  Merge(val, l, q, r);
}

