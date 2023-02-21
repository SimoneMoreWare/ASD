#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define LEN 200
#define REQ 3
#define DBG 1

typedef struct oggetto_{
  char *nome;
  char *cat;
  int r, c, u;
} oggetto;

typedef struct oggetti_ {
  oggetto *o;
  int nO;
} oggetti;

oggetti *leggiFile(char *fname) {
  oggetti* equip;
  int i;
  char nome[LEN], cat[LEN];
  FILE *fin = fopen(fname, "r");
  equip = calloc(1, sizeof(oggetti));
  if (equip == NULL)
    exit(-1);

  fscanf(fin, "%d", &equip->nO);
  equip->o = calloc(equip->nO, sizeof(oggetto));
  if (equip->o == NULL)
    exit(-1);
  for (i=0; i<equip->nO; i++) {
    fscanf(fin, "%s %s %d %d %d", nome, cat, &equip->o[i].r, &equip->o[i].c, &equip->o[i].u);
    equip->o[i].nome = strdup(nome);
    if (equip->o[i].nome == NULL)
      exit(-1);
    equip->o[i].cat = strdup(cat);
    if (equip->o[i].cat == NULL)
      exit(-1);
  }
  fclose(fin);
  return equip;
}

void stampa(oggetti *equip) {
  int i;
  if (equip == NULL || equip->nO <= 0)
    return;
  for (i=0; i<equip->nO; i++) {
    printf("%s %s %d %d %d\n", equip->o[i].nome, equip->o[i].cat, equip->o[i].r, equip->o[i].c, equip->o[i].u);
  }
}

int occupa(int **inv, int x, int y, int r, int c, int val, int R, int C) {
  int i, j, fail = 0;
  for (i=x; i<x+r && !fail; i++) {
    for (j=y; j<y+c && !fail; j++) {
      if (i >= R || j >= C)
          printf("HALT\n");
      if (val != -1 && inv[i][j] != -1) {
        /* Sovrapposizione con un altro oggetto già nella griglia */
        fail = 1;
        break;
      } else {
        inv[i][j] = val;
      }
    }
  }

  if (fail) {
    /* Se l'oggetto incontra sovrapposizioni, pulisci */
    for (i=x; i<x+r; i++) {
      for (j=y; j<y+c; j++) {
        if (inv[i][j] == val) inv[i][j] = -1;
      }
    }
  }
  return fail;
}

int posizionaR(int pos, int r, int c, oggetti *equip, int *sol, int R, int C, int **tmp_inv, int *mark, int piazzati, int scelti) {
  int i, ok, fail;

  /* La ricorsione, anche senza aver raggiunto il "fondo" della matrice ha già disposto tutti gli oggetti scelti dallo zaino */
  if (piazzati == scelti)
    return 1;

  /* La prima precedente, di fatto, è finita */
  if (c >= C) {
    c = 0;
    r++;
  }

  /* Nella posizione attuale c'è già qualcosa, fai avanzare fino a trovare una cella libera */
  while(r < R && tmp_inv[r][c] != -1) {
    c++;
    if (c >= C) {
      c = 0;
      r++;
    }
    pos++;
  }

  /* La ricorsione ha raggiunto la fine della griglia dell'inventario, ma non ha piazzato tutti gli elementi (avrebbe fatto ritorno l'if a inizio funzione) */
  if (pos >= (R*C))
    return 0;

/* Per tutti gli oggetti */
  for(i=0; i<equip->nO; i++)
    /* Questo oggetto o non fa parte della soluzione o è già stato preso */
    if (sol[i] != 0 && mark[i] == 0) {
    /* Questo oggetto non ci sta in altezza, non c'è modo di introdurlo nella griglia in questa posizione e in nessuna delle successive */
      if (equip->o[i].r > (R-r)) {
        return 0;
      } else if (equip->o[i].c > (C-c)) {
      /* questo oggetto non ci sta in larghezza su questa riga, ma potrebbe starci in una riga più in basso partendo più a sinistra rispetto alla c corrente
         ricorre spostando avanti pos per saltare via la porzione della riga rimanente. Lascia che sia la ricorsione successiva a riassestare r e c. */
        ok = posizionaR(pos+C-c, r, C, equip, sol, R, C, tmp_inv, mark, piazzati, scelti);
        if (ok)
          return ok;
      } else {
      /* L'oggetto ci potrebbe stare e quindi occupiamo la porzione di spazio necessaria prima di ricorrere
         se occupa incontra spazio occupato da un altro oggetto, ritorna una condizione di fallimento
         trattata come se l'oggetto non ci fosse stato già in partenza, lasciando che la ricorsione prosegua sulle posizioni a seguire */
        fail = occupa(tmp_inv, r, c, equip->o[i].r, equip->o[i].c, i, R, C);
        if (!fail) {
          mark[i] = 1;
          ok = posizionaR(pos+equip->o[i].c, r, c+equip->o[i].c, equip, sol, R, C, tmp_inv, mark, piazzati+1, scelti);
          if (ok)
            return ok;
        /* La ricorsione non ha ritornato un successo, per cui togli l'oggetto da questa posizione e provane un altro */
          mark[i] = 0;
          occupa(tmp_inv, r, c, equip->o[i].r, equip->o[i].c, -1, R, C);
        } else {
          ok = posizionaR(pos+1, r, c+1, equip, sol, R, C, tmp_inv, mark, piazzati, scelti);
          if (ok)
            return ok;
        }
      }
    }

  return 0;
}

