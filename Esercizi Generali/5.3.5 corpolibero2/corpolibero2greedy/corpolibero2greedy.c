#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#define DBG 0
#define MAX 256

/*
 * Organizzazione della soluzione
 * - Lettura del file e memorizzazione dei contenuti
 * - I dati non vengono riordinati dato che il numero di ripetizioni influenza il punteggio
 * - Cerca di costruire una soluzione rispettando (almeno) i vincoli minimi per la sua validita'
 * - Greedy proposti:
 *   1) Ottimizza una categoria alla volta (fino a min_i)
 *   2) Round Robin sulle categorie, aggiungendo un esercizio alla volta a ogni categoria
 *   3) Round Robin con priorita' sulle categorie, aggiungendo un esercizio a quella con meno punti
 *   4) Round Robin con priorita' sulle categorie, aggiungendo un esercizio a quella con meno esercizi
 */

/* Definizione delle strutture dati */

typedef struct elemento_ {
  char *nomeE;
  float diff;
  float punti;
} elemento;

typedef struct categoria_ {
  elemento *e;
  char *nomeC;
  int nElementi;
  int min, max;
} categoria;

typedef struct categorie_ {
  categoria *c;
  int nCat;
} categorie;

typedef struct solCat_ {
  int *elem;
  float punti, diff;
  int nEs;
} solCat;

typedef struct sol_ {
  solCat *sols;
  float punti, diff;
  int nCat;
} sol;

/* Funzioni di input */

categorie *leggiFile(FILE *in) {
  int i, j;
  char tmp[MAX];
  categorie *wrapper = calloc(1, sizeof(categorie));
  if (wrapper == NULL) return NULL;

  fscanf(in, "%d", &wrapper->nCat);
  wrapper->c = calloc(wrapper->nCat, sizeof(categoria));
  if (wrapper->c == NULL) return NULL;

  for(i=0;i<wrapper->nCat;i++) {
    fscanf(in, "%s %d %d %d", tmp, &wrapper->c[i].nElementi, &wrapper->c[i].min, &wrapper->c[i].max);
    wrapper->c[i].nomeC = strdup(tmp);

    wrapper->c[i].e = calloc(wrapper->c[i].nElementi, sizeof(elemento));
    if (wrapper->c[i].e == NULL) return NULL;

    for(j=0;j<wrapper->c[i].nElementi;j++) {
      fscanf(in, "%s %f %f", tmp, &wrapper->c[i].e[j].punti, &wrapper->c[i].e[j].diff);
      wrapper->c[i].e[j].nomeE = strdup(tmp);
    }
  }

  return wrapper;
}

/* Funzioni di stampa, principalmente per verifica dei contenuti letti e/o generati */

void stampaElementi(categorie *c) {
  int i, j;
  for(i=0;i<c->nCat;i++) {
    printf("%s min = %d max = %d\n", c->c[i].nomeC,c->c[i].min, c->c[i].max);
    for(j=0;j<c->c[i].nElementi;j++) {
      printf("   %s p = %.2f d = %.2f\n", c->c[i].e[j].nomeE, c->c[i].e[j].punti,c->c[i].e[j].diff);
    }
  }
  printf("\n\n");
}

void stampaSol(categorie *c, sol *s, FILE *out) {
  int i, j;
  for(i=0;i<c->nCat;i++) {
    fprintf(out, "%s\n", c->c[i].nomeC);
    for(j=0;j<c->c[i].nElementi;j++) {
      fprintf(out, "  %s x%d [%.2f/%.2f]\n", c->c[i].e[j].nomeE, s->sols[i].elem[j], c->c[i].e[j].punti, c->c[i].e[j].diff);
    }
  }
  fprintf(out, "TOT p = %.2f d = %.2f\n\n", s->punti, s->diff);
}

/* Funzioni di risoluzone Greedy */

/*
 * Greedy1: cerca di soddisfare i vincoli di una categoria fino a min_i prima di passare alla successiva
 * Le categorie incontrate "piu' tardi" sono implicitamente svantaggiate, dato che hanno a disposizione
 * solo la difficolta' residua non usata per soddisfare i vincoli sulle categorie che le precedono.
 */

