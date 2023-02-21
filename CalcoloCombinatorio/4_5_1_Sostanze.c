#include <stdio.h>

#define N       10   /* numero fasi */
#define MAX     100  /* max numero sostanze */
#define MAXNAME 21   /* max lungh. nomi */

typedef struct sostanza {
  char name[MAXNAME];
  int  phase, price;
} SOST;

int read_file (FILE *fin);
void solve (int phase);
int get_index (char *name);
void save_solution (void);

SOST vett[MAX];	        /*  elenco delle sostanze */
char incomp[MAX][MAX];	/*  matrice di incompatibilita' 
                         *  (azzerata automaticamente)
                         */
int solut[N+1],       /* soluzione corrente */
    best_solut[N+1];  /* soluzione migliore */
int n_sost, tot_price = 0, min_price = 10001;

main() {
  char	name[MAXNAME];
  FILE	*fin;
  int	i;

  printf ("Nome file di input: ");
  scanf("%s", name);
  if ((fin = fopen( name, "r")) == NULL) {
    printf ("Errore in apertura file di input \n");
    return;
  }

  if (read_file (fin)) {
    printf ("Errore in lettura file di input \n");
    return;
  }

  solve (1);
  if (min_price != 10001) {
    for (i = 1; i < N+1; i++)
      printf ("Fase %d-Sostanza %s\n", i, vett[best_solut[i]].name);
      printf ("Costo Totale %d\n", min_price);
  }
  else
    printf ("Non esiste soluzione \n");

}

int read_file (FILE *fin) {
  int	i, j, ns, index, n_inc;
  char	name[MAXNAME];

  fscanf (fin, "%d\n", &ns);

  for (i = n_sost = 0; i < ns; i++, n_sost++) {
    fgets (vett[i].name, MAXNAME-1, fin);
    fscanf (fin,"%d %d %d\n",&vett[i].phase,&vett[i].price,&n_inc);
    for (j = 0; j < n_inc; j++) {
      fgets (name, MAXNAME-1, fin);
      index = get_index (name);
      if (index < 0) {
        printf ("Errore: incompatibilità non valida\n");
      }
      else {
        incomp[i][index] = 1;
        incomp[index][i] = 1;
      }
    }
  }
  return( 0);
}

void solve (int phase) {
  int	i, j, is_inc;

  if (phase > N) {
    if (tot_price < min_price) {
      min_price = tot_price;
      save_solution();
    }
    return;
  }
  
  for (i = 0; i < n_sost; i++) {
    /* filtra le sostanze della fase richiesta */
    if (vett[i].phase == phase) {
      is_inc = 0;
      /* controlla incompatibilita' con sostanze gia' selezionate */
      for (j = 1; j < phase; j++)
        if (incomp[solut[j]][i] == 1)
          is_inc = 1;
      if (is_inc != 1) {
        solut[phase] = i;
        tot_price += vett[i].price;
        /* pruning */
        if (tot_price < min_price)
          solve (phase+1);
        tot_price -= vett[i].price;
      }
    }
  }
}

int get_index (char *name) {
  int 	i;
  for (i = 0; i < n_sost; i++) {
    if (strcmp (name, vett[i].name) == 0)
      return (i);
  }
  return (-1);
}

void save_solution(void) {
  int 	i;

  for (i = 1; i < N+1; i++)
    best_solut[i] = solut[i];
}