int posiziona(oggetti *equip, int *sol, int R, int C, int **inv) {
  int i, j, ok, scelti=0, **tmp_inv, *mark;

  mark = calloc(equip->nO, sizeof(int));
  if (mark == NULL)
    exit(-1);
  tmp_inv = calloc(R, sizeof(int*));
  if (tmp_inv == NULL)
    exit(-1);
  for (i=0; i<R; i++) {
    tmp_inv[i] = calloc(C, sizeof(int));
    if (tmp_inv[i] == NULL)
      exit(-1);
    for(j=0; j<C; j++)
      tmp_inv[i][j] = -1;
  }
  for (i=0; i<equip->nO; i++)
    if (sol[i] == 1)
      scelti++;

  ok = posizionaR(0, 0, 0, equip, sol, R, C, tmp_inv, mark, 0, scelti);

  if (ok)
   for (i=0; i<R; i++)
    for (j=0; j<C; j++)
      inv[i][j] = tmp_inv[i][j];

  for (i=0; i<R; i++)
    free(tmp_inv[i]);
  free(tmp_inv);
  free(mark);

  return ok;
}

int check(oggetti *equip, int *sol, int R, int C, int **inv) {
  int i, j;
  char *req[REQ] = {"arma", "armatura", "pozione"};
  int mark[REQ] = {0, 0, 0};
  for (i=0; i<equip->nO; i++) {
    if(sol[i] == 1)
      for(j=0; j<REQ; j++)
        if (strcmp(equip->o[i].cat, req[j]) == 0)
          mark[j] = 1;
  }
  for (i=0; i<REQ; i++)
    if (mark[i] == 0)
      return 0;
  return posiziona(equip, sol, R, C, inv);
}

void zaino(oggetti *equip, int R, int C, int A, int pos, int curr_area, int curr_val, int *sol, int *best_val, int *best_sol, int **inv) {
  if (pos >= equip->nO) {
    if (curr_val > *best_val && check(equip, sol, R, C, inv)) {
#if DBG
      printf("Aggiornamento soluzione corrente %d -> %d\n", *best_val, curr_val);
#endif /* DBG */
      *best_val = curr_val;
      memcpy(best_sol, sol, equip->nO*sizeof(int));
    }
    return;
  }
   if (curr_area+equip->o[pos].r * equip->o[pos].c >A || equip->o[pos].r > R || equip->o[pos].c > C) {
     sol[pos] = 0;
     zaino(equip, R, C, A, pos+1, curr_area, curr_val, sol, best_val, best_sol, inv);
     return;
    }

    sol[pos] = 1;
    curr_area += equip->o[pos].r * equip->o[pos].c;
    curr_val += equip->o[pos].u;
    zaino(equip, R, C, A, pos+1, curr_area, curr_val, sol, best_val, best_sol, inv);

    sol[pos] = 0;
    curr_area -= equip->o[pos].r * equip->o[pos].c;
    curr_val -= equip->o[pos].u;
    zaino(equip, R, C, A, pos+1, curr_area, curr_val, sol, best_val, best_sol, inv);
}

void risolvi(oggetti *equip, int R, int C) {
  int i, j, *sol, *best_sol, best_val = 0, **inv;

  sol = calloc(equip->nO, sizeof(int));
  if (sol == NULL)
    exit(-1);
  best_sol = calloc(equip->nO, sizeof(int));
  if (best_sol == NULL)
    exit(-1);

  inv = calloc(R, sizeof(int*));
  if (inv == NULL)
    exit(-1);
  for (i=0; i<R; i++) {
    inv[i] = calloc(C, sizeof(int));
    if (inv[i] == NULL)
      exit(-1);
    for (j=0; j<C; j++)
      inv[i][j] = -1;
  }

  zaino(equip, R, C, R*C, 0, 0, 0, sol, &best_val, best_sol, inv);

  if (best_val > 0) {
    printf("Soluzione di valore %d trovata\n",  best_val);
    for (i=0; i<equip->nO; i++)
      if (sol[i])
        printf("  %s\n", equip->o[i].nome);
    for (i=0; i<R; i++) {
      for (j=0; j<C; j++) {
        if (inv[i][j] == -1) {
          printf("-\t");
        } else {
          printf("%d\t", inv[i][j]);
        }
      }
      printf("\n");
    }
    printf("\n");
    free(sol);
    free(best_sol);
    for (i=0; i<R; i++) {
      free(inv[i]);
    }
    free(inv);
  }
}

int main(int argc, char **argv) {
  int i, R, C;
  oggetti *equip;
  if (argc < 4) {
    printf("Uso: %s file_input R C", argv[0]);
    exit(-1);
  }

  R = atoi(argv[2]);
  C = atoi(argv[3]);
  equip = leggiFile(argv[1]);
#if DBG
  printf("L'equipaggiamento disponibile e':\n\n");
  stampa(equip);
  printf("\n");
#endif /* DBG  */
  risolvi(equip, R, C);
  for (i=0; i<equip->nO; i++) {
    free(equip->o[i].nome);
    free(equip->o[i].cat);
  }
  free(equip->o);
  free(equip);
  return 0;
}
