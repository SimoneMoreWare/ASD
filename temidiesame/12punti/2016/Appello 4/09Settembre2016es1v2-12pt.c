#include <stdio.h>

#define R 3
#define C 4

int subMatMax(int mat[R][C], int r, int c, int n);

int main(int argc, char **argv){
	int mat[R][C] = 
	{
		{5, 2, 3, 1},
		{3, 1, 6, 4},
		{3, 0, 5, 2}
	};
	
	printf("%d\n", subMatMax(mat, R, C, 2));
	
	return 420;
}

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
