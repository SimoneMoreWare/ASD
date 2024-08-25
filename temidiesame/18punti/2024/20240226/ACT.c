#include "ACT.h"

struct activities{
    attivita *vettAttivita;
    int nAtt;
};

static ACT ACTinit(int nAtt);
static void bestSelectionR(ACT a, char **bestNomi, int *pNsel, char ** sol, int pos, int k, int *bestProf, int *mark);
static void sortSol(ACT a, char **bestNomi, int nSel);
static int partitionMod(char **bestNomi,int l,int r,ACT a);
static void QuickSortModR(char **bestNomi, int l, int r, ACT a);
static void SwapMod(char **bestNomi, int n1, int n2);
ACT activityRead(FILE *f){
    int nA,nP,i,j,k,index,stop;
    char tmp[20], carattere;
    ACT elencoAct;
    fscanf(f,"%d %d", &nA, &nP);
    elencoAct = ACTinit(nA);

    for(i=0;i<nA;i++){
        fscanf(f,"%s %d %d %d", elencoAct->vettAttivita[i].nome, &(elencoAct->vettAttivita[i].inizio), &(elencoAct->vettAttivita[i].durata), &(elencoAct->vettAttivita[i].valore));
    }
    for(i=0;i<nP;i++){
        fscanf(f,"%s", tmp);
        fscanf(f,"%c", &carattere); ///Aggiungo la lettura dello spazio dopo la stringa
        index = ACTfindByName(tmp, elencoAct);
        if(index == -1){
            printf("Attivita' a cui inserire vincoli inesistente!\n");
            exit(1);
        }
        stop=0;
        j=0;
        k=0; ///Aggiungo azzeramento di k
        while(!stop){
            if(j==2){
                stop = 1;
            }
            fscanf(f,"%c", &carattere);
            if(carattere == ' ' || carattere == '\n' || feof(f)){ ///Ho dimenticato di inserire il caso in cui la fscanf dovesse incontrare uno spazio e quando il file finisce, li aggiungo.
                tmp[k] = '\0'; ///Ho aggiunto l'inserimento del carattere di terminazione della stringa
                strcpy(elencoAct->vettAttivita[index].vincoli[j++],tmp); ///Nell'esame per una svista non ho usato strcpy, lo inserisco ora
                elencoAct->vettAttivita[index].nVin = j;
                k=0; ///Aggiungo l'azzeramento di k
                if(carattere == '\n' || feof(f)){
                    stop = 1;
                }
            }else{
                tmp[k++] = carattere;
            }
        }
    }
    return elencoAct;
}

static ACT ACTinit(int nAtt){
    ACT elencoAct;
    elencoAct = (ACT)malloc(sizeof(*elencoAct));
    elencoAct->vettAttivita = (attivita*)malloc(nAtt*sizeof(attivita));
    for(int i=0;i<nAtt;i++){ ///ho modificato elencoAct->nAtt con nAtt perchè in questo punto elencoAct->nAtt non è ancora stato riempito
        elencoAct->vettAttivita[i].nVin = 0;
    }
    elencoAct->nAtt = nAtt;
    return elencoAct;
}

int ACTfindByName(char *tmp, ACT elencoAct){
    int i;
    for(i=0; i<elencoAct->nAtt;i++){
        if(strcmp(elencoAct->vettAttivita[i].nome, tmp) == 0){
            return i;
        }
    }
    return -1;
}

int checkSelection(ACT a, char **selected, int nsel){
    int i,j,k, index1, index2, cnt;
    for(i=1;i<nsel;i++){
        index1 = ACTfindByName(selected[i],a);
        for(j=i-1; j>=0; j--){
            index2 = ACTfindByName(selected[j],a);
            //Per verificare la condizione di non intersezione suppongo che le attività non siano ordinate, se fossero ordinate basterebbe controllare la precedente
            if((a->vettAttivita[index1].inizio < a->vettAttivita[index2].inizio && ((a->vettAttivita[index1].inizio + a->vettAttivita[index1].durata) > a->vettAttivita[index2].inizio)) || (a->vettAttivita[index2].inizio < a->vettAttivita[index1].inizio && ((a->vettAttivita[index2].inizio + a->vettAttivita[index2].durata) > a->vettAttivita[index1].inizio))){
                //Controllo la presenza di un'intersezione tra le attività
                return 0;
            }
        }
    }
    //Condizione di precedenza, il ragionamento applicato a riguardo è meglio spiegato nella relazione
    for(i=0;i<nsel;i++){
        cnt=0; ///ho spostato l'azzeramento prima dell'if per non creare problemi nel caso in cui non siano presenti dei vincoli
        index1 = ACTfindByName(selected[i],a);
        if(a->vettAttivita[index1].nVin != 0){ //Se ha requisiti di precedenza
            for(j=0;j<a->vettAttivita[index1].nVin;j++){
                for(k=0;k<i && cnt < a->vettAttivita[index1].nVin; k++){ ///Ho modificato il limite superiore di k perchè deve arrivare a i-1 dato che gli elementi devono precedere l'indice i
                    if(strcmp(selected[k],a->vettAttivita[index1].vincoli[j]) == 0){
                        cnt++;
                    }
                }
            }
        }
        if(cnt != a->vettAttivita[index1].nVin){ //Se cnt non è verificato anche solo per un'attività allora la sequenza non è valida
            return 0;
        }
    }
    return 1;
}