void greedy1(categorie *c, int D, sol *s) {
  int i, j, k, nC = c->nCat;

  /* Per tutte le categorie... */
  for(i=0;i<nC;i++) {
    /* Per comodita' salva alcuni parametri di questa categoria */
    int min = c->c[i].min;
    int nE = c->c[i].nElementi;
    /* Cerca di soddisfare il vincolo sul minimo */
    for(j=0;j<min;j++) {
      int maxIndex = 0, found = 0;
      float maxPoint = 0.0, molt;
      /* Per tutti gli elementi possibili... */
      for(k=0;k<nE;k++) {
        molt = 1;
        if (s->sols[i].elem[k] == 1) molt = 0.5;
        if (s->sols[i].elem[k] >= 2) molt = 0.0;
        /* Cerca quello che porta il contributo maggiore al punteggio, rispettando D oppure uguale punteggio ma a costo minore */
        if (((molt*c->c[i].e[k].punti) > maxPoint && (s->diff + c->c[i].e[k].diff) <= D)
            ||
            ((molt*c->c[i].e[k].punti) == maxPoint && (s->diff + c->c[i].e[k].diff) <= D && c->c[i].e[k].diff < c->c[i].e[maxIndex].diff)) {
          maxIndex = k;
          maxPoint = molt*c->c[i].e[k].punti;
          found = 1;
        }
      }

      if (found) {
        /* Aggiorna la soluzione */
        s->sols[i].elem[maxIndex]++;
        /* Incrementa il parziale per p e d rispetto a questa singola categoria (nota: non e' strettamente necessario) */
        s->sols[i].diff += c->c[i].e[maxIndex].diff;
        s->sols[i].punti += maxPoint;
        /* Aggiorna il valore complessivo per p e d della soluzione completa sinora costruita */
        s->diff += c->c[i].e[maxIndex].diff;
        s->punti += maxPoint;
        /* Aggiorna conteggio */
        s->sols[i].nEs++;
      } else {
        break;
      }
    }

    if ( s->sols[i].nEs != min) {
      printf("Impossibile soddisfare vincolo su min per la categoria %s\n", c->c[i].nomeC);
      return;
    }
  }
  return;
}

/*
 * Greedy2: cerca di soddisfare i vincoli di una categoria (almeno) fino a min_i, assegnando pero' esercizi a rotazione.
 * Una volta scelto un esercizio per la categoria i, si passa alla successiva (o alla 0, giunti all'ultima).
 * Prova a ridurre lo svantaggio che caratterizza invece Greedy1.
 * Il ciclo sulle categorie e' ripetuto finche' c'e' disponibilita' di difficolta' e finche' e' possibile trovare una soluzione migliorante.
 * L'algoritmo usa una variabile 'miss' che inrementa ogni volta che una certa categoria giunge a una configurazione stabile.
 * A fronte di una modifica alla soluzione, miss viene riportato a 0, forzando di fatto un ulteriore check per ognuna delle categorie.
 * Esiste ancora un bias rispetto all'ordinamento delle categorie, ma e' meno marcato rispetto a Greedy1.
 */

