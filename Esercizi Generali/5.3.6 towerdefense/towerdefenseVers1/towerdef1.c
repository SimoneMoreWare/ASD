#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define DBG 0

typedef enum {VUOTO, RISORSA, ALLEATO, NEMICO} elemento;

typedef struct risorsa_{
  int raggio, att, dif, costo;
} risorsa;

typedef struct risorse_ {
  risorsa *vr;
  int nR;
} risorse;

typedef struct t_{
  int i, j, val;
  elemento tipoTarget;
} t;

typedef struct target_ {
  t *vt;
  int nT;
} target;

typedef struct cella_ {
  int att;
  int dif;
  elemento e;
  int indiceElemento;
} cella;

typedef struct mappa_ {
  int R, C;
  cella **m;
} mappa;

risorse *leggiFileRisorse(char *fn) {
  int i;
  FILE *in = fopen(fn, "r");
  risorse* wrapRisorse = calloc(1, sizeof(risorse));

  if (wrapRisorse == NULL)
    exit(-1);

  fscanf(in, "%d", &wrapRisorse->nR);
  wrapRisorse->vr = calloc(wrapRisorse->nR, sizeof(risorsa));

  for(i=0;i<wrapRisorse->nR;i++)
    fscanf(in, "%d %d %d %d", &wrapRisorse->vr[i].raggio, &wrapRisorse->vr[i].att, &wrapRisorse->vr[i].dif, &wrapRisorse->vr[i].costo);

  fclose(in);
  return wrapRisorse;
}

void stampaRisorse(risorse *r) {
  int i;

  if (r == NULL || r->nR <= 0)
    return;

  for(i=0;i<r->nR;i++)
    printf("%d %d %d %d\n", r->vr[i].raggio, r->vr[i].att, r->vr[i].dif, r->vr[i].costo);
}

void stampaCella(cella c, target *a, target *n, risorse *r, int dettagli) {
  switch(c.e) {
    case ALLEATO:
      if (dettagli)
        printf("%c%d(%d)/%d/%d", 'a', c.indiceElemento, a->vt[c.indiceElemento].val, c.att, c.dif);
      else
        printf("%c%d", 'a', c.indiceElemento);
      break;
    case NEMICO:
      if (dettagli)
        printf("%c%d(%d)/%d/%d", 'n', c.indiceElemento, n->vt[c.indiceElemento].val, c.att, c.dif);
      else
        printf("%c%d", 'n', c.indiceElemento);
      break;
    case RISORSA:
      if (dettagli)
        printf("%c%d", 'r', c.indiceElemento);
      else
        printf("%c%d", 'r', c.indiceElemento);
      break;
    case VUOTO:
      if (dettagli)
        printf("-/%d/%d", c.att, c.dif);
      else
        printf("%d/%d", c.att, c.dif);
      break;
    default:
      break;
  }
}

void stampaMappa(mappa *m, target *a, target *n, risorse *r, int dettagli) {
  int i, j;

  for(i=0;i<m->R;i++) {
    for(j=0;j<m->C;j++) {
      if (j)
        printf("\t");
      stampaCella(m->m[i][j], a, n, r, dettagli);
    }
    printf("\n");
  }
}

void fondiMappe(mappa *dest, mappa *src) {
  int i, j;
  if (dest->R != src->R || dest->C != src->C)
    return;

  for(i=0;i<dest->R;i++) {
    for(j=0;j<dest->C;j++) {
      if (dest->m[i][j].e == VUOTO)
        dest->m[i][j] = src->m[i][j];
    }
  }
}

target *leggiFileTarget(char *fn, elemento tipo) {
  int i;
  target* wrapTarget = calloc(1, sizeof(target));
  FILE *in = fopen(fn, "r");

  if (wrapTarget == NULL)
    exit(-1);

  fscanf(in, "%d", &wrapTarget->nT);
  wrapTarget->vt = calloc(wrapTarget->nT, sizeof(t));

  for(i=0;i<wrapTarget->nT;i++) {
    fscanf(in, "%d %d %d", &wrapTarget->vt[i].i, &wrapTarget->vt[i].j, &wrapTarget->vt[i].val);
    wrapTarget->vt[i].tipoTarget = tipo;
  }
  fclose(in);
  return wrapTarget;
}

void stampaTarget(target *t) {
  int i;
  if (t == NULL || t->nT <= 0) return;

  for(i=0;i<t->nT;i++)
    printf("%d %d %d\n", t->vt[i].i, t->vt[i].j, t->vt[i].val);
}

