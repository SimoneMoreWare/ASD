#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define LEN 6
#define VOC 5
#define voc "aeiou"

typedef struct strSet_ {
  int n;
  char **stringhe;
} strSet;

strSet *leggiFile(char *fn);
int vocale(char c);
void disp_sempl(strSet *ss, int pos, int *val, int *sol, int *mark, int n, int k, int cm, int vm, int lm);
int check(char *curr_string, int len, int cmax, int vmax, int lmax);
void gen(strSet *ss, int n, int k, int cm, int vm, int lm);

int main(int argc, char **argv) {
  int cm, vm, lm, n, k, i;
  strSet *ss;

  ss = leggiFile(argv[1]);
  if (ss == NULL)
    return -1;
  n = ss->n;


  printf("\nP1 - Generazione di tutte le stringhe che rispettano i vincoli:\n");
  printf("Inserisci il numero massimo di consonanti consecutive:  " );
  scanf("%d", &cm);
  printf("Inserisci il numero massimo di vocali consecutive:  " );
  scanf("%d", &vm);
  printf("Inserisci la lunghezza massima della stringa generata:  " );
  scanf("%d", &lm);

  for (k=1; k <=n; k++)
    gen(ss, n, k, cm, vm, lm);

  for(i=0; i<ss->n; i++)
    free(ss->stringhe[i]);
  free(ss->stringhe);
  free(ss);
  return 0;
}

strSet *leggiFile(char *fn) {
  int i;
  char tmp[LEN];
  FILE *in;
  strSet *ss;

  in  = fopen(fn, "r");
  if (in == NULL)
    return NULL;

  ss = calloc(1, sizeof(strSet));
  if (ss == NULL)
    return NULL;

  fscanf(in, "%d", &ss->n);

  ss->stringhe = malloc(ss->n *sizeof(char*) +1);
  for(i=0; i<ss->n; i++) {
    fscanf(in, "%s", tmp);
    ss->stringhe[i] = strdup(tmp);
    if (ss->stringhe[i] == NULL)
      return NULL;
  }

  fclose(in);
  return ss;
}

int vocale(char c) {
  int i;
  for(i=0; i<VOC; i++)
    if (c == voc[i])
      return 1;
  return 0;
}

void gen(strSet *ss, int n, int k, int cm, int vm, int lm) {
  int i, *val, *sol, *mark;
  val = malloc(n * sizeof(int));
  for (i=0; i<n; i++)
    val[i]=i;
  sol = calloc(k, sizeof(int));
  mark = calloc(n, sizeof(int));

  disp_sempl(ss, 0, val, sol, mark, n, k, cm, vm, lm );

  free(val);
  free(sol);
  free(mark);
}

void disp_sempl(strSet *ss, int pos, int *val, int *sol, int *mark, int n, int k, int cm, int vm, int lm) {
  int i, len;
  char *curr_string = calloc(n*LEN, sizeof(char));
  if (curr_string == NULL)
    exit (-1);

  if (pos >= k) {
    for (i=0; i<k; i++)
      strcat(curr_string, ss->stringhe[sol[i]]);
    len = strlen(curr_string);
    if(check(curr_string, len, cm, vm, lm))
       printf("%s\n", curr_string);
    free(curr_string);
    return;
  }
  for (i=0; i<n; i++) {
    if (mark[i] == 0) {
      mark[i] = 1;
      sol[pos] = val[i];
      disp_sempl(ss, pos+1, val, sol, mark, n, k, cm, vm, lm);
      mark[i] = 0;
    }
  }
  free(curr_string);
  return;
}

int check(char *curr_string, int len, int cm, int vm, int lm) {
  int i, v=0, c=0;
  if (len > lm)
    return 0;
  for(i=0; i<len; i++) {
    if (vocale(curr_string[i])) {
      v++;
      c = 0;
      if (v > vm)
        return 0;
    } else {
      c++;
      v = 0;
      if (c > cm)
        return 0;
    }
  }
  return 1;
}



