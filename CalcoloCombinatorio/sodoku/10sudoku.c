#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define MAXBUFFER 128

int num_sol=0;

/********************************************************************
  Prototipi
********************************************************************/

int **acquisisci(char* nomefile, int *dim_ptr);
int controlla(int **schema, int dim, int pos, int val);
void disp_ripet(int **schema, int dim, int pos);

/********************************************************************
  Programma principale
********************************************************************/
int main() {
  int **schema, dim, i;
  char nomefile[20];

  printf("Inserire il nome del file: ");
  scanf("%s", nomefile);

  schema = acquisisci(nomefile, &dim);

  disp_ripet(schema, dim, 0);

  printf("\n Numero di soluzioni = %d\n", num_sol);

  for (i=0; i<dim; i++)
    free(schema[i]);

  free(schema);
  return 0;
}

/********************************************************************
  Funzione ricorsiva di ricerca di una soluzione
********************************************************************/
void disp_ripet(int **schema, int dim, int pos) {
  int i, j, t;

  /* verifica di terminazione */
  if (pos >= dim*dim) {
    num_sol++;
    printf("Soluzione:\n");
    for (i=0; i<dim; i++) {
      for (j=0; j<dim; j++)
	    printf("%3d ", schema[i][j]);
      printf("\n");
    }
    return;
   }

  /* indici casella corrente */
  i = pos / dim;
  j = pos % dim;
  if (schema[i][j] != 0) {
    /* casella inizialmente piena: nessun tentativo da fare */
    disp_ripet(schema, dim, pos+1);
    return;
  }

  /* provo tutti i possibili valori da 1 a dim */
  for (t=1; t<=dim; t++) {
    schema[i][j] = t;
    if (controlla(schema, dim, pos, t))
      disp_ripet(schema, dim, pos+1);
    schema[i][j] = 0;
  }
  return;
}

/********************************************************************
  Funzione di controllo della validita' di una soluzione parziale
********************************************************************/

int controlla(int **schema, int dim, int pos, int val) {
  int i, j, r, c, n=floor(sqrt(dim));

  i = pos/dim;
  j = pos % dim;

  /* controllo le righe */
  for (c=0; c<dim; c++) {
    if (c!=j)
      if (schema[i][c]==val)
        return 0;
  }

  /* controllo le colonne */
  for (r=0; r<dim; r++) {
    if (r!=i)
      if (schema[r][j]==val)
        return 0;
  }

  /* controllo i blocchi */
  for (r=(i/n)*n; r<(i/n)*n+n; r++)
    for (c=(j/n)*n; c<(j/n)*n+n; c++) {
      if ((r!=i) || (c!=j))
        if (schema[r][c]==val)
          return 0;
    }
  return 1;
}


/********************************************************************
  Funzione per la lettura dello schema di partenza
********************************************************************/
int **acquisisci(char* nomefile, int *dim_ptr) {
  int i, j, **schema, dimensione=0;
  char buf[MAXBUFFER];
  FILE *fp;

  fp = fopen(nomefile, "r");
  if (fp == NULL) {
    printf("Errore durante l'apertura del file\n");
    exit(1);
  }

  /* leggo la prima volta il file per sapere la dimensione dello schema */
  while (fgets(buf, MAXBUFFER, fp) != NULL) {
    dimensione++;
  }
  fclose(fp);

  /* allocazione memoria necessaria */
  schema = (int**)malloc((dimensione)*sizeof(int*));
  if (schema == NULL) {
    printf("Errore durante l'allocazione della memoria\n");
    exit(1);
  }

  for (i=0; i<dimensione; i++) {
    schema[i] = (int*)malloc(dimensione*sizeof(int));
    if (schema[i] == NULL) {
	  printf("Errore durante l'allocazione della memoria\n");
	  exit(1);
    }
  }

  /* leggo una seconda volta il file per memorizzare lo schema iniziale */
  fp = fopen(nomefile, "r");
  if (fp == NULL) {
    printf("Errore durante l'apertura del file\n");
    exit(1);
  }

  for (i=0; i<dimensione; i++) {
    for (j=0; j<dimensione; j++) {
	  fscanf(fp, "%d", &schema[i][j]);
    }
  }
  fclose(fp);

  *dim_ptr = dimensione;
  return schema;
}
