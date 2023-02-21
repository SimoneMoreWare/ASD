#include <stdio.h>

#include "time.h"
#include "titoli.h"
#include "quotazioni.h"

#define NSCELTE 6
#define S 1

void printMenu(char **scelte, int* scelta);
void leggiFile(char *filename, titoli titoli);

int main(){
    char nomefile[256],cod[21],sdata[11],sdata2[11];
    char *scelte[] = {
            "0 - Uscita;",
            "1 - Acquisisci file;",
            "2 - Ricerca di un titolo;",
            "3 - Ricerca quotazione in data specifica;",
            "4 - Ricerca Massimo e minimo in un intervallo di date;",
            "5 - Ricerca massimo e minimo assoluto;"
    };
    int continua = 1,scelta;
    titoli titoli;
    titolo tmp;
    float min = 0, max = 0;
    quotazione q;
    titoli = titoliInit();
    leggiFile("F1.txt", titoli);
    leggiFile("F2.txt", titoli);
    leggiFile("F3.txt", titoli);
    titoliStore(stdout, titoli);
    do{
        printMenu(scelte,&scelta);
        switch(scelta){
            case 0:
                continua = 0;
                break;
            case 1:
                printf("Inserisci il nome di un file da acquisire: ");
                scanf("%s",nomefile);
                leggiFile(nomefile, titoli);
                printf("Situazione attuale: \n\n");
                titoliStore(stdout, titoli);
                break;
            case 2:
                printf("Inserisci il nome di un titolo:");
                scanf("%s",cod);
                tmp = titoliSearch(titoli, cod);
                titoloStore(stdout,tmp);
                break;
            case 3:
                printf("Inserisci un titolo: ");
                scanf("%s",cod);
                printf("Inserisci una data nel formato aaaa/mm/gg: ");
                scanf("%s",sdata);
                tmp = titoliSearch(titoli, cod);
                q = ricercaQuotazione(tmp, getData(sdata));
                quotazioneStore(stdout, q);
                break;
            case 4:
                printf("Inserisci un titolo: ");
                scanf("%s",cod);
                printf("Inserisci due date nel formato aaaa/mm/gg: ");
                scanf("%s %s",sdata, sdata2);
                tmp = titoliSearch(titoli, cod);
                titolominMaxRange(tmp, &min, &max, getData(sdata), getData(sdata2));
                printf("MIN: %.2f, MAX:%.2f\n", min, max);
                break;
            case 5:
                printf("Inserisci un titolo: ");
                scanf("%s",cod);
                tmp = titoliSearch(titoli, cod);
                titoloMinMax(tmp, &min, &max);
                printf("MIN: %.2f, MAX:%.2f\n", min, max);
                break;
            default:
                printf("Hai inserito un valore fuori dal range\n:");
                break;
        }

    }while(continua == 1);
}

void printMenu(char **scelte, int* scelta){
    int i;
    printf("\n\n");
    for(i=0; i<NSCELTE; i++)
        printf("%s\n",scelte[i]);
    printf("> ");
    scanf("%d",scelta);
}

void leggiFile(char *filename, titoli titoli){
    int i,n,qta;
    float val;
    char cod[21], data[11], ora[6];
    titolo t;
    FILE *fp;
    fp = fopen(filename, "r");
    if(fp == NULL)
        return;
    while(fscanf(fp, "%s %d\n", cod, &n) == 2){
        t = titoliSearch(titoli,cod);
        if(t == NULL){
            t = titoloNEW(cod);
            titoliInsert(titoli, t);
        }
        for(i=0; i<n; i++){
            fscanf(fp,"%s %s %f %d\n", data, ora, &val, &qta);
            titoloInsertTransazione(t, getData(data), val, qta);
        }
        titolobilancia(t,S);
    }
    fclose(fp);
}
