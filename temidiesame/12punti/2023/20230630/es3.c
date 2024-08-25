#include <stdio.h>
#include <stdlib.h>

void wrapper(int x,int *v,int d);
void algEr(int x,int pos,int m,int *sol,int *v,int d,int *stop);
int check(int *sol,int m,int *v,int d);


int main()
{
    int d=5;
    int v[5]={1,3,2,2,4};
    int x;

    printf("Inserisci x: ");
    scanf("%d",&x);

    wrapper(x,v,d);


    return 0;
}

void wrapper(int x,int *v,int d){
    int m=0;
    int *sol=malloc(d*sizeof(int));
    int pos=0;
    int stop=0;

    algEr(x,pos,0,sol,v,d,&stop);
    if(!stop){
        printf("Non esiste sol.");
    }

}


void algEr(int x,int pos,int m,int *sol,int *v,int d,int *stop){
    int i;

    if((*stop)==1)
        return;

    if(pos>=d){
        if(m==x){ //filtro
        if(check(sol,m,v,d)==1){
            (*stop)=1;
        }
        }
        return;
    }


    for(i=0;i<m;i++){
        sol[pos]=i;
        algEr(x,pos+1,m,sol,v,d,stop);
    }
    sol[pos]=m;
    algEr(x,pos+1,m+1,sol,v,d,stop);

}

int check(int *sol,int m,int *v,int d){
    int sommaSingolo=0;
    int sommacheck=0;
    int i,j;



    for(i=0;i<m;i++){
            sommacheck=0;
        for(j=0;j<d;j++){
            if(sol[j]==i){
                sommacheck=sommacheck+v[j];
            }
        }
        if(!sommaSingolo)
            sommaSingolo=sommacheck;
        else{
            if(sommaSingolo!=sommacheck)
                return 0;
        }

    }

    for(i=0;i<m;i++){
        printf("{ ");
        for(j=0;j<d;j++)
        if(sol[j]==i){
            printf("%d ",v[j]);
        }

        printf("}");
    }
    printf("\n");



    return 1;

}