mappa *setupMappa(int R, int C, target *alleati, target *nemici) {
  int i;
  mappa *wrapMappa = calloc(1, sizeof(mappa));

  wrapMappa->R = R;
  wrapMappa->C = C;
  wrapMappa->m = calloc(R, sizeof(cella*));

  if (wrapMappa->m == NULL)
    exit(-1);

  for(i=0;i<R;i++) {
    wrapMappa->m[i] = calloc(C, sizeof(cella));
    if (wrapMappa->m[i] == NULL)
      exit(-1);
  }

  if (alleati != NULL) {
    for(i=0;i<alleati->nT;i++) {
      if (alleati->vt[i].i < 0 || alleati->vt[i].i >= R || alleati->vt[i].j < 0 || alleati->vt[i].j >= C)
        exit(-1); /* oppure continue se si vuole essere meno drastici... */
      if (wrapMappa->m[alleati->vt[i].i][alleati->vt[i].j].e != VUOTO)
        exit(-1);
      wrapMappa->m[alleati->vt[i].i][alleati->vt[i].j].e = ALLEATO;
      wrapMappa->m[alleati->vt[i].i][alleati->vt[i].j].indiceElemento = i;
    }
  }

  if (nemici != NULL) {
    for(i=0;i<nemici->nT;i++) {
      if (nemici->vt[i].i < 0 || nemici->vt[i].i >= R || nemici->vt[i].j < 0 || nemici->vt[i].j >= C)
        exit(-1);
      if (wrapMappa->m[nemici->vt[i].i][nemici->vt[i].j].e != VUOTO)
        exit(-1);
      wrapMappa->m[nemici->vt[i].i][nemici->vt[i].j].e = NEMICO;
      wrapMappa->m[nemici->vt[i].i][nemici->vt[i].j].indiceElemento = i;
    }
  }

  return wrapMappa;
}

void setupRisorsa(risorse *wr, int r, int c, int ris, mappa *solmap, int add) {
  int i, j, raggio = wr->vr[ris].raggio, a = wr->vr[ris].att, d = wr->vr[ris].dif;

  for(i=-raggio;i<=raggio;i++) {
    for(j=-raggio;j<=raggio;j++) {
      if ((r+i) < 0 || (r+i) >= solmap->R)
        continue;
      if ((c+j) < 0 || (c+j) >= solmap->C)
        continue;
      if (i == 0 && j == 0 && add == 1) {
        solmap->m[r][c].e = RISORSA;
        solmap->m[r][c].indiceElemento = ris;
      } else if (i == 0 && j == 0 && add == -1) {
        solmap->m[r][c].e = VUOTO;
        solmap->m[r][c].indiceElemento = 0;
      } else {
        solmap->m[r+i][c+j].att += add*a;
        solmap->m[r+i][c+j].dif += add*d;
      }
    }
  }
}

int checkMap(risorse *wr, target *a, target *n, mappa *m, mappa *solmap) {
  int i, j, targetDif, targetAtt;

  for(i=0;i<m->R;i++) {
    for(j=0;j<m->C;j++) {
      if (m->m[i][j].e == VUOTO || m->m[i][j].e == RISORSA)
        continue;
      if (m->m[i][j].e == ALLEATO) {
        targetDif = a->vt[m->m[i][j].indiceElemento].val;
        if (targetDif > solmap->m[i][j].dif)
          return 0;
      }
      if (m->m[i][j].e == NEMICO) {
        targetAtt = n->vt[m->m[i][j].indiceElemento].val;
        if (targetAtt > solmap->m[i][j].att)
          return 0;
      }
    }
  }
  return 1;
}

int posizionaR(risorse *wr, target *a, target *n, mappa *m, int *ris, mappa *solmap, int pos, int r, int c, int numRisorse, int start) {
  int i, ok;

  /* La riga precedente, di fatto, è finita */
  if (c >= m->C) {
    c = 0;
    r++;
  }

  /* Nella posizione attuale c'è già qualcosa, fai avanzare fino a trovare una cella libera */
  while(r < m->R && m->m[r][c].e != VUOTO) {
    c++;
    if (c >= m->C) {
      c = 0;
      r++;
    }
    pos++;
  }

  /* Se si è raggiunto l'angolo in basso a dx della mappa, o se non ci sono più risorse da posizionare, controlla disposizione */
  if (numRisorse == 0 || pos >= (m->R*m->C))
    return checkMap(wr, a, n, m, solmap);

  /* Per tutte le risorse */
  for(i=start;i<wr->nR;i++) {
    /* Se non fa parte della soluzione o se ne sono già state usate tutte le copie, continua... */
    if (ris[i] <= 0)
      continue;
    /* Posiziona la risorsa nella cella corrente e rendi visibili i suoi effetti sulla mappa... */
    setupRisorsa(wr, r, c, i, solmap, 1);
    ris[i]--;
    /* Ricorri sulla prossima cella */
    ok = posizionaR(wr, a, n, m, ris, solmap, pos+1, r, c+1, numRisorse-1, 0);
    if (ok)
      return ok;
    /* Se non ha funzionato, rimuovi la risorsa da questa cella e provane altre... */
    ris[i]++;
    setupRisorsa(wr, r, c, i, solmap, -1);

    /* Prova anche a ricorrere lasciando la cella corrente vuota e provando a ripartire da questa stessa risorsa sulla posizione subito dopo... */
    ok = posizionaR(wr, a, n, m, ris, solmap, pos+1, r, c+1, numRisorse, i);
    if (ok)
      return ok;
  }
  return 0;
}

