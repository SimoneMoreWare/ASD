#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUT_FILE "paste.txt"
#define MAX_C 20

typedef struct {

	char* nome;
	int peso;
	int quantita;

} pasticcino;

int comb_rip(int start, pasticcino* paste, int np, int peso_target, int* curr_sol, int curr_peso, int* best_sol, int* best_peso);

int main (int argc, char** argv){

	FILE* fp = NULL;
	pasticcino* paste = NULL;
	int* curr_sol = NULL;
	int* best_sol = NULL;
	int curr_peso, best_peso, np, peso_target, i;
	char tmp[MAX_C+1];

	curr_peso = best_peso = np = peso_target = i = 0;
	fp = fopen(INPUT_FILE,"r");
	if (fp == NULL){
		printf("Errore, impossibile aprire il file %s\n",INPUT_FILE);
		return -1;
	}

	fscanf(fp, "%d", &np);
	if(np <= 0){
		printf("Errore, numero di pasticcini nel file errato");
		return -1;
	}

	paste = (pasticcino*) malloc (np*sizeof(pasticcino));
	if(paste == NULL){
		printf("Impossibile allocare il vettore dinamico di pasticcini");
		return -1;
	}

	for(i=0; i<np; i++){
		fscanf(fp,"%s %d %d", tmp, &paste[i].peso, &paste[i].quantita);
		paste[i].nome = strdup(tmp);
	}

	printf("Pasticcini a disposizione:\n");
	for(i=0; i<np; i++){
		printf("%d\t%s (%dgr)\n",paste[i].quantita, paste[i].nome, paste[i].peso);
	}

	printf("Inserire il peso del vassoio da comporre (in grammi): ");
	scanf("%d", &peso_target);
	if(peso_target <= 0){
		printf("Errore, peso non valido");
		return -1;
	}

	curr_sol = (int*) malloc (np*sizeof(int));
        best_sol = (int*) malloc (np*sizeof(int));
	if(curr_sol == NULL || best_sol == NULL){
		printf("Impossibile allocare i vettori dinamici per il calcolo della soluzione");
		return -1;
	}
	for(i=0; i<np; i++){
		curr_sol[i] = 0;
		best_sol[i] = 0;
	}

	printf("Il vassoio composto pesa ");
	if(comb_rip(0,paste,np,peso_target,curr_sol, curr_peso, best_sol, &best_peso) == 1){
		printf("%d grammi (esattamente il peso richiesto)\n", best_peso);
	}else{
		printf("%d grammi\n", best_peso);
	}

	printf("Composizione del vassoio:\n");
	for(i=0; i<np; i++){
		printf("%d\t%s\n",best_sol[i], paste[i].nome);
	}
        free(curr_sol);
        free(best_sol);
        for(i=0; i<np; i++) {
          free(paste[i].nome);
        }
        free(paste);
        fclose(fp);
	return 0;
}


int comb_rip(int start, pasticcino* paste, int np, int peso_target, int* curr_sol, int curr_peso, int* best_sol, int* best_peso){
  int i;

  if (*best_peso < curr_peso){
    *best_peso = curr_peso;
    for(i=0; i<np; i++)
      best_sol[i] = curr_sol[i];
      /* peso target raggiunto esattamente -> termino tutta la ricorsione */
    if(*best_peso == peso_target)
      return 1;
  }

  for(i=start; i<np; i++){
    /* controllo se questa tipologia ha paste disponibili e se ce ne sta una */
    if( (paste[i].quantita > 0) && (curr_peso+paste[i].peso <= peso_target) ){
      /* aggiunto il pasticcino */
      paste[i].quantita--;
      curr_peso += paste[i].peso;
      curr_sol[i]++;
      /* ricorro sulla stessa tipologia (nel caso ci siano altre paste disponibili) */
      if(comb_rip(i,paste,np,peso_target,curr_sol,curr_peso,best_sol,best_peso) == 1)
        return 1;
      /* backtrack */
      paste[i].quantita++;
      curr_peso -= paste[i].peso;
      curr_sol[i]--;
  }
}

 return 0;
}
