#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N_SCELTE 11
#define DBG 1

#include "atleti.h"
#include "esercizi.h"

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
  int selezione, nCharConfronto, nuoveOre;
  bool fineProgramma = falso;
  atleta_t a;

  tabAtleti *atleti = calloc(1, sizeof(tabAtleti));
  categorie_t *categorie = calloc(1, sizeof(categorie_t));
  tabEser *esercizi = calloc(1, sizeof(tabEser));

  caricaAnagrafica(atleti, categorie);
#if DBG
  stampaAnagrafica(atleti, categorie, NULL);
#endif
  caricaEsercizi(esercizi);
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
				stampaAnagrafica(atleti, categorie, NULL);
			} break;

			case 2: {
				printf("Inserire nome file\n");
				scanf("%s",nomeFile);
				stampaAnagrafica(atleti, categorie, nomeFile);
			} break;

			case 3: {
				printf("Stampa per categoria\n");
				stampaPerCategoria(atleti, categorie);
			} break;

			case 4: {
				printf("Inserire codice atleta: ");
				scanf("%s", codiceRicerca);
                printf("Inserire il nuovo monte ore settimanale: ");
				scanf("%d", &nuoveOre);
				if(ricercaCodiceModifica(atleti, codiceRicerca, nuoveOre) != 0)
					printf("Monte ore di %s modificato\n", codiceRicerca);
				else
					printf("Atleta non presente in elenco\n");
			} break;

			case 5: {
				printf("Inserire codice: ");
				scanf("%s", codiceRicerca);
                if(ricercaCodice(atleti, codiceRicerca, &a) != 0)
				  stampaAtleta(&a, categorie, stdout);
			} break;

			case 6:{
				printf("Inserire cognome atleta: ");
				scanf("%s%n", cognomeRicerca, &nCharConfronto);
				ricercaCognome(atleti, categorie, cognomeRicerca, nCharConfronto-1);
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
        ricercaCodiceCaricaPiano(atleti, esercizi, codiceRicerca);
			} break;

			case 10: {
				printf("Inserire codice: ");
				scanf("%s", codiceRicerca);
				ricercaCodiceModificaPiano(atleti, esercizi, codiceRicerca);
			} break;

			default:{
				printf("Scelta non valida\n");
			} break;
		}
	} while(!fineProgramma);
        liberaEsercizi(esercizi);
        liberaAtleti(atleti);
        liberaCategorie(categorie);
        free(atleti);
        free(categorie);
        free(esercizi);
	return 0;
}

void stampaMenu(char *scelte[], int *selezione){
  int i=0;
  printf("\nMENU'\n");
	for(i=0;i<N_SCELTE;i++) printf("%2d > %s\n",i,scelte[i]);
  scanf(" %d",selezione);
}


