/*
 * Z Z o R
 * S S o T
 * R S o T
 * T Z o R
 */

/*
 * calcolare lunghezza massima
 *
 * Tecniche: divide et impera + memorization
 *
 * Implementazione
 * Matrice quadridimensionale per salvare se ho gia trovato quella determinata configurazione di collana, altimenti -1
 * Chiamo funzione Fz
 * Decido quale gemma utilizzare per la posizione corrente
 *      ricorro in base alle disponibilità delle gemme e delle regole
 *          prima di ricorrere
 *              si verifica se la soluzione è stata gia calcolando vedendo la matrice quadridimensioanle
 *                  si ritorno valore in quella cella della matrice quadridimensionale
 *                  no ricorsione sulla gemma successiva compatibile (es fz, chiamo prima fz e poi fr)
 *                      chiamo la funzione con la gemma del tipo in esame decrementata
 *                          verifico tra le due soluzioni parziali delle funzioni chiamate qual è la massima è la salva nella matrice quadridimensuionale
 *                          backtrack, ritorno indietro e incremento la gemma di quel tipo in esame.
 *                      * chiamo singolarmente prima fz, poi fr,fs,ft e verifico man mano qual è la lunghezza massima trovata dalle rispettive funzioni.
 *      Condizione di terminazione
 *          quando non sono piu disponibili gemme del tipo in esame
 *      sottoproblema
 *          collana con z,r,t,s ancora disponobili
 *          soluzione
 *              memorizzata in una cella quadrimensionale
 *
 *
 */


#include <stdio.h>
#include <stdlib.h>

typedef enum {
    zaffiro,rubino,topazio,smeraldo
} Item;

//int disp_rip(int pos,int *val,int *sol,int n,int k,int prec, int found);
//int check(int prec,int att);
 //VARIABILE GLOBALE !!!!! so che tutte le funzioni hanno bisogno di vedere
int SolveM(int *val);
int ****malloc4d(int MAXZ,int MAXR,int MAXT,int MAXS);
int max(int a,int b);
int fz(int ****mz,int ****mr,int ****mt,int ****ms,int *val);
int fr(int ****mz,int ****mr,int ****mt,int ****ms,int *val);
int ft(int ****mz,int ****mr,int ****mt,int ****ms,int *val);
int fs(int ****mz,int ****mr,int ****mt,int ****ms,int *val);
void dealloca(int ****memoizationZ,int ****memoizationR,int ****memoizationT,int ****memoizationS,int maxZ,int maxR,int maxT);
int main(){
    FILE *fp;
    int lunghezza;
    int testcase;
    int i;
    int val[4];
    fp=fopen("../log.txt","r");
    if(fp!=NULL){
        fscanf(fp,"%d\n",&testcase);
        for(i=1;i<=testcase;i++){
            fscanf(fp,"%d %d %d %d",&val[zaffiro],&val[rubino],&val[topazio],&val[smeraldo]);
            lunghezza=SolveM(val);
            printf("Lunghezza test %d e' di : %d \n",i,lunghezza);
        }
    }else{
        printf("Errore file");
    }
    return 0;
}

int SolveM(int *val){
    int ****MemorizationZ;
    int ****MemorizationR;
    int ****MemorizationT;
    int ****MemorizationS;
    int lenmax,tmp;
    int MAXZ=val[zaffiro],MAXR=val[rubino],MAXT=val[topazio],MAXS=val[smeraldo];
    MemorizationZ=malloc4d(MAXZ,MAXR,MAXT,MAXS);
    MemorizationR=malloc4d(MAXZ,MAXR,MAXT,MAXS);
    MemorizationT=malloc4d(MAXZ,MAXR,MAXT,MAXS);
    MemorizationS=malloc4d(MAXZ,MAXR,MAXT,MAXS);
    //for(z=0;z<MAXZ;z++) for(r=0;r<MAXR;r++) for(t=0;t<MAXT;t++) for(s=0;s<MAXS;s++) printf("%d\n",MemorizationZ[z][r][t][s]=-1);
    lenmax=fz(MemorizationZ,MemorizationR,MemorizationT,MemorizationS,val);
    tmp=fr(MemorizationZ,MemorizationR,MemorizationT,MemorizationS,val);
    lenmax=max(lenmax,tmp);
    tmp=ft(MemorizationZ,MemorizationR,MemorizationT,MemorizationS,val);
    lenmax=max(lenmax,tmp);
    tmp=fs(MemorizationZ,MemorizationR,MemorizationT,MemorizationS,val);
    lenmax=max(lenmax,tmp);
    dealloca(MemorizationZ,MemorizationR,MemorizationT,MemorizationS,MAXZ,MAXR,MAXT);
    return lenmax;
    //inserisci free

}

int ****malloc4d(int MAXZ,int MAXR,int MAXT,int MAXS){
    int ****m;
    int z,r,t,s;
    m=(int ****) malloc((MAXZ+1)*sizeof(int ***));
    for(z=0;z<=MAXZ;z++){
        m[z]=(int ***) malloc((MAXR+1)*sizeof(int **));
        for(r=0;r<=MAXR;r++){
            m[z][r]=(int **) malloc((MAXT+1)*sizeof(int *));
            for(t=0;t<=MAXT;t++){
                m[z][r][t]=(int *) malloc((MAXS+1)*sizeof(int));
            }
        }
    }
    for(z=0;z<=MAXZ;z++) for(r=0;r<=MAXR;r++) for(t=0;t<=MAXT;t++) for(s=0;s<=MAXS;s++) m[z][r][t][s]=-1;
    return m;
}

