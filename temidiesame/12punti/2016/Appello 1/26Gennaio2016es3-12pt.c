#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 30

void decomponiR(int pos, int start, int n, char *str, int *sol, int *lungh, int l);
void decomponi(char *str, int num, int *lungh);
int checkSol(int n, int *sol, int l);

int main()
{
    char str[MAX] = "tentativo";
    int num = 3, *lungh;

    lungh = malloc(num*sizeof(int));
    lungh[0] = 2;
    lungh[1] = 5;
    lungh[2] = 7;

    decomponi(str,num,lungh);

    return 0;
}

int checkSol(int n, int *sol, int l){
    int i,sum=0;

    for(i=0;i<n;i++){
        sum+=sol[i];
    }

    if(sum == l)
        return 1;
    return 0;
}

void decomponiR(int pos, int start, int n, char *str, int *sol, int *lungh, int l){
    int i,j = 0,sum = 0;

    if(pos==n){
       if(checkSol(n,sol,l)){
            printf("Soluzione: { ");
            for(i=0;i<n;i++)
                printf("%d ",sol[i]);
            printf("}\n");

            printf("Decomposizione: ");
            for(i=0;i<n;i++){
                while(j<sol[i]+sum){
                    printf("%c", str[j]);
                    j++;
                }
                printf(" ");
                sum+=sol[i];
            }
       }
        return;
    }

    for(i=start;i<n;i++){
        sol[pos] = lungh[i];
        decomponiR(pos+1,start,n,str,sol,lungh,l);
        start++;
    }
}

void decomponi(char *str, int num, int *lungh){
    int *sol;
    char l = strlen(str);

    sol = malloc(num*sizeof(int));

    decomponiR(0,0,num,str,sol,lungh,l);

    return;
}