void greedy2(categorie *c, int D, sol *s) {
  int i = -1, k, nC = c->nCat, miss = 0, min, max, nE, maxIndex, found;
  float maxPoint, molt;
  /* Per tutte le categorie, a rotazione */
  do {
#if DBG
    stampaSol(c, s, stdout);
#endif /* DBG */
    i = ((i+1) >=  nC) ? 0 : i+1;
    /* Per comodita' salva alcuni parametri di questa categoria */
    min = c->c[i].min;
    max = c->c[i].max;
    nE = c->c[i].nElementi;

    if (s->sols[i].nEs >= max) {
      /* La categoria corrente e' al completo
         NOTA: volendo si può rendere più restrittivo il greedy impostando >= min
         in questa maniera smette di occupare difficolta' per categorie gia' soddisfatte al minimo, lasciando spazio alle altre */
      miss++;
      continue;
    }

    maxIndex = 0;
    found = 0;
    maxPoint = 0.0;

    /* Per tutti gli elementi possibili della categoria 'i'... */
    for(k=0;k<nE;k++) {
      molt = 1;
      if (s->sols[i].elem[k] == 1) molt = 0.5;
      if (s->sols[i].elem[k] >= 2) molt = 0.0;
        /* Cerca quello che porta il contributo maggiore al punteggio, rispettando D oppure uguale punteggio ma a costo minore */
      if (((molt*c->c[i].e[k].punti) > maxPoint && (s->diff + c->c[i].e[k].diff) <= D)
          ||
          ((molt*c->c[i].e[k].punti) == maxPoint && (s->diff + c->c[i].e[k].diff) <= D && c->c[i].e[k].diff < c->c[i].e[maxIndex].diff)) {
        maxIndex = k;
        maxPoint = molt*c->c[i].e[k].punti;
        found = 1;
      }
    }

    if (found) {
      /* Aggiorna la soluzione */
      s->sols[i].elem[maxIndex]++;
      /* Incrementa il parziale per p e d rispetto a questa singola categoria (nota: non e' strettamente necessario) */
      s->sols[i].diff += c->c[i].e[maxIndex].diff;
      s->sols[i].punti += maxPoint;
      /* Aggiorna il valore complessivo per p e d della soluzione completa sinora costruita */
      s->diff += c->c[i].e[maxIndex].diff;
      s->punti += maxPoint;
      /* Aggiorna conteggio */
      s->sols[i].nEs++;
      /* La soluzione attuale e' cambiata, e quindi ancora non siamo giunti a una situazione stabile */
      miss = 0;
    } else if (!found && s->sols[i].nEs < min) {
      /* Non c'e' un esercizio ammissibile e il vincolo sul minimo non e' rispettato */
      printf("Impossibile soddisfare vincolo su min per la categoria %s\n", c->c[i].nomeC);
      break;
    } else {
      /* La categoria e' sodisfatta sul minimo, e non e' possibile aggiungere altri esercizi */
      miss++;
    }
  } while(s->diff < D && miss != nC);

  /* Check finale dei vincoli nel caso il programma termini per raggiungimento di D */
  for(i=0;i<nC;i++) {
    if (s->sols[i].nEs < c->c[i].min) {
      printf("Vincolo non rispettato per %s\n", c->c[i].nomeC);
      return;
    }
  }
  stampaSol(c, s, stdout);

  return;
}

/*
 * Greedy3: come Greedy2, ma anziche' incrementare in sequenza le categorie, si cerca quella attualmente piu' svantaggiata (per punteggio)
 * Per evitare che l'algoritmo rimanga incastrato nell'estrazione ripetuta di una categoria che non ammette altre modifiche la variabile miss viene
 * affiancata da un vettore di flag lungo quanto il numero di categorie.
 */

