#include <stdio.h>
#include <stdlib.h>

void wrapper(int piattaforme[5],int P);
void powerset_combsempl(int pos,int k,int *sol,int piattaforme[5],int P,int *stop);
int check(int *sol,int P,int k);

int main(){
    int piattaforme[] = {2,2,3,2,1};
    int P = 5;
    wrapper(piattaforme,P);
    return 0;
}

void wrapper(int piattaforme[5],int P){
    int pos=0;
    int *sol = (int *) malloc(P*sizeof(int));
    int i;
    int stop=0;
    for(i=1;i<=P && stop==0;i++) powerset_combsempl(pos,i,sol,piattaforme,P,&stop);
    free(sol);
}

void powerset_combsempl(int pos,int k,int *sol,int piattaforme[5],int P,int *stop){

    int i;

    if((*stop)==1) return;

    if(pos>=k){ //riempito vettore sol 
        //for(i=0;i<k;i++) printf("%d ",sol[i]);
        if(check(sol,P,k)){
            (*stop)=1;
        }
        //printf("\n");
        return;
    }

    for(i=1;i<=piattaforme[pos];i++){ //itero per ogni piattaforma da 1 fino al max dei salti
        sol[pos]=i; //assegno valore salto
        powerset_combsempl(pos+1,k,sol,piattaforme,P,stop); //posizione piattaforma succesiva
    }

}

int check(int *sol,int P,int k){

    int i;
    int distanza=0;
    int printdistanza=0;
    for(i=0;i<k;i++){
        distanza=distanza+sol[i];
    }

    if(distanza==P-1){
        for(i=0;i<k;i++){
            printf("%d ",printdistanza);
            printdistanza=printdistanza+sol[i];
        }
        printf("%d",P-1);
    }
    if(distanza==P-1) return 1;
    return 0;
}
