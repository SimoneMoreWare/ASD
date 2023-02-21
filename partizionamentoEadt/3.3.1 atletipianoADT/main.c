#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LEN 50
#define N_SCELTE 11
#define DBG 1

#include "atlList.h"
#include "esArray.h"
#include "catArray.h"

enum { falso, vero };

typedef int bool;

void stampaMenu(char *scelte[], int *selezione);
int main(int argc, char** argv) {

  char *scelte[] = {
		"Uscita",
		"Stampa atleti a video",
		"Stampa atleti su file",
		"Stampa per categoria",
		"Aggiorna monte ore",
		"Ricerca per codice",
		"Ricerca per cognome",
		"Elimina atleta",
		"Aggiungi atleta",
    "Carica/Salva piano",
    "Modifica piano"
	};

  char codiceRicerca[LEN], cognomeRicerca[LEN], nomeFile[25];
  int selezione, nCharConfronto;
	bool fineProgramma = falso;
	atl_t a;

  atlList_t atleti = atlListInit();
  catArray_t categorie = catArrayInit();
  esArray_t esercizi = esArrayInit();

  caricaAnagrafica(atleti, categorie, "atleti.txt");
#if DBG
  stampaAnagrafica(atleti, categorie, esercizi, NULL);
#endif
  caricaEsercizi(esercizi, "esercizi.txt");
#if DBG
  stampaEsercizi(esercizi, NULL);
#endif

  do {
		stampaMenu(scelte, &selezione);
		switch(selezione){

			case 0: {
				fineProgramma = vero;
		   } break;

			case 1: {
				stampaAnagrafica(atleti, categorie, esercizi, NULL);
			} break;

			case 2: {
				printf("Inserire nome file\n");
				scanf("%s",nomeFile);
				stampaAnagrafica(atleti, categorie, esercizi, nomeFile);
			} break;

			case 3: {
				printf("Stampa per categoria\n");
				stampaPerCategoria(atleti, categorie, esercizi);
			} break;

			case 4: {
				printf("Inserire codice atleta: ");
				scanf("%s", codiceRicerca);
				a = ricercaCodice(atleti, codiceRicerca);
				if(a != NULL) {
          atletaAggiornaOre(a);
				}
				else
					printf("Atleta non presente in elenco\n");
			} break;

			case 5: {
				printf("Inserire codice: ");
				scanf("%s", codiceRicerca);
				a = ricercaCodice(atleti, codiceRicerca);
				if(a != NULL) {
				  stampaAtleta(a, categorie, esercizi, stdout);
				}
			} break;

			case 6:{
				printf("Inserire cognome atleta: ");
				scanf("%s%n", cognomeRicerca, &nCharConfronto);
				ricercaCognome(atleti, categorie, esercizi, cognomeRicerca, nCharConfronto-1);
			} break;

			case 7: {
				printf("Inserire codice: ");
				scanf("%s", codiceRicerca);
				elimina(atleti, codiceRicerca);
			} break;

			case 8: {
				aggiungi(atleti, categorie);
			} break;

			case 9: {
				printf("Inserire codice: ");
				scanf("%s", codiceRicerca);
				a = ricercaCodice(atleti, codiceRicerca);
        if(a != NULL) atletaGestionePiano(a, esercizi);
			} break;

			case 10: {
				printf("Inserire codice: ");
				scanf("%s", codiceRicerca);
				a = ricercaCodice(atleti, codiceRicerca);
        if(a != NULL) {
          aggiornaEsercizioInPiano(a->piano, esercizi);
				}
			} break;

			default:{
				printf("Scelta non valida\n");
			} break;
		}
	} while(!fineProgramma);

  freeCategorie(categorie);
  freeEsercizi(esercizi);
  freeAtleti(atleti);
  free(esercizi);
  free(categorie);
  free(atleti);

	return 0;
}

void stampaMenu(char *scelte[], int *selezione){
  int i=0;
  printf("\nMENU'\n");
	for(i=0;i<N_SCELTE;i++) printf("%2d > %s\n",i,scelte[i]);
  scanf(" %d",selezione);
}


