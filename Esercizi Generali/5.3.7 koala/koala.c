#include<stdlib.h>
#include<string.h>
#include<float.h>
#include<stdio.h>
#define maxT 100

#define DBG 1

typedef struct koala_ {
  int n_alberi;
  int *alberi;
  int famiglia;
} koala;


koala* leggi_habitat(char *fn, int *N, int *T) {
  int i, j, t;
  koala *vk;

  FILE *in = fopen(fn, "r");
  if (in == NULL)
    exit(-1);

  fscanf(in, "%d", N);
  vk = (koala*) calloc(*N, sizeof(koala));

  for(i=0;i<*N;i++) {
    fscanf(in, "%d", &t);
    vk[i].alberi = calloc(t, sizeof(int));
    vk[i].n_alberi = t;
    vk[i].famiglia = -1;
    for(j=0;j<t;j++) {
      fscanf(in, "%d", &vk[i].alberi[j]);
      if (vk[i].alberi[j] > *T)
        *T = vk[i].alberi[j];
    }
  }
  (*T)++;
  printf("Nella foresta ci sono %d alberi distinti\n", *T);
  fclose(in);
  return vk;
}

void leggi_famiglie(char *fn, koala *vk, int *S, int N) {
  int i, j, nk, k;
  FILE *in = fopen(fn, "r");

  if (in == NULL)
    exit(-1);
  fscanf(in, "%d", S);

  for(i=0;i<*S;i++) {
    fscanf(in, "%d", &nk);
    for(j=0;j<nk;j++) {
      fscanf(in, "%d", &k);
      if (k < 0 || k >= N)
        exit(-1);
      if (vk[k].famiglia != -1)
        exit(-1);
      vk[k].famiglia = i;
    }
  }
  fclose(in);
}

int **leggi_nemici(char *fn, int S) {
  int **nemici = NULL, i, j;
  FILE *in = fopen(fn, "r");

  if (in == NULL)
    exit(-1);

  nemici = calloc(S, sizeof(int*));
  for(i=0;i<S;i++)
    nemici[i] = calloc(S, sizeof(int));

  while(fscanf(in, "%d %d", &i, &j) == 2) {
    if (i == j || i < 0 || j < 0 || i >= S || j >= S)
      exit(-1);
    nemici[i][j] = nemici[j][i] = 1;
  }
  fclose(in);
  return nemici;
}

int check(int *sol, koala *vk, int **nemici, int N) {
  int k1, k2, f1, f2;
  for(k1=0;k1<N-1;k1++) {
    for(k2=k1+1;k2<N;k2++) {
      if (sol[k1] == sol[k2]) {  /* se i koala stanno sullo stesso albero, la coppia va controllata */
        f1 = vk[k1].famiglia; /* controlla se i due koala possono vivere insieme sulla base delle due famiglie di appartenenza */
        f2 = vk[k2].famiglia;
        if (nemici[f1][f2])
          return 0;
      }
    }
  }
  return 1;
}


int risolviDisp_r(int pos, int *sol, int *alberi, koala *vk, int **nemici, int N, int S, int T, int m) {
  int t, i, trovato=0, ok;

  if (pos >= N) {
    return check(sol, vk, nemici, N);
  }
  for (t=0; t<T; t++) { /* prova a posizionare il koala pos su ogni t-esimo albero */
    if (alberi[t] < m) { /* se albero già pieno, non provarci nemmeno */
      for(i=0;i<vk[pos].n_alberi && !trovato;i++)
        if (t == vk[pos].alberi[i])
         trovato = 1; /* l'albero t è ammissibile per il koala pos */
      if (trovato) { /* se è stato trovato un albero t ammissibile */
        alberi[t]++; /* c'e' un koala  in più sull'albero t */
        sol[pos] = t; /* il koala pos viene messo sull'albero t */
        ok = risolviDisp_r(pos+1, sol, alberi, vk, nemici, N, S, T, m);
        if (ok)
          return 1;
        alberi[t]--;
      }
    }
  }
  return 0;
}


void risolviDisp(koala *vk, int **nemici, int N, int S, int T, int m) {
  int *sol = calloc(N, sizeof(int));
  int *alberi = calloc(T, sizeof(int));
  int ok = 0, i;

  for(i=0;i<N;i++)
    sol[i] = -1;
  ok = risolviDisp_r(0, sol, alberi, vk, nemici, N, S, T, m);

  printf("\n -- DISP -- \n");
  if(ok > 0)
    for(i=0;i<N;i++)
      printf("Koala %d su albero %d\n", i, sol[i]);
  else
    printf("Impossibile generare soluzione valida\n");

  free(alberi);
  free(sol);
}


int risolviEr_r(int pos, int *sol, int *alberi, koala *vk, int **nemici, int maxAlberi, int N, int S, int T, int m) {
  int ok, t;

  if (pos >= N) {
    return check(sol, vk, nemici, N);
  }

  for(t=0;t<maxAlberi;t++) { /* prova a posizionare il koala pos su ogni t-esimo albero attualmente considerato */
    if (alberi[t] < m) { /* se albero già pieno, non provarci nemmeno */
      alberi[t]++; /* occupa un posto in più in t */
      sol[pos] = t; /* assegna t al koala pos */
      ok = risolviEr_r(pos+1, sol, alberi, vk, nemici, maxAlberi, N, S, T, m);
      if (ok)
        return 1;
      alberi[t]--;
    }
  }

  if (maxAlberi < T) { /* se posso estendere ulteriormente i blocchi (un albero in più) allora */
    sol[pos] = maxAlberi; /* posiziona il koala pos sull'albero nuovo */
    alberi[maxAlberi]++;  /* traccia l'occupazione */
    ok = risolviEr_r(pos+1, sol, alberi, vk, nemici, maxAlberi+1, N, S, T, m);
    if (ok)
      return 1;
    alberi[maxAlberi]--;
  }
  return 0;
}

void risolviEr(koala *vk, int **nemici, int N, int S, int T, int m) {
  int *sol = calloc(N, sizeof(int));
  int *alberi = calloc(T, sizeof(int));
  int ok = 0, i;

  for(i=0;i<N;i++)
    sol[i] = -1;
  ok = risolviEr_r(0, sol, alberi, vk, nemici, 0, N, S, T, m);
  printf("\n -- ER -- \n");
  if(ok > 0)
    for(i=0;i<N;i++)
      printf("Koala %d su albero %d\n", i, sol[i]);
  else
    printf("Impossibile generare soluzione valida\n");

  free(alberi);
  free(sol);
}

int main(int argc, char **argv) {

  int N = 0, S = 0, T = 0, **nemici, i;
  int m = atoi(argv[1]);

  koala *vk = leggi_habitat("habitat.txt", &N, &T);
  leggi_famiglie("famiglie.txt", vk, &S, N);
  nemici = leggi_nemici("nemici.txt", S);

  /* trascurando habitat */
  risolviEr(vk, nemici, N, S, T, m);

  /* tenendo conto di habitat */
  risolviDisp(vk, nemici, N, S, T, m);
  for(i=0;i<N;i++) {
    free(vk[i].alberi); 
  }
  free(vk);
  for(i=0;i<S;i++) {
    free(nemici[i]);
  }
  free(nemici);
  return 0;
}
