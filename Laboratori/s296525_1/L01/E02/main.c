#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LENGTH 30+1
#define fileName "corse.txt"

const char menu[422+1] =	"1. Elenca tutte le corse partite in un certo intervallo di date;\n"
						 			"2. Elenca tutte le corse partite da una certa fermata;\n"
									"3. Elenca tutte le corse aventi una data destinazione (capolinea);\n"
									"4. Elenca tutte le corse che hanno raggiunto la destinazione in ritardo, in un certo intervallo di date;\n"
									"5. Elenca il ritardo complessivo accumulato dalle corse identificate da un certo codice di tratta;\n"
									"6. Termina il programma.\n";

const char header[131+1] = "| CODICE |            PARTENZA            |          DESTINAZIONE          |    DATA    | ORA PARTENZA | ORA ARRIVO | RITARDO (min)";

/*
 * Struttura dati per le scelte
 */
typedef enum {
	r_date = 1,
	r_partenza,
	r_capolinea,
	r_ritardo,
	r_ritardo_tot,
	r_fine
} comando_e;

/*
 * Struttura dati booleana
 */
typedef enum {
	FALSE,
	TRUE
} state;

/*
 * Struttura dati per la corsa
 */
typedef struct {
	char codice[6+1];
	char partenza[MAX_LENGTH];
	char destinazione[MAX_LENGTH];
	char data[10+1];
	char oraPartenza[8+1];
	char oraArrivo[8+1];
	int ritardo;
} corsa;

/*
 * Esegue la lettura di un comando
 * e lo codifica nel tipo comando_e
 *
 * ritorna un valore di comando_e
 */
comando_e leggiComando();

/*
 * Esegue l'operazione definita dalla scelta
 *
 * log = vettore di corse
 * N = dimensione vettore
 * scelta = scelta inserita
 */
void menuParola(corsa** log, int N, comando_e scelta);

/*
 * Stampa la struttura corsa come una tabella
 *
 * c = elemento di tipo corsa da stampare
 */
void stampaCorsa(corsa* c);

int main() {
	FILE *fLog;
	int i, N;

	if((fLog = fopen(fileName, "r")) == NULL) {
      	printf("Non e' stato possibile aprire il file.");
      	return 1;
	}
	if(!feof(fLog)) {
		fscanf(fLog, " %d ", &N);
	} else {
		printf("Il file e' vuoto.\n");
		return 2;
	}

	// allocazione memoria per log
    corsa** log = (corsa**)calloc(N, sizeof(corsa*));
    for(i = 0; i < N; i++) {
     	log[i] = (corsa*)calloc(1, sizeof(corsa));
     	fscanf(fLog, " %6s %30s %30s %30s %30s %30s %d", log[i]->codice, log[i]->partenza, log[i]->destinazione, log[i]->data, log[i]->oraPartenza, log[i]->oraArrivo, &log[i]->ritardo);
    }
    fclose(fLog);

	// inserimento scelta ed esecuzione comando
	comando_e scelta;
	do {
		scelta = leggiComando();
		menuParola(log, N, scelta);
	} while(scelta != r_fine);

	// deallocazione memoria per log
	for(i = 0; i < N; i++) {
		free(log[i]);
	}
	free(log);
	return 0;
}

comando_e leggiComando() {
	int comando = 0;
	printf("%s\n", menu);
	do {
		scanf("%d", &comando);
		if(comando >= 1 && comando <= r_fine) {
			return comando;
		} else {
			printf("Scegli un'opzione valida!\n");
		}
	} while(TRUE);
}

void menuParola(corsa** log, int N, comando_e scelta) {
	int i;
	state flag = FALSE;

	switch(scelta) {
		case r_date: {
			char dPartenza[10+1], dArrivo[10+1];
			printf("Inserisci la data di partenza e la data di arrivo (formato yyyy/mm/dd): ");
			scanf("%s %s", dPartenza, dArrivo);
			for(i = 0; i < N; i++) {
				if(strcmp(log[i]->data, dPartenza) >= 0 && strcmp(log[i]->data, dArrivo) <= 0) {
					if(!flag) {
						printf("%s\n", header);
					}
					stampaCorsa(log[i]);
					flag = TRUE;
				}
			}
			printf("\n");
			break;
		}
		case r_partenza: {
			char partenza[MAX_LENGTH+1];
			printf("Inserisci la stazione di partenza: ");
			scanf("%s", partenza);
			for(i = 0; i < N; i++) {
				if(strcmp(log[i]->partenza, partenza) == 0) {
					if(!flag) {
						printf("%s\n", header);
					}
					stampaCorsa(log[i]);
					flag = TRUE;
				}
			}
			printf("\n");
			break;
		}
		case r_capolinea: {
			char arrivo[MAX_LENGTH+1];
			printf("Inserisci la stazione di arrivo: ");
			scanf("%s", arrivo);
			for(i = 0; i < N; i++) {
				if(strcmp(log[i]->destinazione, arrivo) == 0) {
					if(!flag) {
						printf("%s\n", header);
					}
					stampaCorsa(log[i]);
					flag = TRUE;
				}
			}
			printf("\n");
			break;
		}
		case r_ritardo: {
			char dPartenza[10+1], dArrivo[10+1];
			printf("Inserisci la data di partenza e la data di arrivo (formato yyyy/mm/dd): ");
			scanf("%s %s", dPartenza, dArrivo);
			for(i = 0; i < N; i++) {
				if(strcmp(log[i]->data, dPartenza) >= 0 && strcmp(log[i]->data, dArrivo) <= 0 && log[i]->ritardo > 0) {
					if(!flag) {
						printf("%s\n", header);
					}
					stampaCorsa(log[i]);
					flag = TRUE;
				}
			}
			printf("\n");
			break;
		}
		case r_ritardo_tot: {
			int ritardo = 0;
			char codice[6+1];
			printf("Inserisci il codice della tratta (formato GTTXXX): ");
			scanf("%s", codice);
			for(i = 0; i < N; i++) {
				if(strcmp(log[i]->codice, codice) == 0) {
					ritardo += log[i]->ritardo;
				}
			}
			printf("Il ritardo complessivo della tratta equivale a %d minuti.\n", ritardo);
			printf("\n");
			break;
		}
		case r_fine:
			printf("Termino il programma...\n");
			break;
		default:
			printf("Scegli un'opzione valida!\n");
	}
}

void stampaCorsa(corsa* c) {
	int dimPart = MAX_LENGTH - strlen(c->partenza) - 1,
	dimDest = MAX_LENGTH - strlen(c->destinazione) - 1;
	printf(	"| %s | %s%*c | %s%*c | %s | %s%*c | %s%*c | %d \n",
				c->codice,
				c->partenza, dimPart, ' ',
				c->destinazione, dimDest, ' ',
				c->data,
				c->oraPartenza, 4, ' ',
				c->oraArrivo, 2, ' ',
				c->ritardo
	);
}
