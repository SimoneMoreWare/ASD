#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LENGTH 30+1
#define fileName "corse.txt"

const char menu[346+1] =	"\n1. Stampa l'intero log;\n"
						 	"2. Ordina il vettore per data e ora;\n"
							"3. Ordina il vettore per codice di tratta;\n"
							"4. Ordina il vettore per stazione di partenza;\n"
							"5. Ordina il vettore per stazione di arrivo;\n"
							"6. Ricerca linearmente una tratta con stazione di partenza.\n"
							"7. Ricerca dicotomicamente una tratta con stazione di partenza.\n"
                            "8. Termina il programma.";

const char header[131+1] = "| CODICE |            PARTENZA            |          DESTINAZIONE          |    DATA    | ORA PARTENZA | ORA ARRIVO | RITARDO (min)";

/*
 * Struttura dati per le scelte
 */
typedef enum {
	p_log = 1,
	o_data,
	o_codice,
	o_partenza,
	o_arrivo,
	r_tratta_lin,
	r_tratta_dic,
	e_fine
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

/*
 * Scambia due puntatori di una varabile di tipo corsa
 * 
 * c1 = primo puntatore
 * c2 = secondo puntatore
 */
void scambiaCorse(corsa* c1, corsa* c2);

/*
 * Ricerca linearmente tutte le istanze della stringa partenza
 * dentro al log 
 * 
 * log = vettore di corse
 * N = dimensione vettore
 * partenza = stringa da ricercare
 * 
 * ritorna se la ricerca ha avuto successo o meno
 */
state ricercaLineare(corsa** log, int N, char* partenza);

/*
 * Ricerca dicotomicamente tutte le istanze della stringa partenza
 * dentro al log 
 * 
 * log = vettore di corse
 * l = estremo inferiore della dimensione del sottovettore
 * r = estremo superiore della dimensione del sottovettore
 * partenza = stringa da ricercare
 * print_header = controlla se è già stato stampato l'header
 * 
 * ritorna se la ricerca ha avuto successo o meno
 */
state ricercaDicotomica(corsa** log, int l, int r, char* partenza, state print_header);

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
	} while(scelta != e_fine);

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
		if(comando >= 1 && comando <= 8) {
			return comando;
		} else {
			printf("Scegli un'opzione valida!\n");
		}
	} while(TRUE);
}

void menuParola(corsa** log, int N, comando_e scelta) {
	int i, j;

	switch(scelta) {
		case p_log: {
			printf("%s \n", header);
			for(i = 0; i < N; i++) {
				stampaCorsa(log[i]);
			}
			break;
		}
		case o_data: {
			for(i = 0; i < N; i++) {
				for(j = 0; j < N-i-1; j++) {
					if(strcmp(log[j]->data, log[j+1]->data) > 0) {
						scambiaCorse(log[j], log[j+1]);
					}
					else if(strcmp(log[j]->data, log[j+1]->data) == 0 
							&& strcmp(log[j]->oraPartenza, log[j+1]->oraPartenza) > 0) {
						scambiaCorse(log[j], log[j+1]);
					}
				}
			}
			break;
		}
		case o_codice: {
			for(i = 0; i < N; i++) {
				for(j = 0; j < N-i-1; j++) {
					if(strcmp(log[j]->codice, log[j+1]->codice) > 0) {
						scambiaCorse(log[j], log[j+1]);
					}
				}
			}
			break;
		}
		case o_partenza: {
			for(i = 0; i < N; i++) {
				for(j = 0; j < N-i-1; j++) {
					if(strcmp(log[j]->partenza, log[j+1]->partenza) > 0) {
						scambiaCorse(log[j], log[j+1]);
					}
				}
			}
			break;
		}
		case o_arrivo: {
			for(i = 0; i < N; i++) {
				for(j = 0; j < N-i-1; j++) {
					if(strcmp(log[j]->destinazione, log[j+1]->destinazione) > 0) {
						scambiaCorse(log[j], log[j+1]);
					}
				}
			}
			break;
		}
		case r_tratta_lin: {
			char partenza[MAX_LENGTH] = "";
			printf("Inserisci la stazione di partenza di cui cercare la tratta: ");
			scanf("%s", partenza);
			if(!ricercaLineare(log, N, partenza)) {
				printf("Non è stata trovata una tratta con %s come stazione di partenza. \n", partenza);
			}
			break;
		}
		case r_tratta_dic: {
			char partenza[MAX_LENGTH] = "";
			printf("Inserisci la stazione di partenza di cui cercare la tratta: ");
			scanf("%s", partenza);
			for(i = 0; i < N; i++) {
				for(j = 0; j < N-i-1; j++) {
					if(strcmp(log[j]->partenza, log[j+1]->partenza) > 0) {
						scambiaCorse(log[j], log[j+1]);
					}
				}
			}
			if(!ricercaDicotomica(log, 0, N-1, partenza, FALSE)) {
				printf("Non è stata trovata una tratta con %s come stazione di partenza. \n", partenza);
			}
			break;
		}
		case e_fine:
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

void scambiaCorse(corsa* c1, corsa* c2) {
	corsa temp = *c2;
	*c2 = *c1;
	*c1 = temp;
}

state ricercaLineare(corsa** log, int N, char* partenza) {
	int i;
	state found = FALSE;
	for(i = 0; i < N; i++) {
		if(strstr(log[i]->partenza, partenza) != NULL) {
			if(!found) {
				printf("%s \n", header);
			}
			stampaCorsa(log[i]);
			found = TRUE;
		}
	}
	return found;
}

state ricercaDicotomica(corsa** log, int l, int r, char* partenza, state print_header) {
	if(l > r) {
		return FALSE;
	}

	state found = FALSE;
	int h = (l+r)/2;
	if (strstr(log[h]->partenza, partenza) != NULL) {
		if (!print_header) {
			printf("%s \n", header);
			print_header = TRUE;
		}
		stampaCorsa(log[h]);
		found = TRUE;
	}

	if (ricercaDicotomica(log, l, h-1, partenza, print_header)) {
		found = TRUE;
	}

	if (ricercaDicotomica(log, h+1, r, partenza, print_header)) {
		found = TRUE;
	}
	return found;
}
