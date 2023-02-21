#include<string.h>
#include<stdlib.h>
#include<stdio.h>

#include "ingrediente.h"

#define N_SCELTE 3

void valutaRicetta(list *ingredienti);
void stampaMenu(char *scelte[], int *selezione);

int main(int argc, char **argv) {

  char *scelte[] = {
		"Uscita",
		"Stampa Ingredienti",
		"Valuta Ricetta"
	};

  int selezione;
  int fineProgramma = 0;
  list *ingredienti;
  FILE *fin = fopen(argv[1], "r");
  if (fin == NULL)
    exit(-1);

  if (argc != 2) {
	printf("Uso: %s <file_ingredienti>\n", argv[0]);
	return -1;
  }

  ingredienti = leggiIngredienti(fin);
  if (ingredienti == NULL)
    return -1;
  fclose(fin);

  do {
    stampaMenu(scelte, &selezione);
    switch(selezione) {
      case 0:
        {
          fineProgramma = 1;
	}
        break;
      case 1:
       {
         stampaIngredienti(ingredienti, stdout);
       }
       break;
     case 2:
       {
         valutaRicetta(ingredienti);
       }
       break;
     default:
       {
         printf("Scelta non valida\n");
       }
       break;
    }
  } while(!fineProgramma);
  liberaIngredienti(ingredienti);
  return 0;
}

void stampaMenu(char *scelte[], int *selezione){
  int i=0;
  printf("MENU'\n");
  for (i=0; i<N_SCELTE; i++)
    printf("  %d) %s\n",i,scelte[i]);
  printf("Scelta: ");
  scanf("%d",selezione);
}


void valutaRicetta(list *ingredienti) {
  int nIngr = -1, i, qta;
  float cal = 0.0, prezzo = 0.0;
  char ingrTmp[LEN];
  ingrediente_t *iTmp = NULL;

  do {
    printf("Inserire numero di ingredienti: ");
    scanf("%d", &nIngr);
  } while(nIngr <= 0);

  for (i=0; i<nIngr; i++) {
    printf("Scegliere ingrediente [nome] [quantita' (g)]\n");
    printf(" > ");
    scanf("%s %d", ingrTmp, &qta);
    iTmp = cercaIngrediente(ingrTmp, ingredienti);
    if (iTmp == NULL)
        printf("Ingrediente non trovato\n");
    if (iTmp != NULL) {
      prezzo += (qta * iTmp->prezzo / 1000.0) ;
      cal += (qta * iTmp->cal ) ;
    }
  }
  printf("Costo complessivo: %.2f\n", prezzo);
  printf("Calorie totali: %.2f\n", cal);
}