int bestSelection(ACT a, char **bestNomi, int *pNsel){
    char **sol;
    int i,j, bestProf=0, *mark;
    mark = (int*)calloc(a->nAtt,sizeof(int));
    for(i=1;i<a->nAtt;i++){ ///Ho modificato lo start di i da 0 ad 1 perchè le disposizioni più piccole saranno su un elemento
        sol = (char**)malloc(i*sizeof(char*));
        for(j=0;j<i;j++){
            sol[j] = (char*)malloc(MAXC*sizeof(char)); ///Ho modificato i con j
        }
        bestSelectionR(a,bestNomi,pNsel,sol,0,i,&bestProf, mark);
        for(j=0;j<i;j++){
            free(sol[j]); ///ho modificato i con j
        }
        free(sol);
    }
    free(mark);
    sortSol(a,bestNomi,*pNsel);
    return bestProf;
}
static int calcolaProfitto(char **sol, ACT a, int k){
    int index, prof=0;
    for(int i=0; i<k; i++){
        index = ACTfindByName(sol[i],a);
        prof+=a->vettAttivita[index].valore;
    }
    return prof;
}

///Consultare relazione nella sezione relativa alle modifiche di bestSelection
static void bestSelectionR(ACT a, char **bestNomi, int *pNsel, char ** sol, int pos, int k, int *bestProf, int *mark){ ///Aggiunta del vettore mark
    int prof,i;
    if(pos>=k) {
        prof = calcolaProfitto(sol,a,k);
        if (prof > (*bestProf)){
            for(i=0;i<k;i++){
                strcpy(bestNomi[i],sol[i]);
            }
            *bestProf = prof; ///Ho aggiornato il miglior profitto
            *pNsel = k;
        }
        return;
    }
    for(i=0;i<a->nAtt;i++){
        if(mark[i] == 0) {
            strcpy(sol[pos],a->vettAttivita[i].nome); ///Per una svista ho utilizzato -> anche per il campo nome ma in realtà devo utilizzare il punto perchè vettAttivita[i] non è un puntatore a struct ma bensì una struct
            if(checkSelection(a,sol,pos+1)){ ///utilizzo pos+1 per includere anche l'attività appena inserita nel check
                mark[i] = 1;
                bestSelectionR(a,bestNomi,pNsel,sol,pos+1,k,bestProf, mark);
                mark[i] = 0;
            }
        }
    }
}


static void sortSol(ACT a, char **bestNomi, int nSel){
    QuickSortModR(bestNomi,0,nSel-1,a); ///ho corretto nSel con nSel-1
}

static void QuickSortModR(char **bestNomi, int l, int r, ACT a){ ///Aggiungo il parametro ACT a per sapere i tempi di inizio legati alle key
    int q;
    if(l>=r){
        return;
    }
    q=partitionMod(bestNomi, l, r, a);
    QuickSortModR(bestNomi, l, q-1, a);
    QuickSortModR(bestNomi, q+1, r, a);
}

static int partitionMod(char **bestNomi,int l,int r,ACT a){
    int i = l-1, j=r, index;

    index = ACTfindByName(bestNomi[r],a);
    int x = a->vettAttivita[index].inizio;
    for( ; ; ){
        while(a->vettAttivita[ACTfindByName(bestNomi[++i],a)].inizio < x);
        while(a->vettAttivita[ACTfindByName(bestNomi[--j],a)].inizio > x);
        if(i>=j){
            break;
        }
        SwapMod(bestNomi,i,j);
    }
    SwapMod(bestNomi,i,r);
    return i;
}

static void SwapMod(char **bestNomi, int n1, int n2){
    char tmp[MAXC];
    strcpy(tmp, bestNomi[n1]);
    strcpy(bestNomi[n1],bestNomi[n2]);
    strcpy(bestNomi[n2], tmp);
}
//Funzioni aggiuntive

int ACTgetN(ACT elencoAct){
    return elencoAct->nAtt;
}

void ACTprintAtt(int index, ACT a){
    printf("%s %d %d %d Vincoli: ", a->vettAttivita[index].nome, a->vettAttivita[index].inizio, a->vettAttivita[index].durata, a->vettAttivita[index].valore);
    if(a->vettAttivita[index].nVin == 0){
        printf("Vuoto");
    }
    for(int i = 0; i<a->vettAttivita[index].nVin;i++){
        printf("%s ", a->vettAttivita[index].vincoli[i]);
    }
    printf("\n");
}

void ACTdealloc(ACT a){
    free(a->vettAttivita);
    free(a);
}