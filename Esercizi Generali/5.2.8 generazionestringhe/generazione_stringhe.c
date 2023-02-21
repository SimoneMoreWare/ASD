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
int perm_sempl(strSet *ss, int pos, int *val, int *sol, int *mark, int n, char *target);
void powerset(strSet *ss, int pos, int *val, int *sol, int k, char *target, int scelta);
int check1(strSet *ss, int *sol, char *target);
int check2(strSet *ss, int *val, int *sol, int k, char *target);
void sottoinsiemi(strSet *ss, char *target, int scelta);
void printSubset(strSet *ss, int *sol);

int main(int argc, char **argv) {
  int i;
  strSet *ss;

  ss = leggiFile(argv[1]);
  if (ss == NULL)
    return -1;

  printf("\nP3 - Insiemi (versione 1):\n");
  sottoinsiemi(ss, argv[2], 0);

  system("pause");

  /*printf("\nP3 - Insiemi (versione 2):\n");
  sottoinsiemi(ss, argv[2], 1);*/
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

  fscanf(in, "%d", &ss->n);

  ss->stringhe = malloc(ss->n *sizeof(char*) +1);
  for(i=0; i<ss->n; i++) {
    fscanf(in, "%s", tmp);
    ss->stringhe[i] = strdup(tmp);
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

int perm_sempl(strSet *ss, int pos, int *val, int *sol, int *mark, int n, char *target) {
  int i;
  char *start = target;

  if (pos >= n) {
    for(i=0; i<n; i++) {
      start = strstr(start, ss->stringhe[sol[i]]);
      if (start == NULL)
        return 0;
      start += strlen(ss->stringhe[sol[i]]);
    }
    return 1;
  }

  for (i=0; i<n; i++)
    if (mark[i] == 0) {
      mark[i] = 1;
      sol[pos] = val[i];
      if (perm_sempl(ss, pos+1, val, sol, mark, n, target))
        return 1;
      mark[i] = 0;
    }
  return 0;
}

void sottoinsiemi(strSet *ss, char *target, int scelta) {
  int i, k = ss->n, *val, *sol;
  val = malloc(k * sizeof(int));
  for (i=0; i<k; i++)
    val[i]=i;
  sol = calloc(k, sizeof(int));

  powerset(ss, 0, val, sol, k, target, scelta);

  free(val);
  free(sol);
}

void powerset(strSet *ss, int pos, int *val, int *sol, int k, char *target, int scelta)  {
  if (pos >= k) {
    if (check1(ss, sol, target))
        printSubset(ss, sol);
/*
      if (check2(ss, val, sol, k, target))
        printSubset(ss, sol);
*/
  return;
  }

  sol[pos] = 0;
  powerset(ss, pos+1, val, sol, k, target, scelta);
  sol[pos] = 1;
  powerset(ss, pos+1, val, sol, k, target, scelta);
}

int check1(strSet *ss, int *sol, char *target) {
  int i, cnt=0;
  for(i=0; i<ss->n; i++) {
    if (sol[i] != 0)
      if (strstr(target, ss->stringhe[i]) == NULL)
        return 0;
    cnt++;
  }
  return (cnt > 0) ? 1 : 0;
}

int check2(strSet *ss, int *val, int *sol, int k, char *target) {

  int i, j =0, cnt=0, ok;
  int *compact, *perm, *mark;

  for(i=0;i<ss->n;i++)
    if (sol[i] != 0)
      cnt++;

  if (cnt <= 0)
    return 0;

  compact = malloc(cnt * sizeof(int));
  mark = calloc(cnt, sizeof(int));
  perm = calloc(cnt, sizeof(int));

  for(i=0; i<ss->n; i++)
    if (sol[i] != 0)
      compact[j++] = val[i];

  ok = perm_sempl(ss, 0, compact, perm, mark, cnt, target);

  free(compact);
  free(perm);
  free(mark);
  return ok;
}

void printSubset(strSet *ss, int *sol) {
  int i;
  for(i=0; i<ss->n; i++)
    if(sol[i])
      printf("%s ", ss->stringhe[i]);
  printf("\n");
}


