int subMatMax(int mat[R][C], int r, int c, int n){
	int i, j, k, p, t, max = 0;
	
	for(i=0; i<=r-n; i++){
		for(j=0; j<=c-n; j++){
			t = 0;
			for(k=i; k<i+n; k++)
				for(p=j; p<j+n; p++)
					t+=mat[k][p];
			if (t > max) max = t;
		}
	}
	
	return max;
}
