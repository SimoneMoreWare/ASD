#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

typedef struct {
    char *s;
    int pos;
    int costo;
} part;

void solve(char *target,part P[10], int nParts);
void powerset_combsempl(int pos,int start,int *sol,char *target,part P[10],int nParts,int k,int *best,int *blocchi,int *costominimo);
int check(int *sol,int k,char *target, part P[10]);

int main(){
    char target[] = "persona";
    part P[10] = {
            {"p", 0, 1}, // p0
            {"pers", 0, 5}, // p1
            {"er", 1, 4}, // p2
            {"ers", 1, 4}, // p3
            {"sa", 3, 1}, // p4
            {"so", 3, 2}, // p5
            {"ato", 0, 1}, // p6
            {"on", 4, 2}, // p7
            {"ona", 4, 3}, // p8
            {"a", 6, 1} // p9
    };
    int nParts=10;
    solve(target,P,nParts);
    return 0;
}

void solve(char *target, part P[10], int nParts){
    int start=0;
    int pos=0;
    int *sol=(int *) malloc(nParts*sizeof(int));
    int i;
    int *best=(int *) malloc(nParts*sizeof(int));
    int blocchi=0;
    int costominimo = INT_MAX;
    for(i=1;i<=nParts;i++) powerset_combsempl(pos,start,sol,target,P,nParts,i,best,&blocchi,&costominimo);

    if(blocchi==0){
        printf("Non ci sono soluzioni");
    }else{
        printf("Costo minimo: %d\n",costominimo);
        for(i=0;i<blocchi;i++) printf("%s ",P[best[i]].s);
    }
    free(sol);
    free(best);
}

void powerset_combsempl(int pos,int start,int *sol,char *target,part P[10],int nParts,int k,int *best,int *blocchi,int *costominimo){

    int i;
    int costoparziale=0;
    if(pos>=k){
        if(check(sol,k,target,P)){
            for(i=0;i<k;i++) costoparziale = costoparziale + P[sol[i]].costo;
            if(costoparziale==(*costominimo) && k>(*blocchi)){
                (*blocchi)=k;
                for(i=0;i<k;i++) best[i]=sol[i];
            }
            if(costoparziale<(*costominimo)){
                (*blocchi)=k;
                (*costominimo)=costoparziale;
                for(i=0;i<k;i++) best[i]=sol[i];
            }
        }
    }

    for(i=start;i<nParts;i++){
        sol[pos]=i;
        powerset_combsempl(pos+1,i+1,sol,target,P,nParts,k,best,blocchi,costominimo);
    }
}

int check(int *sol,int k,char *target, part P[10]){

    int i,j;
    int t=0;
    int len=0;
    for(i=0;i<k;i++){
        for(j=0;j<strlen(P[sol[i]].s);j++){
            len++;
            if(t<strlen(target)) if(P[sol[i]].s[j]!=target[t++]) return 0;
        }
    }
    if(len!=strlen(target)) return 0;
    return 1;
}
