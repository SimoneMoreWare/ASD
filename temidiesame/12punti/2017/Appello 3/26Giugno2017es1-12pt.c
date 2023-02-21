#include <stdio.h>
#include <stdlib.h>

float my_atof(char* s);

int main(int argc, char **argv){
	char* s = malloc(10*sizeof(int));
	printf("Digitare il numero: ");
	scanf("%s", s);
	printf("Numero: %s\nNumero Convertito: %f\n",
	s, my_atof(s));
	
	return 420;
}

float my_atof(char* s){
	float my_float = 0, float_t;
	int pos;
	int exp;
	int i;
	for(pos = 1; s[pos] != '.'; pos++);
	for(exp = pos-1; exp > 0; exp--){
		float_t = (float)( (int)(s[pos-exp] - '0'));
		for(i=1; i < exp; i++) float_t *= 10;
		my_float += float_t;
	}
	
	pos++;
	exp = pos;
	while(s[pos] != '\0'){
		float_t = (float)( (int)(s[pos] - '0'));
		for(i=0; i<pos-exp+1; i++) float_t /= 10;
		my_float += float_t;
		pos++;
	}
	
	return s[0] == '+' ? my_float : -my_float;
}