void greedy3(categorie *c, int D, sol *s) {
  int i = 0, j, k, nC = c->nCat, miss = 0, found, min, max, nE, maxIndex;
  int *flags = calloc(nC, sizeof(int)), molt, maxPoint;
  float minPoint = -1;

  /* Per tutte  le categorie, a rotazione */
  do {
#if DBG
    stampaSol(c, s, stdout);
#endif /* DBG */
    for(j=0, i=-1, minPoint = -1.0;j<nC;j++) {
      if (!flags[j] && ( s->sols[j].punti <= minPoint || minPoint < 0.0) && s->sols[j].nEs < c->c[i].max) {
        i = j;
        minPoint = s->sols[j].punti;
      }
    }

    if (i == -1) {
      break;
    }

    /* Per comodita' salva alcuni parametri di questa categoria */
    min = c->c[i].min;
    max = c->c[i].max;
    nE = c->c[i].nElementi;

    if (s->sols[i].nEs >= max) {
      /* La categoria corrente e' al completo
         NOTA: volendo si puo' rendere piu' restrittivo il greedy impostando >= min
         in questa maniera smette di occupare difficolta' per categorie gia' soddisfatte al minimo, lasciando spazio alle altre */
      flags[i] = 1;
      continue;
    }

    maxIndex = 0;
    maxPoint = 0.0;

    /* Per tutti gli elementi possibili della categoria 'i'... */
    for(k=0;k<nE;k++) {
      molt = 1;
      if (s->sols[i].elem[k] == 1) molt = 0.5;
      if (s->sols[i].elem[k] >= 2) molt = 0.0;
        /* Cerca quello che porta il contributo maggiore al punteggio, rispettando D oppure uguale punteggio ma a costo minore */
      if (((molt*c->c[i].e[k].punti) > maxPoint && (s->diff + c->c[i].e[k].diff) <= D)
          ||
          ((molt*c->c[i].e[k].punti) == maxPoint && (s->diff + c->c[i].e[k].diff) <= D && c->c[i].e[k].diff < c->c[i].e[maxIndex].diff)) {
        maxIndex = k;
        maxPoint = molt*c->c[i].e[k].punti;
        found = 1;
      }
    }

    if (found) {
      /* Aggiorna la soluzione */
      s->sols[i].elem[maxIndex]++;
      /* Incrementa il parziale per p e d rispetto a questa singola categoria */
      s->sols[i].diff += c->c[i].e[maxIndex].diff;
      s->sols[i].punti += maxPoint;
      /* Aggiorna il valore complessivo per p e d della soluzione completa sinora costruita */
      s->diff += c->c[i].e[maxIndex].diff;
      s->punti += maxPoint;
      /* Aggiorna conteggio */
      s->sols[i].nEs++;
      /* La soluzione attuale e' cambiata, e quindi ancora non siamo giunti a una situazione stabile */
      miss = 0;
      for(j=0;j<nC;j++) flags[j] = 0;
    } else if (!found && s->sols[i].nEs < min) {
      /* Non c'e' un esercizio ammissibile e il vincolo sul minimo non e' rispettato */
      printf("Impossibile soddisfare vincolo su min per la categoria %s\n", c->c[i].nomeC);
      break;
    } else {
      /* La categoria e' sodisfatta sul minimo e non e' possibile aggiungere altri esercizi */
      flags[i] = 1;
    }

    for(miss = 0, i=0;i<nC;i++) miss += flags[i];
  } while(s->diff < D && miss != nC);

  /* Check finale dei vincoli nel caso il programma termini per raggiungimento di D */
  for(i=0;i<nC;i++) {
    if (s->sols[i].nEs < c->c[i].min) {
      printf("Vincolo non rispettato per %s\n", c->c[i].nomeC);
      return;
    }
  }
  stampaSol(c, s, stdout);
  return;
}

/*
 * Greedy4: come Greedy3, ma anziche' incrementare in sequenza le categorie, si cerca quella attualmente piu' svantaggiata (per numero di esercizi)
 * Per evitare che l'algoritmo rimanga incastrato nell'estrazione ripetuta di una categoria che non ammette altre modifiche la variabile miss viene
 * affiancata da un vettore di flag lungo quanto il numero di categorie.
 * Con questo approccio si punta a rispettare esattamente i vincoli sul minimo, senza provare a fare di meglio.
 */

