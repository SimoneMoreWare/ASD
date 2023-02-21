#include<string.h>
#include<stdlib.h>
#include<stdio.h>

#include "ingredienti.h"
#include "ricette.h"

#define N_SCELTE 9

void stampaMenu(char *scelte[], int *selezione);

int main(int argc, char **argv) {
  FILE *fing, *fric;
  char *scelte[] = {
		"Uscita",
		"Stampa Ingredienti",
		"Stampa Ricette",
		"Dettagli ingrediente",
		"Dettagli ricetta",
		"Costo ricetta",
		"Apporto calorico ricetta",
		"Ricette dato ingrediente",
		"Nuova ricetta"
	};
  int selezione, fineProgramma = 0;
  char tmp[LEN];
  ingrediente *ing;
  ricetta *r;
  tabIngr *ingredienti;
  tabRicette *ricette;
  if (argc != 3) {
	printf("Uso: %s <file_ingredienti> <file_ricette>\n", argv[0]);
	return -1;
  }

  fing = fopen(argv[1], "r");
  if (fing == NULL)
    exit(-1);
  ingredienti = leggiIngredienti(fing);
  if (ingredienti == NULL)
    exit(-1);
  fclose(fing);
  fric = fopen(argv[2], "r");
  if (fric == NULL)
    exit(-1);
  ricette = leggiRicette(fric, ingredienti);
  if (ricette == NULL)
    exit(-1);
  fclose(fric);

  do {
    stampaMenu(scelte, &selezione);
    switch(selezione) {
      case 0:
        fineProgramma = 1;
		break;
      case 1:
        stampaIngredienti(ingredienti, stdout);
        break;
      case 2:
        stampaRicette(ricette, stdout);
        break;
      case 3: {
        printf("Inserire nome ingrediente: ");
        scanf("%s", tmp);
        ing = cercaIngrediente(tmp, ingredienti);
        if (ing != NULL)
          stampaIngrediente(*ing, stdout);
        }
        break;
      case 4: {
        printf("Inserire nome ricetta: ");
        scanf("%s", tmp);
        stampaRicetta(cercaRicetta(tmp, ricette), stdout);
        }
        break;
      case 5: {
        printf("Inserire nome ricetta: ");
        scanf("%s", tmp);
        r = cercaRicetta(tmp, ricette);
        if (r != NULL)
          printf("Costo: %.2f\n", r->costo);
        }
        break;
      case 6: {
        printf("Inserire nome ricetta: ");
        scanf("%s", tmp);
        r = cercaRicetta(tmp, ricette);
        if (r != NULL)
          printf("Calorie: %.2f\n", r->cal);
        }
        break;
      case 7: {
        printf("Inserire nome ingrediente: ");
        scanf("%s", tmp);
        ing = cercaIngrediente(tmp, ingredienti);
        if (ing != NULL)
          stampaRicetteIngrediente(*ing, stdout);
        }
        break;
      case 8:
        nuovaRicetta(ricette, ingredienti);
        break;
      default:
        printf("Scelta non valida\n");
	break;
    }
  } while(!fineProgramma);
  liberaRicette(ricette);
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
