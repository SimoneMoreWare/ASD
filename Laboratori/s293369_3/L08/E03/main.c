/*
 * >
 *
 * primo punto
 *
 * effettuare visita in profondità, se non ha archi back allora è un dag
 * effettuare powerset per cercare tutti gli archi da rimuovere, in pratica l'insieme degli archi da eliminare sono diversi in base al vertice da dove parti, ma per un vertice qualsiasi si devono comunque eliminare tutti gli archi back per ottenere un dag
 * considerare tutti i possibili insiemi per poter scegliere poi quello di peso massimo

svolgo il powerset per cercare tutte gli archi da rimuovere, per far questo svolgo una visita in profondità del dag e se non incontro archi back la soluzione va bene, in seguito seleziono la soluzione che rimuove il minor numero di archi e con peso maggiore
in teoria ti basta rimuovere dei set di archi , devi trovare il numero minimo di archi che se tolti ti trasformano il grafo in un dag


 */
#include <stdio.h>
#include <stdlib.h>
#include "titles.h"
#define MAXC 11

int main(void) {
    int i, cont;
    char name[MAXC];
    FILE *fin, *fout;
    cont = 1;
    while(cont) {
        printf("===============\n");
        printf("1.Load title from file\n");
        printf("2.Ricerca di un titolo azionario\n");
        printf("3.Ricerca della quotazione di una certa data della sua quotazione\n");
        printf("4.Ricerca della quatoaazione minima e massima dato un titolo e un range di date\n");
        printf("5.Ricerca della quotazione minima e massima dato un titolo nell'intero perido\n");
        printf("6.Bilanciamento dell'albero delle quotazioni, dato un titolo\n");
        printf("7.Free graph and exit\n");
        printf("Enter your choice : ");
        if(scanf("%d",&i)<=0) {
            printf("Integers only!\n");
            exit(0);
        }
        else {
            switch(i) {
                case 1:     printf("Input file name: ");
                    scanf("%s", name);
                    fin = fopen(name, "r");
                    if (fin == NULL) exit(-1);
                    readfile(fin);
                    fclose(fin);
                    break;
                case 2:
                    printf("inserire funzione 2");
                    break;
                case 3:
                    printf("inserire funzione 3");
                    break;
                case 4:
                    printf("inserire funzione 4");
                    break;
                case 5:
                    printf("inserire funzione 5");
                    break;
                case 6:
                    printf("inserire funzione 2");
                    break;
                case 7:     cont = 0;
                    break;
                default:    printf("Invalid option\n");
            }
        }
    }
    return 0;
}