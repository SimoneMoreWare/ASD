#include <stdio.h>
#include <stdlib.h>

#define filename "../mat.txt"

void separa(int **matrix,int nr,int nc,int *casellenere,int *casellebianche, FILE *fpin);
int **malloc2dr(int nr,int nc, FILE *fpin);
void free2dr(int **matrix,int nr);
void stampacaselle(int *casellenere,int *casellebianche,int dimcasellenere,int dimcasellebianche);

int main(){
    FILE *fpin;
    int nr,nc;
    int *casellenere,*casellebianche;
    int **matrix=NULL; //creo un vettore "verticale" di puntatori, ogni casella puntatore a un vettore
    fpin= fopen(filename,"r");
    if(fpin!=NULL){
        fscanf(fpin,"%d",&nr);
        fscanf(fpin,"%d",&nc);
        casellenere=(int *) malloc((((nr*nc)+1)/2)*sizeof(int));
        casellebianche=(int *) malloc((((nr*nc)+1)/2)*sizeof(int));
        separa(matrix,nr,nc,casellenere,casellebianche,fpin);
        stampacaselle(casellenere,casellebianche,((nr*nc)+1)/2,(nr*nc)/2);
        free(casellenere);
        free(casellebianche);
    }
    fclose(fpin);
    return 0;
}

void separa(int **matrix,int nr,int nc,int *casellenere,int *casellebianche,FILE *fpin){
    int i,j;//con i vedo le caselle nere dove si trovano ved j vedo le colonne bianche dove si trovano
    int count=0;
    int index_riga_nere,index_colonna_nere,index_riga_bianche,index_colonne_bianche;
    int dimensione_scacchiera=nr*nc;
    matrix= malloc2dr(nr,nc,fpin);

    /*stampa matrix
    for(i=0;i<nr;i++){
        for(j=0;j<nc;j++){
            printf("%d ",matrix[i][j]);
        }
        printf("\n");
    }*/

    //riempo vettore caselle nere e bianche, sapendo che sono alternate
    for(i=0;i<dimensione_scacchiera;i=i+2){
        index_riga_nere=i/nr;
        index_colonna_nere=i%nc;
        casellenere[count]=matrix[index_riga_nere][index_colonna_nere];
        count++;
    }
    count=0;
    for(j=1;j<dimensione_scacchiera;j=j+2){
        index_riga_bianche=j/nr;
        index_colonne_bianche=j%nc;
        casellebianche[count]=matrix[index_riga_bianche][index_colonne_bianche];
        count++;
    }
    free2dr(matrix,nr);
}

int **malloc2dr(int nr,int nc, FILE *fpin){
    int **creatematrix;
    int i,j;
    creatematrix=(int **) malloc(nr*sizeof(int *)); //creo vettore "verticale" di puntatore, ogni casella punterà a un vettore
    for(i=0;i<nr;i++) {
        creatematrix[i] = (int *) malloc(nc * sizeof(int));//per ogni casella del vettore verticale preparo lo spazio di memoria per il vettore
        for (j = 0; j < nc; j++) {
            fscanf(fpin,"%d",&creatematrix[i][j]); // inserisco valore
        }
    }

    /*
    for(i=0;i<nr;i++){

        }
    }*/ //inserire dopo i valori va bene?

    return creatematrix; //ritorno doppio puntatore (aka matrice) alla funzione chiamante

}

void free2dr(int **matrix,int nr){
    int i;
    for(i=0;i<nr;i++){
        free(matrix[i]);
    }
    free(matrix);
}

void stampacaselle(int *casellenere,int *casellebianche,int dimcasellenere,int dimcasellebianche){
    int i;

    //da ricordarsi che le dimensioni dei neri e bianchi potrebbe differire se la nr*nc è dispari (di 1 valore)

    //caselle nere
    printf("Caselle nere: ");
    for(i=0;i<dimcasellenere;i++) printf("%d ",casellenere[i]);
    printf("\n");
    //caselle bianche
    printf("Caselle bianche: ");
    for(i=0;i<dimcasellebianche;i++) printf("%d ",casellebianche[i]);
}
