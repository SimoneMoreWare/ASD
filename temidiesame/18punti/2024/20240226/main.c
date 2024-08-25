#include <stdio.h>
#include "ACT.h"
#define nomeFile "input.txt"
#define DBG_LETTURA
#define DBG_VINCOLI
#define DBG_BESTSEL
int main() {
    ACT a;
    FILE *fp;
    fp = fopen(nomeFile, "r");
    if(fp == NULL){
        printf("Errore nell'apertura del file!\n");
        exit(1);
    }
    a = activityRead(fp);
#ifdef DBG_LETTURA
    for(int i=0;i< ACTgetN(a);i++){
        ACTprintAtt(i,a);
    }
#endif
#ifdef DBG_VINCOLI
    char **sequenza;
    sequenza = (char**)malloc(3*sizeof(char*));

    for(int i=0;i<3;i++){
        sequenza[i] = (char*)malloc(MAXC*sizeof(char));
    }
    strcpy(sequenza[0],"Act1");
    strcpy(sequenza[1],"Act2");
    strcpy(sequenza[2],"Act3");
    printf("La sequenza ritorna : %d", checkSelection(a,sequenza,3));
#endif
#ifdef DBG_BESTSEL
    char **bestNomi;
    int nSel,maxProf;
    bestNomi = (char**)malloc(ACTgetN(a)*sizeof(char*));
    for(int i=0;i< ACTgetN(a);i++){
        bestNomi[i] = (char*)malloc(ACTgetN(a)*sizeof(char));
    }
    maxProf = bestSelection(a,bestNomi,&nSel);

    printf("\nMigliore soluzione: ( ");
    for(int i=0;i<nSel;i++){
        printf("%s ", bestNomi[i]);
    }
    printf("), Profitto: %d\n", maxProf);
    for(int i=0;i< ACTgetN(a);i++){
        free(bestNomi[i]);
    }
    free(bestNomi);
#endif
    fclose(fp);
    ACTdealloc(a);
    return 0;
}
