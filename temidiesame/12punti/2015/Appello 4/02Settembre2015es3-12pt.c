#include <stdio.h>
#include <stdlib.h>

#define N 3
#define M N

void bestPath(int x, int y, int step, int* path, int* bestLen, int* bestVal, int* bestPathS, int maxX, int maxY, int values[N][M], int mark[N][M]);

int main(int argc, char **argv)
{
	int values[N][M] = 
	{ {1, 2, -3}, {9, -9, 7}, {0, 1, 4}};
	int mark[N][M] = {0};
	int path[N*M] = {0}; int bestPathS[N*M] = {0};
	int bestLen = N*M+1, bestVal = -1;
	
	bestPath(0, 0, 0, path, &bestLen, &bestVal, bestPathS, N, M, values, mark);
	
	printf("Soluzione: ");
	for(int i=0; i<bestLen; i++) printf("%d ", bestPathS[i]);
	printf("\n");
	printf("Somma: %d Lunghezza: %d\n", bestVal, bestLen);
	
	return 420;
}

void bestPath(int x, int y, int step, int* path, int* bestLen, int* bestVal, int* bestPathS, int maxX, int maxY, int values[N][M], int mark[N][M]){
	int i, val;
	if (x == maxX)
		if (y == maxY){
			// Vedere se la cosa migliora
			val = 0;
			for(i=0; i<step; i++) val += path[i];
			if (val > *bestVal || (val == *bestVal && step < *bestLen) ){
				*bestVal = val;
				*bestLen = step;
				for(i=0; i<step; i++) bestPathS[i] = path[i];
			}
			return;
		}
	if (x < 0) return;
	if (y < 0) return;
	if (x > maxX) return;
	if (y > maxY) return;
	if (mark[y][x] == 0){
		mark[y][x] = 1;
		path[step] = values[y][x];
		bestPath(x+1, y, step+1, path, bestLen, bestVal, bestPathS, maxX, maxY, values, mark);
		bestPath(x, y+1, step+1, path, bestLen, bestVal, bestPathS, maxX, maxY, values, mark);
		bestPath(x-1, y, step+1, path, bestLen, bestVal, bestPathS, maxX, maxY, values, mark);
		bestPath(x, y-1, step+1, path, bestLen, bestVal, bestPathS, maxX, maxY, values, mark);
		
		bestPath(x+1, y+1, step+1, path, bestLen, bestVal, bestPathS, maxX, maxY, values, mark);
		bestPath(x+1, y-1, step+1, path, bestLen, bestVal, bestPathS, maxX, maxY, values, mark);
		bestPath(x-1, y+1, step+1, path, bestLen, bestVal, bestPathS, maxX, maxY, values, mark);
		bestPath(x-1, y-1, step+1, path, bestLen, bestVal, bestPathS, maxX, maxY, values, mark);
		mark[y][x] = 0;
	}
}
