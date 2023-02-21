#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include<math.h>

#define DBG 1       /* Impostare questa define a 1 per vedere la stampa e il contatore delle soluzioni parziali considerate */
#define NUM_DIGIT 9
#define KO 0        /* Soluzione parziale che non puo' condurre a quella cercata */
#define OK 1        /* Soluzione parziale che non puo' condurre a quella cercata */

#if DBG
int cnt = 0;
#endif

int risolvi(char *num[3], int liv, int n, int *mark, int riporto);
void spazi(int l);
void stampa (char *num[3], int liv, int n);

int main(int argc, char **argv) {

    int n = -1;
    char *num[3];
    int mark[NUM_DIGIT] = {0,0,0,0,0,0,0,0,0};

    if (argc <= 4) {
        printf("Uso: %s <N> <addendo1> <addendo2> <somma>\n", argv[0]);
        exit(-1);
    }

    n = atoi(argv[1]);
    num[0] = strdup(argv[2]);
    num[1] = strdup(argv[3]);
    num[2] = strdup(argv[4]);

    if (risolvi(num, 0, n, mark, 0) == OK) {
      printf("Soluzione trovata\n");
      stampa(num,-1,n); /* -1 per disabilitare asterischi */
    }
    return 0;
}

int risolvi(char *num[3], int liv, int n, int *mark, int riporto) {
  int i, i_cifra, i_num, ris, ris_cifra, ris_riporto;

  if (liv == 3*n)
    return OK;

  i_num = liv%3;
  i_cifra = n - liv/3 - 1;

  if (i_num<2) {
    if (num[i_num][i_cifra] != '_')
      return (risolvi(num, liv+1, n, mark, riporto));
    else {
      for(i=0;i<NUM_DIGIT;i++) {
        if (!mark[i]) {
          mark[i] = 1;
          num[i_num][i_cifra] = '1' + i;
          if (risolvi(num, liv+1, n, mark, riporto) == OK)
            return OK;
          num[i_num][i_cifra] = '_';
          mark[i] = 0;
        }
      }
    }
  }
  else {
    ris = riporto + (num[0][i_cifra]-'0') + (num[1][i_cifra]-'0');
    ris_cifra = ris%10;
    ris_riporto = ris/10;

    if (num[i_num][i_cifra] != '_') {
      if (num[i_num][i_cifra] != (ris_cifra+'0'))
        return KO;
      else
        if (risolvi(num, liv+1, n, mark, ris_riporto) == OK)
          return OK;
    }
    else if (!mark[ris_cifra-1]) {
      mark[ris_cifra-1] = 1;
      num[i_num][i_cifra] = ris_cifra+'0';
      if (risolvi(num, liv+1, n, mark, ris_riporto) == OK)
        return OK;
      num[i_num][i_cifra] = '_';
      mark[ris_cifra-1] = 0;
    }
  }
  return KO;
}

void spazi(int l) {
  int i;
  for (i=0; i<l; i++) printf(" ");
}

void stampa (char *num[3], int liv, int n) {
  int i;
  /* stampa stringhe, indicando con asterisco riga e colonna corrente */
  if (liv>=0) {
    spazi(liv+(3 + n - liv/3)); printf("*\n");
  }
  for (i=0; i<3; i++) {
    spazi(liv); printf("N%d: %s", i, num[i]);
    if (liv%3 == i) printf("*"); printf("\n");
  }
  printf("\n");
}

