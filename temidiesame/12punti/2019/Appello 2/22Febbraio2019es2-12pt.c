#include <stdio.h>
#include <stdlib.h>
#include <float.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

#define k 3

typedef struct nodo nodo_t;
typedef nodo_t *link;

int maxSum(link root, float *maxwt);
float somma(link root);

struct nodo {
	int id;
	float wid;
	int nc;
	link children[k];
	float sum;
};

int main(int argc, char *argv[]) 
{
	int id;
	float max;
	
	nodo_t n00 = { 0, 15.2, 3};
	nodo_t n01 = { 1, -8.1, 2};
	nodo_t n02 = { 2, 3, 1};
	nodo_t n03 = { 3, 7.27, 1};
	nodo_t n04 = { 4, -20.9, 0};
	nodo_t n05 = { 5, -4, 0};
	nodo_t n06 = { 6, 5.3, 2};
	nodo_t n07 = { 7, -10.8, 3};
	nodo_t n08 = { 8, 2.4, 0};
	nodo_t n09 = { 9, -5, 0};
	nodo_t n10 = {10, -3.1, 0};
	nodo_t n11 = {11, 2, 0};
	nodo_t n12 = {12, 2.8, 0};
		
	n00.children[0] = &n01;	
	n00.children[1] = &n02;	
	n00.children[2] = &n03;	
	n01.children[0] = &n04;	
	n01.children[1] = &n05;	
	n02.children[0] = &n06;	
	n03.children[0] = &n07;	
	n06.children[0] = &n08;	
	n06.children[1] = &n09;	
	n07.children[0] = &n10;	
	n07.children[1] = &n11;	
	n07.children[2] = &n12;	

	somma(&n00);
	printf("\n\n");

	//max = n00.sum;
	max = -FLT_MAX;
	id = maxSum(&n00, &max);
	
	printf("ID della radice dell'albero di peso massimo (%.2f): %d\n\n", max, id);
	
	system("pause");
	return 0;
}

int maxSum(link root, float *maxwt)
{
	int i, id, t;
	float s;
	
	//printf("id: %d --> peso %.2f\n", root->id, root->sum);
	id = root->id;
	if (root->sum > *maxwt) {
		*maxwt = root->sum;
		//printf("nuovo id: %d --> nuovo peso %.2f\n", root->id, root->sum);
	}
	for (i=0; i<root->nc; i++) {
		s = *maxwt;
		t = maxSum(root->children[i], maxwt); 
		if (*maxwt > s) {
			id = t;
		}
	}
	return id;
}

float somma(link root)
{
	int i;
	float s;
	
	s = 0;
	for (i=0; i<root->nc; i++) {
		s += somma(root->children[i]); 
	}
	s += root->wid;
	root->sum = s;
	//printf("id: %d --> peso %.2f\n", root->id, s);
	return s;
}
