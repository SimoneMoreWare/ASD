/*
 * nlogn se implemento la binary search ma non ingozza
 * ho usato la dinamic
 */

#include <stdio.h>
#include <stdlib.h>

#define filename "../log.txt"

typedef struct{
    int s;
    int f;
    int durata;
}att;

att* caricastruct(int *dim);
void attSel(int dim,att *attivita);
int comparator(const void* p0, const void* p1);
void predecessor(int **pred,att *attivita,int dim);
int massimo(int a,int b);
int main(){
    att *attivita=NULL;
    int dim;
    attivita=caricastruct(&dim);
    //for(int i=0;i<dim;i++) printf("%d %d\n",attivita[i].s,attivita[i].f);
    //INSERIRE ORDINAMENTO PER ESTREMO DI FINE
    qsort(attivita,dim,sizeof(att),comparator);
    for(int i=1;i<=dim;i++) printf("%d %d %d\n",attivita[i].s,attivita[i].f,attivita[i].durata);
    attSel(dim,attivita);
    free(attivita);//ricordati della free
    return 0;
}

att* caricastruct(int *dim){
    FILE *fp;
    att *vet;
    int i;
    fp=fopen(filename,"r");
    if(fp!=NULL){
        fscanf(fp,"%d\n",&(*dim));
        vet=(att *) malloc((*dim+1)*sizeof(att));
        for(i=1;i<=(*dim);i++){
            fscanf(fp,"%d %d",&(vet[i].s),&(vet[i].f));
            vet[i].durata=vet[i].f-vet[i].s;
        }
        //sentinel
        vet[0].s=vet[0].f=vet[0].durata=0;
    }else{
        printf("Errore file");
        exit(1);
    }
    fclose(fp);
    return vet;
}

int comparator(const void* p0, const void* p1){
    att* ps0 = (att*) p0;
    att* ps1 = (att*) p1;
    return ((ps0->f)>=(ps1->f));
}

void predecessor(int **pred,att *attivita,int dim){
    int i,j;
    (*pred)[0]=0;
    for(i=1;i<=dim;i++){
        j=i-1;
        while(j>0 && (attivita[i].s)<(attivita[j].f)) j=j-1;
        (*pred)[i]=j;
    }
}

void attSel(int dim,att *attivita){
    int *pred;
    int *dp;
    int *res;
    int k;
    int i;
    dp=(int*) calloc(dim,sizeof(int));
    pred=(int*) calloc(dim,sizeof(int));
    res=(int*) calloc(dim,sizeof(int));
    printf("\n");
    predecessor(&pred,attivita,dim);
    for(i=0;i<dim;i++) printf("%d %d\n",i,pred[i]);
    dp[0]=0;
    for(i=1;i<=dim;i++) dp[i]=massimo(dp[i-1],dp[pred[i]]+(attivita[i].durata));
    printf("\n");
    k=0;
    for(i=dim;i>0;){
        if(attivita[i].durata+dp[pred[i]]>=dp[i-1]){
            res[k]=i;
            k++;
            i=pred[i];
        }else{
            i--;
        }
    }
    for(i=k;i>=0;i--){
        if(attivita[res[i]].s!=0 && attivita[res[i]].f!=0) printf("%d %d\n",attivita[res[i]].s,attivita[res[i]].f);
    }
    free(dp);
    free(pred);
}

int massimo(int a,int b){
    return a>b ? a:b;
}
