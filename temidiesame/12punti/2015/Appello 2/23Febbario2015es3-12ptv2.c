#include <stdio.h>
#include <stdlib.h>

void generatePassword(char* passw, int* rip, int k, int pos);

int main(int argc, char **argv)
{
	char* passw = malloc(5*sizeof(char));
	int* rip = calloc(36, sizeof(int));
	int maxRip = 2;
	printf("Genero le password...\n");
	generatePassword(passw, rip, maxRip, 0);
	printf("Termino esecuzione.\n");
	printf("hello world\n");
	return 0;
}


void generatePassword(char* passw, int* rip, int k, int pos){
	int i;
	if(pos >= 5){
		for(i=0; i<5; i++) printf("%c", passw[i]);
		printf("\n");
		return;
	}
	if (pos < 3){
		for(i='A'; i <= 'Z'; i++){
			if(rip[i-'A']+1 <= k){
				rip[i-'A']++;
				passw[pos] = i;
				generatePassword(passw, rip, k, pos+1);
				rip[i-'A']--;
			}
		}
	} else {
		for(i='0'; i <= '9'; i++){
			if(rip['Z'+i+1]+1 <= k){
				rip['Z'+i+1]++;
				passw[pos] = i;
				generatePassword(passw, rip, k, pos+1);
				rip['Z'+i+1]--;
			}
		}
	}
}
