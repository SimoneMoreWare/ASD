#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#include "PQ.h"
#include "Item.h"

#define RATIO 0.25

enum { f, t };

typedef enum menuSel_e {
  exit_c, ranking_c, insert_c, delete_c, play_c,  load_c, store_c, numSel_c
} menuSel;

typedef int bool;

/* si propone una tabella di conversione tra menu e stringhe, basata su
   vettore di struct, anziche' vettore con accesso diretto */
typedef struct {menuSel code; char *prompt; char *cmd;} select_t;

select_t selections[] = {
  {exit_c,       "Exit               ", "Stop"},
  {ranking_c,    "Print ranking      ", "Rank"},
  {insert_c,     "Insert player      ", "Ins"},
  {delete_c,     "Delete player      ", "Del"},
  {play_c,       "Play               ", "Play"},
  {load_c,       "Load from file     ", "Load"},
  {store_c,      "Store to           ", "Sto"},
  {numSel_c,     NULL,                   NULL}
};

menuSel menu(void);
void play(PQ pq);

int main(int argc, char *argv[]) {
  menuSel sel;
  bool stopPrg;
  PQ pq;
  char tmp[MAXC];
  FILE *fin;
  Id k;
  int i, numEl = 0;
  Item *v;

  srand((unsigned)time(NULL));
  stopPrg = f;
  pq = NULL;
  do {
    sel = menu();
    switch(sel){

    case exit_c:
      stopPrg = t;
      break;

    case ranking_c:
      numEl = PQsize(pq);
      if (numEl > 0) {
        v = calloc(numEl, sizeof(Item));
        if (v == NULL) exit(-1);
        for (i=0; i<numEl; i++)
          v[i] = PQextractMin(pq);
        for (i=numEl-1; i>=0; i--)
          ITEMstore(stdout, v[i]);
        for (i=0; i<numEl; i++)
          PQinsert(pq, v[i]);
        free(v);
      }
      break;

    case insert_c:
      printf("Input player id > ");
      PQinsert(pq, ITEMscan(stdin));
      break;

    case delete_c:
      printf("Input player id > ");
      k = SCANid();
      if (k == NULL) exit(-1);
      PQremove(pq, k);
      break;

    case play_c:
      play(pq);
      PQstore(pq, stdout);
      break;

    case load_c:
      printf("Input file name > ");
      scanf("%s", tmp);
      fin = fopen(tmp, "r");
      PQload(&pq, fin);
      if (pq == NULL) exit(-1);
      fclose(fin);
      break;

    case store_c:
      printf("Input file name > ");
      scanf("%s", tmp);
      fin = fopen(tmp, "w");
      PQstore(pq, fin);
      fclose(fin);
      break;

    default:
      printf("Invalid selection\n");
      break;
    }
  } while(!stopPrg);

  PQfree(pq);

  return 0;
}

menuSel menu(void){
  int i, nFound, iFound, len;
  char sel[MAXC];
  printf("\nMENU \n");
  for(i=0; i<numSel_c; i++)
    printf("%s (%s)\n", selections[i].prompt, selections[i].cmd);
  printf("\nSELECT: ");
  scanf(" %s",sel);
  iFound = -1;
  nFound = 0;
  len = strlen(sel);
  for (i=0; i<numSel_c; i++) {
    if (strncmp(sel,selections[i].cmd,len)==0) {
      nFound++;
      iFound = i;
    }
  }
  if (nFound==1) {
    return selections[iFound].code;
  }
  else if (nFound>1) {
    /* parte iniziale troppo corta - ripetere */
    printf("Ambiguous selection %s\n", sel);
  }
  return numSel_c;
}

void play(PQ pq) { /* ADT */
  Item a, b;
  int rnd;

  if (PQsize(pq) < 2)
    return;

  a = PQextractMin(pq);
  ITEMstore(stdout, a);
  b = PQextractMin(pq);
  ITEMstore(stdout, b);
  rnd = rand() < RAND_MAX/2;
  if (rnd == 0) {
    printf("%s beats %s\n", GETid(a), GETid(b));
    ITEMchange(a, b, RATIO);
  } else {
    printf("%s beats %s\n", GETid(b), GETid(a));
    ITEMchange(b, a, RATIO);
  }
  if (!ITEMzero(a))
    PQinsert(pq, a);
  if (!ITEMzero(b))
    PQinsert(pq, b);

  return;
}
