#include <stdio.h>
#include <stdlib.h>
#define MAX_LENGTH_NAME_FILE 30
#define N_CHARS 26
#define N_NUMBERS 10

void generatePassword(FILE *f, int pos, char *chars, char *numbers, char *sol, int *mark_numbers, int *mark_chars, int k);

int main()
{
    char nomeFile[MAX_LENGTH_NAME_FILE], *sol;
    int *mark_chars, *mark_numbers,i,k=2;
    char numbers[N_NUMBERS] = {'1','2','3','4','5','6','7','8','9','0'};
    char chars[N_CHARS] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
    FILE *fp;

    sol = malloc(5*sizeof(char));
    mark_chars = malloc(N_CHARS*sizeof(char));
    mark_numbers = malloc(N_NUMBERS*sizeof(char));

    for(i=0; i<N_CHARS; i++){
        mark_chars[i] = 0;
    }

    for(i=0; i<N_NUMBERS; i++){
        mark_numbers[i] = 0;
    }

    printf("Inserisci nome del file: ");
    scanf("%s", nomeFile);

    fp = fopen(nomeFile,"w");
    generatePassword(fp,0,chars,numbers,sol,mark_numbers,mark_chars,k);
    fclose(fp);
    return 0;
}

void generatePassword(FILE *f, int pos, char *chars, char *numbers, char *sol, int *mark_numbers, int *mark_chars, int k){
    int i;

    if(pos==5){
        for(i=0; i<5; i++)
            fprintf(f,"%c", sol[i]);
        fprintf(f,"\n");
        return;
    }

    //insert chars in the first 3 positions
    if(pos >= 0 && pos <= 2){
        for(i=0; i<N_CHARS;i++){
            if(mark_chars[i]<k){
                mark_chars[i]++;
                sol[pos]=chars[i];
                generatePassword(f,pos+1,chars,numbers,sol,mark_numbers,mark_chars,k);
                mark_chars[i]--;
            }
        }
    //insert numbers in the last 2 positions
    }else if(pos >= 3 && pos < 5){
        for(i=0; i<N_NUMBERS;i++){
            if(mark_numbers[i]<k){
                mark_numbers[i]++;
                sol[pos]=numbers[i];
                generatePassword(f,pos+1,chars,numbers,sol,mark_numbers,mark_chars,k);
                mark_numbers[i]--;
            }
        }
    }
    return;
}
