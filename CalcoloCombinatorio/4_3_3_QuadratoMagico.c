int N = 0;
int nMax = 0;
int sumMax = 0;

int** square = NULL;
int* mark = NULL;

typedef enum check_kind{LINE, COLUMN, DIAG1, DIAG2} constraint;

int generate_square(int index) {

  int i, r, c, ret;

  //caso terminale
  if (index == nMax)
    return check_square();
  
  r = index/N;
  c = index%N;

  ret=0;
  for (i=0; i<nMax; i++) {
    if (mark[i] == 0) {

      mark[i] = 1;
      square[r][c] = i+1;
      ret = generate_square(index+1);

      if (ret == 0) {
	//backtrack
	mark[i] = 0;
	square[r][c] = 0;
      } else
	return 1;

    }
  }

  return 0;
}

int check_square(void) {

  int i, ret;

  ret = 1;
  for (i=0; i<N; i++) {
    ret = ret && check_constraint(i,LINE);
    ret = ret && check_constraint(i,COLUMN);
  }

  ret = ret && check_constraint(0,DIAG1);
  ret = ret && check_constraint(0,DIAG2);
 
  return ret;
}

int check_constraint(int rc, constraint ck) {
  
  int sum, i

  sum=0;
  for (i=0; i<N; i++) {
    switch(ck) {
      case LINE: 	sum += square[rc][i];    break;
      case COLUMN: 	sum += square[i][rc];    break;
      case DIAG1: 	sum += square[i][i];     break;
      case DIAG2: 	sum += square[i][N-1-i]; break;
    }
  }

  return ((sum==sumMax) ? 1 : 0);
}
