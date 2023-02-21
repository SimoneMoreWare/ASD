#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAXBIT 8
#define MAXCOD 256

int pow2(int e) {
  return 1<<e;
}

/* Implementazione dalla definizione */
void gray_1(int codici[MAXCOD][MAXBIT], int pos, int nbit) {
  int i, j, ncodici = pow2(nbit-pos);

  if (pos == nbit)
    return;

  gray_1(codici, pos+1, nbit);

  for (i=0; i<ncodici/2; i++) {
    codici[i][pos] = 0;
    codici[ncodici/2+i][pos] = 1;
    for (j=pos+1; j<nbit; j++)
      codici[ncodici/2+i][j] = codici[ncodici/2-1-i][j];
  }

  return;
}

void gray_1_wrapper(int codici[MAXCOD][MAXBIT], int nbit) {
  gray_1(codici, 0, nbit);
}

/* Implementazione dalla seconda definizione */
void gray_2(int *codice, int n, int k) {
  if (n == 1) {
    codice[0] = k;
    return;
  }
  if (k < (pow2(n-1))) {
    codice[0] = 0;
    gray_2(codice+1, n-1, k);
    return;
  }
  else {
    codice[0] = 1;
    gray_2(codice+1, n-1, pow2(n) - 1 - k);
    return;
  }
}


void gray_2_wrapper(int codici[MAXCOD][MAXBIT], int nbit) {
  int i, ncodici = pow2(nbit);
  for (i = 0; i < ncodici; i++) {
    gray_2(codici[i], nbit, i);
  }
}

/* Implementazione dalla seconda definizione */
void gray_2b(int *codice, int n, int k, int nbit) {
  /*printf("%d\n", n);*/
  if (n == 1) {
    codice[nbit-1] = k;
    return;
  }
  if (k < (pow2(n-1))) {
    codice[nbit-n] = 0;
    gray_2b(codice, n-1, k, nbit);
    return;
  }
  else {
    codice[nbit-n] = 1;
    gray_2b(codice, n-1, pow2(n) - 1 - k, nbit);
    return;
  }
}


void gray_2b_wrapper(int codici[MAXCOD][MAXBIT], int nbit) {
  int i, ncodici = pow2(nbit);
  for (i = 0; i < ncodici; i++) {
    gray_2b(codici[i], nbit, i, nbit);
  }
}



void gray_3_discendente(int *codice, int pos, int nbit);
void gray_3_ascendente(int *codice, int pos, int nbit);

void gray_3_discendente(int *codice, int pos, int nbit) {
  int i;
  if (pos == nbit) {
    for (i=0; i<nbit; i++)
      printf("%d", codice[i]);
    printf("\n");
    return;  
  }
  codice[pos] = 0;
  gray_3_discendente(codice, pos+1, nbit);
  codice[pos] = 1;
  gray_3_ascendente(codice, pos+1, nbit);
}

void gray_3_ascendente(int *codice, int pos, int nbit) {
  int i;  
  if (pos == nbit) {
    for (i=0; i<nbit; i++)
      printf("%d", codice[i]);
    printf("\n");
    return;  
  }
  codice[pos] = 1;
  gray_3_discendente(codice, pos+1, nbit);
  codice[pos] = 0;
  gray_3_ascendente(codice, pos+1, nbit);
}

void gray_3_wrapper(int nbit) {
  int codice[MAXCOD];
  gray_3_discendente(codice, 0, nbit);
  
}

/* Simile a disposizioni ripetute */
void gray_4(int *codice, int pos, int nbit, int primo) {
  int i, secondo = (primo+1) % 2; /* 1->0, 0->1 */
  if (pos == nbit) {
    for (i=0; i<nbit; i++)
      printf("%d", codice[i]);
    printf("\n");
    return;  
  }
  codice[pos] = primo;
  gray_4(codice, pos+1, nbit, 0);
  codice[pos] = secondo;
  gray_4(codice, pos+1, nbit, 1);
}

void gray_4_wrapper(int nbit) {
  int codice[MAXCOD];
  gray_4(codice, 0, nbit, 0);
}

void gray_5(int *codice, int pos, int nbit, int primo, int codici[MAXCOD][MAXBIT], int *code_idx) {
  int i, secondo = (primo+1) % 2; /* 1->0, 0->1 */
  if (pos == nbit) {
    for (i = 0; i < nbit; i++) {
      codici[*code_idx][i] = codice[i];
    }
    *code_idx = *code_idx + 1;
    return;
  }
  codice[pos] = primo;
  gray_5(codice, pos+1, nbit, 0, codici, code_idx);
  codice[pos] = secondo;
  gray_5(codice, pos+1, nbit, 1, codici, code_idx);
}

void gray_5_wrapper(int codici[MAXCOD][MAXBIT], int nbit) {
  int codice[MAXCOD];
  int code_idx = 0;
  gray_5(codice, 0, nbit, 0, codici, &code_idx);
}


void gray_6(int *codice, int pos, int nbit, int codici[MAXCOD][MAXBIT], int *code_idx) {
  int i; /* 1->0, 0->1 */
  if (pos == nbit) {
    for (i = 0; i < nbit; i++) {
      codici[*code_idx][i] = codice[i];
    }
    *code_idx = *code_idx + 1;
    return;
  }
  gray_6(codice, pos+1, nbit, codici, code_idx);
  codice[pos] = 1 - codice[pos];
  gray_6(codice, pos+1, nbit, codici, code_idx);
}

void gray_6_wrapper(int codici[MAXCOD][MAXBIT], int nbit) {
  int codice[MAXCOD] = {0};
  int code_idx = 0;
  gray_6(codice, 0, nbit, codici, &code_idx);
}


void reset_codici(int codici[MAXCOD][MAXBIT], int nbit) {
  int i, j, ncodici = pow2(nbit);
  for (i=0; i<ncodici; i++) {
    for (j=0; j<nbit; j++) {
      codici[i][j] = 0;
    }
  }
}
void print_codici(int codici[MAXCOD][MAXBIT], int nbit) {
  int i, j, ncodici = pow2(nbit);
  for (i=0; i<ncodici; i++) {
    for (j=0; j<nbit; j++) {
      printf("%d", codici[i][j]);
    }
    printf("\n");
  }
}

int main(int argc, char **argv) {
    int codici[MAXCOD][MAXBIT];
    int nbit = atoi(argv[1]);
    int ncodici = pow2(nbit);
    int i, j;

    if (nbit > MAXBIT) {
      printf("Error - Number of bits should be <= 8\n");
      return 1;
    }

    reset_codici(codici, nbit);
    printf("\nGray1\n");
    gray_1_wrapper(codici,nbit);
    print_codici(codici, nbit);
    
    printf("\n-----\n\nGray2\n");
    reset_codici(codici, nbit);
    gray_2_wrapper(codici,nbit);
    print_codici(codici, nbit);
    
    printf("\n-----\nGray2b\n");
    reset_codici(codici, nbit);
    gray_2b_wrapper(codici,nbit);
    print_codici(codici, nbit);
    
    printf("\n-----\nGray3\n");
    gray_3_wrapper(nbit);
    printf("\n-----\nGray4\n");
    gray_4_wrapper(nbit);
    
    printf("\n-----\nGray5\n");
    reset_codici(codici, nbit);
    gray_5_wrapper(codici,nbit);
    print_codici(codici, nbit);
    
    printf("\n-----\nGray6\n");    
    reset_codici(codici, nbit);
    gray_6_wrapper(codici,nbit);
    print_codici(codici, nbit);
    printf("\n-----\n\n");
    return 0;
}

