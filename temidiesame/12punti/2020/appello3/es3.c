#include <stdlib.h>
#include <stdio.h>

typedef struct{
    char name[100];
    int costo;
    int valore;
    int tipo;
    int quantita;
}oggetto;

int solve(oggetto oggetti[5],int n,int c);
void solve_r(int pos,int k,int *sol,oggetto oggetti[5],int n,int c,int costo,int *valoremassimo,int *best);
int check(int k,oggetto oggetti[5],int *sol);

int main(){
    int n=5;
    oggetto oggetti[5] = {
            {"uno",3,4,1,2},
            {"due",2,3,2,3},
            {"tre",4,5,3,1},
            {"quattro",1,2,4,2},
            {"cinque",5,7,5,1}
    };
    int c=10;
    int res;
    res=solve(oggetti,n,c);
    printf("%d",res);
    return 0;
}

int solve(oggetto oggetti[5],int n,int c){
    int *sol = (int *) calloc(n,sizeof(int));
    int *best = (int *) calloc(n,sizeof(int));
    int pos=0;
    int i;
    int costo=0,valore;
    int costotmp;
    int valoremassimo=0;
    for(i=1;i<=n;i++) solve_r(pos,i,sol,oggetti,n,c,costo,&valoremassimo,best);
    for(i=0;i<n;i++){
        if(best[i]!=0){
            costotmp=best[i]*oggetti[i].costo;
            valore=best[i]*oggetti[i].valore;
            printf("-%s costo:%d valore:%d tipo:%d quantita:%d-",oggetti[i].name,costotmp,valore,oggetti[i].tipo,best[i]);
        }
    }
    printf("\n");
    free(best);
    free(sol);
    return valoremassimo;
}

void solve_r(int pos,int k,int *sol,oggetto oggetti[5],int n,int c,int costo,int *valoremassimo,int *best){

    int i,j;
    int new_cost;
    int costoparziale,valoreparziale;
    if(pos>=k){
        costoparziale=0;
        for(i=0;i<k;i++){
                if(sol[i]!=0){
                    costoparziale = costoparziale + sol[i]*oggetti[i].costo;
                }
            }
            if(costoparziale<=c) {
                valoreparziale=0;
                for(j=0;j<k;j++){
                    if(sol[j]!=0){
                        valoreparziale=valoreparziale+sol[j]*oggetti[j].valore;
                    }
                }
                if((valoreparziale)>(*valoremassimo)){
                    (*valoremassimo)=valoreparziale;
                    for(j=0;j<k;j++) best[j]=sol[j];
                }
            }
        return;
    }

    for(i=0;i<=oggetti[pos].quantita;i++){
        new_cost=costo+i*oggetti[i].costo;
        if(new_cost<=c && check(pos,oggetti,sol)){
                sol[pos]=i;
                solve_r(pos+1,k,sol,oggetti,n,c,new_cost,valoremassimo,best);
        }
        }
}

int check(int k,oggetto oggetti[5],int *sol){
    int i,j;
    for(i=0;i<k;i++){
        for(j=i+1;j<k;j++){
            if(sol[i]!=0 && sol[j]!=0){
                if(oggetti[i].tipo==oggetti[j].tipo) return 0;
            }
        }
    }
    return 1;
}