int fz(int ****mz,int ****mr,int ****mt,int ****ms, int *val){
    int maxz,maxr;
    int resz;
    if(val[zaffiro]==0) return 0;
    if(mz[val[zaffiro]][val[rubino]][val[topazio]][val[smeraldo]]!=-1) return mz[val[zaffiro]][val[rubino]][val[topazio]][val[smeraldo]];
    val[zaffiro]--;
    maxz=fz(mz,mr,mt,ms,val);
    maxr=fr(mz,mr,mt,ms,val);
    val[zaffiro]++;
    resz=max(maxz,maxr)+1;
    mz[val[zaffiro]][val[rubino]][val[topazio]][val[smeraldo]]=resz;
    return resz;
}

int ft(int ****mz,int ****mr,int ****mt,int ****ms, int *val){
    int maxz,maxr;
    int rest;
    if(val[topazio]==0) return 0;
    if(mt[val[zaffiro]][val[rubino]][val[topazio]][val[smeraldo]]!=-1) return mt[val[zaffiro]][val[rubino]][val[topazio]][val[smeraldo]];
    val[topazio]--;
    maxz=fz(mz,mr,mt,ms,val);
    maxr=fr(mz,mr,mt,ms,val);
    val[topazio]++;
    rest=max(maxz,maxr)+1;
    mt[val[zaffiro]][val[rubino]][val[topazio]][val[smeraldo]]=rest;
    return rest;
}

int fr(int ****mz,int ****mr,int ****mt,int ****ms, int *val){
    int maxs,maxt;
    int resr;
    if(val[rubino]==0) return 0;
    if(mr[val[zaffiro]][val[rubino]][val[topazio]][val[smeraldo]]!=-1) return mr[val[zaffiro]][val[rubino]][val[topazio]][val[smeraldo]];
    val[rubino]--;
    maxs=fs(mz,mr,mt,ms,val);
    maxt=ft(mz,mr,mt,ms,val);
    val[rubino]++;
    resr=max(maxs,maxt)+1;
    mr[val[zaffiro]][val[rubino]][val[topazio]][val[smeraldo]]=resr;
    return resr;
}

int fs(int ****mz,int ****mr,int ****mt,int ****ms, int *val){
    int maxs,maxt;
    int ress;
    if(val[smeraldo]==0) return 0;
    if(ms[val[zaffiro]][val[rubino]][val[topazio]][val[smeraldo]]!=-1) return ms[val[zaffiro]][val[rubino]][val[topazio]][val[smeraldo]];
    val[smeraldo]--;
    maxs=fs(mz,mr,mt,ms,val);
    maxt=ft(mz,mr,mt,ms,val);
    val[smeraldo]++;
    ress=max(maxs,maxt)+1;
    ms[val[zaffiro]][val[rubino]][val[topazio]][val[smeraldo]]=ress;
    return ress;
}

int max(int a,int b){
    return a>b ? a:b;
}

void dealloca(int ****memoizationZ,int ****memoizationR,int ****memoizationT,int ****memoizationS,int maxZ,int maxR,int maxT){
    int i,j,k;
    for(i = 0; i <= maxZ; i++) {
        for(j = 0; j <= maxR; j++) {
            for(k = 0; k <= maxT; k++) {
                free(memoizationZ[i][j][k]);
                free(memoizationR[i][j][k]);
                free(memoizationT[i][j][k]);
                free(memoizationS[i][j][k]);
            }
            free(memoizationZ[i][j]);
            free(memoizationR[i][j]);
            free(memoizationT[i][j]);
            free(memoizationS[i][j]);
        }
        free(memoizationZ[i]);
        free(memoizationR[i]);
        free(memoizationT[i]);
        free(memoizationS[i]);
    }
    free(memoizationZ);
    free(memoizationR);
    free(memoizationT);
    free(memoizationS);
}


/*
int disp_rip(int pos,int *val,int *sol,int n,int k,int prec,int found){
    int i;
    if (pos >= k) {//terminazione
        for (i=0; i<k; i++) printf("%d ", sol[i]);
        printf("\n");
        return 1;
    }
    for (i = 0; i < n; i++) {//iterazioni sulle scelte
        if (val[i] > 0 && check(prec,i)) {//val non registra l uso o non l uso ma registra quante sono le sitanze disponibili da utilizzare, se c'è ne ancora una significa che la prendiamo
            val[i]--;//scelta decrementate
            sol[pos] = i;//scelta e poi vado sulla successiva
            if(disp_rip(pos+1, val, sol, n, k,i,found)) return 1;//backtrack implicit
            val[i]++;//fase backtrack, annullo ultima scelta, rimetto in gioco quella scelta, incremento il vettore val nella posizione i
        }
    }
    return 0;
}

int check(int prec,int att){
    if(prec==-1
       || ((prec==zaffiro) && (att==zaffiro || att==rubino))
       ||  ((prec==smeraldo) && (att==smeraldo || att==topazio))
       ||  ((prec==rubino) && (att==smeraldo || att==topazio))
       ||  ((prec==topazio) && (att==zaffiro || att==rubino))) return 1;
    return 0;
}*/
