#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define R 4
#define C 5

char** matrice();
int mat_search();

int main(int argc, char **argv)
{
	char* s = strdup("foo\0");
	char** mat = matrice(R, C);
	mat_search(mat, R, C, s);
	return 0;
}

int mat_search(char** mat, int r, int c, char* s){
	int i, j, k, count = 0;
	for(i=0; i<r; i++){
		for(j=0; j<c; j++){
			if (mat[i][j] == s[0]){
				for(k=i; s[k-i] != '\0' && s[k-i] == mat[k][j] && k < r; k++);
				if (s[k-i] == '\0') {
					printf("Occurrence @ (%d, %d) [Going Down]\n", i, j);
					count++;
				}
				for(k=j; s[k-j] != '\0' && s[k-j] == mat[i][k] && k < c; k++);
				if (s[k-j] == '\0'){
					printf("Occurrence @ (%d, %d) [Going Right]\n", i, j);
					count++;
				}
			}
		}
	}
	
	if (count == 0) printf("No occurrences found.\n");
	return count;
}

char** matrice(int r, int c){
	char** mat =  malloc(r*sizeof(char*));
	//for(int i=0; i<r; i++) mat[i] = malloc(c*sizeof(char));
	
	mat[0] = strdup("xfoox");
	mat[1] = strdup("yoxzf");
	mat[2] = strdup("xo2fo");
	mat[3] = strdup("g4xao");
	
	return mat;
}