void greedy4(categorie *c, int D, sol *s) {
  int i = 0, j, k, nC = c->nCat, miss = 0, found, min, max, nE, maxIndex;
  int minEs = -1;
  float maxPoint, molt;
  int *flags = calloc(nC, sizeof(int));
  if (flags == NULL)
    exit(-1);

  /* Per tutte  le categorie, a rotazione */
  do {
#if DBG
    stampaSol(c, s, stdout);
#endif /* DBG */
    for(j=0, i=-1, minEs = -1;j<nC;j++) {
      if (!flags[j] && ( s->sols[j].nEs <= minEs || minEs < 0) && s->sols[j].nEs < c->c[i].min) {
        i = j;
        minEs = s->sols[j].nEs;
      }
    }

    if (i == -1) {
      break;
    }

    /* Per comodita' salva alcuni parametri di questa categoria */
    min = c->c[i].min;
    max = c->c[i].max;
    nE = c->c[i].nElementi;

    if (s->sols[i].nEs >= max) {
      /* La categoria corrente e' al completo
         NOTA: volendo si può rendere piu' restrittivo il greedy impostando >= min
         in questa maniera smette di occupare difficolta' per categorie già soddisfatte al minimo, lasciando spazio alle altre */
      flags[i] = 1;
      continue;
    }

    maxIndex = 0;
    maxPoint = 0.0;

    /* Per tutti gli elementi possibili della categoria 'i'... */
    for(k=0;k<nE;k++) {
      molt = 1;
      if (s->sols[i].elem[k] == 1) molt = 0.5;
      if (s->sols[i].elem[k] >= 2) molt = 0.0;
        /* Cerca quello che porta il contributo maggiore al punteggio, rispettando D oppure uguale punteggio ma a costo minore */
      if (((molt*c->c[i].e[k].punti) > maxPoint && (s->diff + c->c[i].e[k].diff) <= D)
          ||
          ((molt*c->c[i].e[k].punti) == maxPoint && (s->diff + c->c[i].e[k].diff) <= D && c->c[i].e[k].diff < c->c[i].e[maxIndex].diff)) {
        maxIndex = k;
        maxPoint = molt*c->c[i].e[k].punti;
        found = 1;
      }
    }

    if (found) {
      /* Aggiorna la soluzione */
      s->sols[i].elem[maxIndex]++;
      /* Incrementa il parziale per p e d rispetto a questa singola categoria */
      s->sols[i].diff += c->c[i].e[maxIndex].diff;
      s->sols[i].punti += maxPoint;
      /* Aggiorna il valore complessivo per p e d della soluzione completa sinora costruita */
      s->diff += c->c[i].e[maxIndex].diff;
      s->punti += maxPoint;
      /* Aggiorna conteggio */
      s->sols[i].nEs++;
      /* La soluzione attuale e' cambiata, quindi ancora non siamo giunti a una situazione stabile */
      miss = 0;
      for(j=0;j<nC;j++) flags[j] = 0;
    } else if (!found && s->sols[i].nEs < min) {
      /* Non c'e' un esercizio ammissibile e il vincolo sul minimo non e' rispettato */
      printf("Impossibile soddisfare vincolo su min per la categoria %s\n", c->c[i].nomeC);
      break;
    } else {
      /* La categoria e' sodisfatta sul minimo, e non e' possibile aggiungere altri esercizi */
      flags[i] = 1;
    }

    for(miss = 0, i=0;i<nC;i++) miss += flags[i];
  } while(s->diff < D && miss != nC);

  /* Check finale dei vincoli nel caso il programma termini per raggiungimento di D */
  for(i=0;i<nC;i++) {
    if (s->sols[i].nEs < c->c[i].min) {
      printf("Vincolo non rispettato per %s\n", c->c[i].nomeC);
      free(flags);
      return;
    }
  }
  stampaSol(c, s, stdout);
  free(flags);
  return;
}


/* Intero blocco risolutivo */

void risolvi(categorie *c, int D) {
  int i;
  sol *s = calloc(1, sizeof(sol));
  s->nCat = c->nCat;
  s->sols = calloc(s->nCat, sizeof(solCat));
  for(i=0;i<s->nCat;i++) {
    s->sols[i].elem = calloc(c->c[i].nElementi, sizeof(int));
  }

  greedy4(c, D, s);
  for(i=0;i<s->nCat;i++) {
    free(s->sols[i].elem);
  }
  free(s->sols);
  free(s);
}

int main(int argc, char **argv) {
  int i,j,D;
  FILE *in;
  categorie *c;
  if (argc != 3) {
    printf("Uso: %s file D", argv[0]);
    return -1;
  }

  in = fopen(argv[1], "r");
  c = leggiFile(in);
  if (c == NULL) return -1;
#if DBG
  stampaElementi(c);
#endif /* DBG */
  fclose(in);

  D = atoi(argv[2]);

  risolvi(c, D);
  for(i=0;i<c->nCat;i++) {
    for(j=0;j<c->c[i].nElementi;j++) {
      free(c->c[i].e[j].nomeE);
    }
    free(c->c[i].e);
    free(c->c[i].nomeC);
  }
  free(c->c);
  free(c);
  return 0;
}
