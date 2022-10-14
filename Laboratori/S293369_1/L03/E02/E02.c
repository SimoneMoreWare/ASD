#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define filename "../brani.txt"
#define MAXNCHAR 256

typedef struct{
    char **scelte; //array di stringhe
    //*scelte[MAXN] NON va bene?
    int num_scelte;
}Livello;

void leggifile();
int principiodimoltiplicazione(int pos,Livello *val,char **sol,int n,int cnt);

int main(){
    leggifile();
    return 0;
}

void leggifile(){
    Livello *val; //struttura di tipo livello
    char **sol;//creo array di stringhe
    int n; //dimensione n (quante soluzioni ho)
    int pos=0; //posizione indice della ricorsione e soluzione parziale
    int cnt=0; //variabile per conteggio di tutte le soluzioni
    int i,j;
    FILE *fpin;
    fpin= fopen(filename,"r");
    if(fpin!=NULL){
        fscanf(fpin,"%d",&n);

        val=(Livello *) malloc(n* sizeof(Livello));

        sol=(char **) malloc(n* sizeof(char *));
        for(i=0;i<n;i++) sol[i]=(char *) malloc(MAXNCHAR*sizeof (char));

        for(i=0;i<n;i++){
            fscanf(fpin,"%d",&val[i].num_scelte);
            val[i].scelte=(char **) malloc(val[i].num_scelte*sizeof(char *));
            for(j=0;j<val[i].num_scelte;j++){
                val[i].scelte[j]=(char *) malloc(MAXNCHAR*sizeof(char));
                fscanf(fpin,"%s",val[i].scelte[j]);
            }
        }

        cnt= principiodimoltiplicazione(pos,val,sol,n,cnt);
        printf("%d",cnt);

        //inserisci free
        free(val->scelte);
        free(val);
        for(i=0;i<n;i++) free(sol[i]);
        free(sol);

    }else {
        printf("Errore file");
    }
    fclose(fpin);
}

//pos indice ricorsione e dimensione soluzione parziale
//struttura val , ho le scelte possibili insieme al numero di scelte
//sol, vettore di dimensione n che riempierò man mano nella ricerca di tutte le soluzioni
//n dimensione delle combinazioni
//cnt conteggio soluzioni

int principiodimoltiplicazione(int pos,Livello *val,char **sol,int n,int cnt){
    int i;
    if(pos>=n){//condizione di terminazione, significa che la mia posizione parziale ha oltreppasato l'array
        for(i=0;i<n;i++) printf("%s ",sol[i]);//stampo tutte le soluzioni che ho trovato (da 0 a n-1)
        printf("\n");
        return cnt+1;//soluzione trovata, ritorno cnt+1, "rifaccio il for"
    }
    for(i=0;i<val[pos].num_scelte;i++){//devo interare sul n.scelte in base alla posizione in cui mi trovo
        strcpy(sol[pos],val[pos].scelte[i]);//assegno al vettore sol nella posizione pos il valore che assume la struttura val nella posizione POS nel cassella i delle scelte possibili
        cnt=principiodimoltiplicazione(pos+1,val,sol,n,cnt);//mi sposto ricorsivamente nel vedere le soluzioni in pos+1
    }
    return cnt;

}
