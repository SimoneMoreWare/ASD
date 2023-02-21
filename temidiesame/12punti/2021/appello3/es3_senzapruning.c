#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *s;
    int pos;
    int costo;
} sub;

void solve(char *start, char *end, sub S[8], int nSubs);
void powerset_combsempl(int pos,int startComb,int *sol,int k,char *start,char *end,sub S[8],int nSubs,int *nsostituzioni,int *minimocosto,int *best);
int check(int *sol,int k,sub S[8],char *start,char *end);

int main(){
    char start[]="passato";
    char end[]="persona";
    int nSubs=8;
    sub S[8] = {
            {"er", 1, 4},
            {"ers", 1, 5},
            {"sa", 3, 1},
            {"so", 3, 2},
            {"ato", 0, 1},
            {"on", 4, 2},
            {"ona", 4, 3},
            {"a", 6, 1}
    };
    solve(start,end,S,nSubs);
    return 0;
}

void solve(char *start, char *end, sub S[8], int nSubs){
    int *sol = (int *) malloc(nSubs*sizeof(int));
    int pos=0;
    int startComb=0;
    int nsostituzioni=0;
    int i;
    int minimocosto=INT_MAX;
    int *best = (int *) malloc(nSubs*sizeof(int));
    for(i=nSubs;i>=1;i--) powerset_combsempl(pos,startComb,sol,i,start,end,S,nSubs,&nsostituzioni,&minimocosto,best);
    if(nsostituzioni==0){
        printf("Non è stato possibile trovare una soluzione");
    }else{
        printf("Costo migliore: %d\n",minimocosto);
        for(i=0;i<nsostituzioni;i++) printf("%s ",S[best[i]].s);
    }
    free(sol);
    free(best);
}

void powerset_combsempl(int pos,int startComb,int *sol,int k,char *start,char *end,sub S[8],int nSubs,int *nsostituzioni,int *minimocosto,int *best) {
    int i;
    int costoparziale;
    if(pos>=k){
        if(check(sol,k,S,start,end)){
            costoparziale=0;
            for(i=0;i<k;i++) costoparziale=costoparziale + S[sol[i]].costo;
            if(costoparziale==(*minimocosto) && k>(*nsostituzioni)){
                (*nsostituzioni) = k;
            }
            else if(costoparziale<(*minimocosto)){
                (*minimocosto) = costoparziale;
                (*nsostituzioni)=k;
                for(i=0;i<k;i++) best[i]=sol[i];
            }
        }
        return;
    }
    //potrei fare un pruning sul costo del sottoinsieme che sto costreundo?
 
    for(i=startComb;i<nSubs;i++){
        sol[pos]=i;
        powerset_combsempl(pos+1,i+1,sol,k,start,end,S,nSubs,nsostituzioni,minimocosto,best);
    }
}

int check(int *sol,int k,sub S[8],char *start,char *end){
    int i,j;
    char *tmp = (char *) malloc(strlen(start)*sizeof(char));
    strcpy(tmp,start);


    //S[sol[i]]

    for(i=0;i<k;i++){
        for(j=0;j<strlen(S[sol[i]].s);j++){
            tmp[S[sol[i]].pos+j] = S[sol[i]].s[j];
        }
    }

    if(strcmp(tmp,end)==0){
        free(tmp);
        return 1;
    }
    free(tmp);
    return 0;
}
