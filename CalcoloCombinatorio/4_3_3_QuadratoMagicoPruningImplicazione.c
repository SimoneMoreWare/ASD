int* sumR = NULL;
int* sumC = NULL;
int sumD1 = 0;
int sumD2 = 0;

int generate_square_impl(int index) {
    
  int r,c,i,imply;
    
  //caso terminale
  if (index == nMax)
    return (1);
  
  r = index/N;
  c = index%N;
  
  //implicazione su riga
  if ((r < N-1) && (c == N-1)) {
             
    if ((imply=imply_constraint(r,LINE)) == 0)
      return 0;
      
    assign_square(imply,r,c);
    
    if (generate_square_impl(index+1) == 0) {
      backtrack_square(imply,r,c);
      return 0;
    }else
      return 1;
  } 
  
  //implicazione su colonna
  if (r == N-1) {
             
    if ((imply=imply_constraint(c,COLUMN)) == 0)
      return 0;
    if (c == N-1) {
      if (imply!=imply_constraint(r,LINE) || 
          imply!=imply_constraint(0,DIAG1))   
        return 0;
    }
    if (c == 0) {
      if (imply!=imply_constraint(0,DIAG2))   
        return 0;
    }
    assign_square(imply,r,c);
    
    if (generate_square_impl(index+1) == 0) {
      backtrack_square(imply,r,c);
      return 0;
    }else
      return 1;
  } 

  for (i=0; i<nMax; i++) {
    if (mark[i] == 0) {
      
      assign_square(i+1,r,c);
    
      if (generate_square_impl(index+1) == 0) {
	backtrack_square(i+1,r,c);
      }else
	return 1;
    }
  }

  return 0;
}

void assign_square(int val, int r, int c) {
  
  square[r][c] = val;
  mark[val-1] = 1;
  
  sumR[r] += val;
  sumC[c] += val;
  
  if(r == c)
    sumD1 += val;
   
  if(r+c == N-1)
    sumD2 += val;
  
  return;
}


void backtrack_square(int val, int r, int c) {
  
  square[r][c] = 0;
  mark[val-1] = 0;
  
  sumR[r] -= val;
  sumC[c] -= val;
  
  if(r == c)
    sumD1 -= val;
  
  if(r+c == N-1)
    sumD2 -= val;

  return;
}

int imply_constraint(int rc, constraint ck) {

  int sum, n;

  switch(ck) {
    case LINE: 		sum = sumR[rc];	 break;
    case COLUMN: 	sum = sumC[rc];  break;
    case DIAG1: 	sum = sumD1; 	 break;
    case DIAG2: 	sum = sumD2; 	 break;
  }

  n = sumMax - sum;
  if (n <= 0 || n > nMax)
    return 0;
   
  return ((mark[n-1]==0) ? n : 0);
}
