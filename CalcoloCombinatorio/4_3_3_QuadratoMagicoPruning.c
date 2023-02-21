int generate_square_opt(int index) {

  int i, r, c, ret, en_rec;

  //caso terminale
  if (index == nMax) 
    return check_constraint(0,DIAG1);
  
  r = index/N;
  c = index%N;
 
  for (i=0; i<nMax; i++) {
    if (mark[i] == 0) {

      mark[i] = 1;
      square[r][c] = i+1;

      //pruning
      en_rec = 1;
      if (c == N-1)
	en_rec = en_rec && check_constraint(r,LINE);
      if (r == N-1) {
	en_rec = en_rec && check_constraint(c,COLUMN);
	if(c == 0)
	  en_rec = en_rec && check_constraint(0,DIAG2);
      }

      if (en_rec == 1)
	ret = generate_square_opt(index+1);

      if (en_rec == 0 || ret == 0) {
	//backtrack
	mark[i] = 0;
	square[r][c] = 0;
      }else
	return 1;

    }
  }

  return 0;
}
