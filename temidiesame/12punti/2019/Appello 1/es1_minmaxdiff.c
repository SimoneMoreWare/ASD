#include <stdio.h>
#include <limits.h>

int minmaxdiff(int A[4][3], int n, int m);
int abs(int a);

int main(){
    int A[4][3] = {
          {15,13,7},
          {6,18,4},
          {11,4,12},
          {13,9,5}
    };
    int n=4;
    int m=3;
    int rescolonna;
    rescolonna=minmaxdiff(A,n,m);
    printf("%d",rescolonna);
    return 0;
}

int abs(int a){
    if(a<0) return (-1)*a;
    return a;
}

int minmaxdiff(int A[4][3], int n, int m){

	int i,j;
	int maxdiff=INT_MIN;
	int min_res=INT_MAX;
	int diff;
	int rmbcolonna;
        for(j=0;j<m;j++){
		maxdiff=INT_MIN;
		for(i=0;i<n-1;i++){
			//itero su ogni colonna
			diff=abs(A[i][j]-A[i+1][j]);
			if(diff>maxdiff) maxdiff=diff;
		}
		if(maxdiff<min_res){
			min_res=maxdiff;
			rmbcolonna=j;
		}
	}
	return rmbcolonna;
}
