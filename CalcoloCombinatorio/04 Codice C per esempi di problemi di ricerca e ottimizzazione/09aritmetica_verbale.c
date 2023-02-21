#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include<ctype.h>

#define LUN_MAX 8+1   // lunghezza massima delle stringhe 1 e 2, incluso \0
#define n 10          // massimo numero di lettere distinte possibili per numeri in base 10
#define base 10      // numero di cifre nella base decimale

int lett_dist = 0;    // numero di lettere distinte presenti

typedef struct {
  char car;
  int  val;
} alpha;

int trova_indice(alpha *lettere, char c) {  // trova l'indice di un carattere
  int i;

  for(i=0; i < lett_dist; i++)
    if (lettere[i].car == c) return i;
  return -1;
}


alpha * init_alpha() { //inizializza il vettore di struct lettere
  int i;
  alpha *lettere;
  lettere = malloc(n * sizeof(alpha));
  if (lettere == NULL)
    exit(-1);

  for(i=0; i < n; i++) {
    lettere[i].val = -1;
    lettere[i].car = '\0';
  }
  return lettere;
}

void stampa(alpha *lettere) {
  int i;

  for(i=0; i < lett_dist; i++) {
    printf("%c > %d\n", lettere[i].car, lettere[i].val);
  }
}

int w2n(alpha *lettere, char *str) { // converti stringa di caratteri in intero
  int i, valore = 0, l = strlen(str);
  if (lettere[trova_indice(lettere, str[0])].val == 0)
    return -1;

  for(i=0; i < l; i++)
    valore = valore * 10 + lettere[trova_indice(lettere, str[i])].val;
  return valore;
}

int contr_sol(alpha *lettere, char *str1, char *str2, char *str3) { //escludendo i casi con cifra piu' significativa nulla, controlla se n1+n2=n3
  int n1, n2, n3;
  n1 = w2n(lettere, str1);
  n2 = w2n(lettere, str2);
  n3 = w2n(lettere, str3);
  if (n1 == -1 || n2 == -1 || n3 == -1)
    return 0;
  return ((n1 + n2) == n3);
}

int disp(alpha *lettere, int *mark, int pos, char *str1, char *str2, char *str3) {

  int i = 0;
  if (pos == lett_dist) {
    int risolto = contr_sol(lettere, str1, str2, str3);
    if (risolto) stampa(lettere);
    return risolto;
  }

  for(i=0;i < base; i++) {
    if (mark[i]==0) {
        lettere[pos].val = i;
        mark[i] = 1;
        if (disp(lettere, mark, pos+1, str1, str2, str3))
            return 1;
        lettere[pos].val = -1;
        mark[i] = 0;
    }
  }

  return 0;
}

void setup(alpha *lettere, char *str1, char *str2, char *str3) {
  int i, l1=strlen(str1), l2= strlen(str2), l3=strlen(str3);

  for(i=0; i<l1; i++) {
    if (trova_indice(lettere, str1[i]) == -1)
        lettere[lett_dist++].car = str1[i];
  }

  for(i=0; i<l2; i++) {
    if (trova_indice(lettere, str2[i]) == -1)
        lettere[lett_dist++].car = str2[i];
  }

  for(i=0; i<l3; i++) {
    if (trova_indice(lettere, str3[i]) == -1)
        lettere[lett_dist++].car = str3[i];
  }
}

int main(void) {

  char str1[LUN_MAX], str2[LUN_MAX], str3[LUN_MAX+1];
  int mark[base] = {0};
  int i;

  printf("Input stringa1: ");
  scanf("%s", str1);
  printf("Input stringa2: ");
  scanf("%s", str2);
  printf("Input stringa3: ");
  scanf("%s", str3);

  alpha *lettere = init_alpha();
  setup(lettere, str1, str2, str3);

  disp(lettere, mark, 0, str1, str2, str3);

  free(lettere);
  return 0;
}