int posiziona(risorse *r, target *a, target *n, mappa *m, int *sol, mappa *solmap) {
  int ok, i, numRisorse = 0;
  /* Crea una copia di comodo dell'eleneco delle risorse disponibili e del numero totale di elementi presi */
  int *ris = calloc(r->nR, sizeof(int));
  memcpy(ris, sol, r->nR*sizeof(int));

  for(i=0;i<r->nR;i++)
    numRisorse += ris[i];

  ok = posizionaR(r, a, n, m, ris, solmap, 0, 0, 0, numRisorse, 0);

  free(ris);

  return ok;
}

int check(risorse *r, target *a, target *n, mappa *m, int *sol, mappa *solmap) {

  /* Pruning rapido per soluzioni deboli in partenza
     se la somma cumulativa del potere di attacco/difesa di tutte le risorse prese
     non permetterebbe di distruggere/difendere il target più problematico (val maggiore), non provare
     nemmeno a piazzare le risorse su mappa */

  int sumAtt = 0, sumDif = 0, i;

  for(i=0;i<r->nR;i++) {
    sumAtt += sol[i]*r->vr[i].att;
    sumDif += sol[i]*r->vr[i].dif;
  }

  for(i=0;i<a->nT;i++)
    if (a->vt[i].val > sumDif)
      return 0;

  for(i=0;i<n->nT;i++)
    if (n->vt[i].val > sumAtt)
      return 0;


#if DBG
    for(i=0;i<r->nR;i++) printf("%d ", sol[i]);
    printf(" ATT = %d DIF = %d\n", sumAtt, sumDif);
#endif /* DBG */

  /* Prova a posizionare le risorse su mappa... */
  return posiziona(r, a, n, m, sol, solmap);
}

int compra(risorse *r, target *a, target *n, mappa *m, int budget, int *sol, mappa *solmap, int start) {
  int i;

  if (check(r, a, n, m, sol, solmap))
    return 1;

  for(i=start;i<r->nR;i++) {
    if ((budget - r->vr[i].costo) < 0)
      continue;
    sol[i]++;
    if (compra(r, a, n, m, budget-r->vr[i].costo, sol, solmap, i))
      return 1;
    sol[i]--;
  }
  return 0;
}



void risolvi(risorse *r, target *a, target *n, mappa *m, int B) {
  int i;
  int *sol = calloc(r->nR, sizeof(int));
  mappa *solmap = setupMappa(m->R, m->C, NULL, NULL);

  if (compra(r, a, n, m, B, sol, solmap, 0)) {
    printf("Configurazione vincente trovata\n");
    fondiMappe(m, solmap);
    stampaMappa(m, a, n, r, 0);
  } else {
    printf("Impossibile individuare una soluzione\n");
  }
  for(i=0;i<m->R;i++) {
    free(solmap->m[i]);
  }
  free(solmap->m);
  free(solmap);
  free(sol);
}

int main(int argc, char **argv) {
  int R, C, B ,i;
  risorse *r;
  target *a, *n;
  mappa *m;

  if (argc < 7) {
    printf("Uso: %s file_risorse file_alleati file_nemici R C B", argv[0]);
    exit(-1);
  }

  r = leggiFileRisorse(argv[1]);
  a = leggiFileTarget(argv[2], ALLEATO);
  n = leggiFileTarget(argv[3], NEMICO);
  R = atoi(argv[4]);
  C = atoi(argv[5]);
  B = atoi(argv[6]);

  m = setupMappa(R, C, a, n);

#if DBG
  printf("Risorse\n");
  stampaRisorse(r);
  printf("Alleati\n");
  stampaTarget(a);
  printf("Nemici\n");
  stampaTarget(n);
  printf("Mappa\n");
  stampaMappa(m, a, n, r, 1);
#endif /* DBG */
  risolvi(r, a, n, m, B);
  free(r->vr);
  free(r);
  free(a->vt);
  free(a);
  free(n->vt);
  free(n);
  for(i=0;i<R;i++) {
    free(m->m[i]);
  }
  free(m->m);
  free(m);
  return 0;
}
