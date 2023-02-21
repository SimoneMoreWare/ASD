#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include<ctype.h>

#include "ST.h"
#include "Graph.h"

#define MAXL 31

/*
 * NOTA: tutte le funzioni sono scritte per eseguire sia usando lAdj sia mAdj.
 * Basta passare il valore opportuno a "flag": 0 -> liste, 1 -> matrice
 * Nel menù non sono riportate le invocazioni su mAdj, per brevità.
 */


Graph read_file(FILE *in, ST *st, Vertex **net, int *nV);

int main(int argc, char **argv) {
  char label[MAXL], select[MAXL], *sel;
  int i, j, V, stop = 0, id, matgen=0, *adjacentN, *adjacentW, extra, intra;
  Graph g = NULL;
  ST st = NULL;
  Vertex *net = NULL;
  FILE *fin;

  if (argc != 2) {
    printf("Use: %s <file_in>\n", argv[0]);
    exit(-1);
  }

  fin = fopen(argv[1], "r");
  if (fin == NULL)
    exit(-1);

  g = read_file(fin, &st, &net, &V);
  if (g == NULL) exit(-1);

  if (g == NULL || st == NULL || net == NULL)
    exit(-1);

  do {
        printf("\nQuale operazione vuoi eseguire?\n");
        printf("\tA: Visualizza numero e nome dei nodi\n");
        printf("\tB: Visualizza archi incidenti su un nodo\n");
        printf("\tC: Genera matrice di adiacenza\n");
        printf("\tD: Calcolo dei flussi\n");
        printf("\tZ: Esci\n");
        scanf("%s", select);
        for (sel=select; !isalpha(*sel); sel++);
        *sel = toupper(*sel);
        switch(*sel) {
            case 'A': {
                printf("Numero di vertici: %d\n", V);
                for (i=0; i<V; i++)
                  printf("\t%s\n", net[i].name);
            }
            break;
            case 'B': {
                printf("Quale nodo vuoi esaminare? [nome]\n");
                scanf("%s", label);
                id = STsearch(st, label);
                if (id >= 0) {
                  adjacentN = malloc(V*sizeof(int));
                  adjacentW = malloc(V*sizeof(int));
                  if (adjacentN == NULL || adjacentW == NULL) exit(-1);
                  for (i=0; i<V; i++) {
                    adjacentN[i] = -1;
                    adjacentW[i] = -1;
                  }
                  printf("Grado del nodo: %d\n", GRAPHnodeDegree(g, id, 0));
                  GRAPHadjacent(g, adjacentN, adjacentW, id, 0);
                }
                printf("Nodi adiacenti: \n");
                for (i=0; i<V; i++)
                  if (adjacentN[i]!=-1)
                    printf("\t%s", net[adjacentN[i]].name);
                printf("\n");
                free(adjacentN);
                free(adjacentW);
            }
            break;
            case 'C': if (!GRAPHlist2mat(g))
                        printf("Generazione avvenuta con successo!\n");
                      matgen = 1;
                      break;
            case 'D': {
                intra = extra = 0;
                adjacentN = malloc(V*sizeof(int));
                adjacentW = malloc(V*sizeof(int));
                if (adjacentN == NULL || adjacentW == NULL) exit(-1);
                for (i=0; i<V; i++) {
                  adjacentN[i] = -1;
                  adjacentW[i] = -1;
                }

                for (i=0; i<V; i++) {

                  for (j=0; j<V; j++) {
                    adjacentN[j] = -1;
                    adjacentW[j] = -1;
                  }
                  GRAPHadjacent(g, adjacentN, adjacentW, i, 0);

                  for (j=0; j<V; j++)
                    if (adjacentN[j]!=-1) {
                      if (strcmp(net[i].subnet, net[adjacentN[j]].subnet)==0)
                        intra += adjacentW[j];
                      else
                        extra += adjacentW[j];
                    }
                }
                printf("Flusso intra-rete: %d\n", intra/2);
                printf("Flusso extra-rete: %d\n", extra/2);
                free(adjacentN);
                free(adjacentW);
            }
            break;
            case 'Z': {
                stop  = 1;
            }
            break;
            default:
                printf("Scelta non valida!\n");
        }
    } while(!stop);

  fclose(fin);
  free(net);
  STfree(st);
  GRAPHfree(g, matgen);
  return 0;
}

Graph read_file(FILE *in, ST *st, Vertex **net, int *V) {
  int i, id1, id2;
  char label1[MAXL], label2[MAXL];
  Graph g;

  fscanf(in, "%d", V);
  g = GRAPHinit(*V);
  if (g == NULL)
    return NULL;

  *st = STinit(*V);
  if (*st == NULL)
    return NULL;

  *net = malloc((*V)*sizeof(Vertex));
  if (*net == NULL)
    return NULL;

  for (i=0; i<*V; i++) {
    fscanf(in, "%s %s", label1, label2);
    strcpy((*net)[i].name, label1);
    strcpy((*net)[i].subnet, label2);
    STinsert(*st, (*net)[i].name, i);
  }

  while(fscanf(in, "%s %s %d", label1, label2, &i) == 3) {
    id1 = STsearch(*st, label1);
    id2 = STsearch(*st, label2);
    if (id1 != id2 && id1 >= 0 && id2 >= 0)
      GRAPHinsertE(g, id1, id2, i);
    }
  return g;
}
