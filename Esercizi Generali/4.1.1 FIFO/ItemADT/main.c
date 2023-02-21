#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include<ctype.h>

#include "Item.h"
#include "Queue.h"

#define BUFF_SIZE 10

int main(int argc, char **argv) {
    char scelta[5], *sc;
    int termina = 0;
    Q q = NULL;
    do {
        printf("Quale operazione vuoi eseguire?\n");
        printf("A: Inizializza nuovo buffer\n");
        printf("B: Vedi cardinalita'\n");
        printf("C: Inserzione\n");
        printf("D: Estrazione\n");
        printf("E: Visualizza tutto\n");
        printf("F: Salva su file\n");
        printf("G: Leggi da file\n");
        printf("H: Distruggi buffer\n");
        printf("Z: Esci\n");
        scanf("%s", scelta);
        for(sc=scelta;!isalpha(*sc);sc++);
        *sc = toupper(*sc);
        switch(*sc) {
            case 'A': {
                q = QUEUEinit(BUFF_SIZE);
            }
            break;
            case 'B': {
                printf("%d\n", QUEUEnum(q));
            }
            break;
            case 'C': {
                Item d;
                ITEMscan(stdin, &d);
                if (q == NULL) q = QUEUEinit(BUFF_SIZE);
                QUEUEput(q, d);
            }
            break;
            case 'D': {
                Item d;
                QUEUEget(q, &d);
                ITEMfree(d);
            }
            break;
            case 'E': {
                QUEUEshow(stdout, q);
            }
            break;
            case 'F': {
                char filename[100];
                FILE *out;
                printf("Inserisci nome del file\n");
                scanf("%s", filename);
                out = fopen(filename, "w");
                QUEUEshow(out, q);
                fclose(out);
            }
            break;
            case 'G': {
                char filename[100];
                FILE *in;
                printf("Inserisci nome del file\n");
                scanf("%s", filename);
                in = fopen(filename, "r");
                if (q != NULL) QUEUEfree(q);
                q = QUEUEscan(in, BUFF_SIZE);
                fclose(in);
            }
            break;
            case 'H': {
                QUEUEfree(q);
                q = NULL;
            }
            break;
            case 'Z': {
                termina = 1;
                QUEUEfree(q);
                q = NULL;
            }
            break;
                default:
                printf("Scelta non valida!\n");
        }
    } while(!termina);
    return 0;
}
