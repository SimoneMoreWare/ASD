#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "schema.h"
#include "parole.h"

typedef struct{
	Word *words;
}Soluzione;

char **leggiFile(Schema s, FILE *f);
char **malloc2D(int nr, int nc);
int verificaSchema(Schema *s, Parole *p, char **m);
void getParola(char *parola, char **m, int nr, int nc, int lun, int rI, int cI, char dir);
void free2D(char **mat, int nr);
void solve(Schema *s, Parole *p);
void solve_r(Schema *s, Parole *p, Soluzione *sol, char **griglia, int pos, int *trovato);
int checkSol(Schema *s, Soluzione *sol, char *parolaMatrice, char *scelta, int lun);
void copiaParolaGriglia(char **m, int rI, int cI, int lun, char dir, char *str);

int main()
{
    FILE *f;
    Schema s;
    Parole p;
    char **mat;

    f=fopen("schema.txt", "r");
    if(f==NULL)
        exit(-1);
    s=SCHEMAread(f);
    fclose(f);

    f=fopen("parole.txt", "r");
    if(f==NULL)
        exit(-1);
    p=PAROLEread(f);
    fclose(f);

    f=fopen("fatto.txt", "r");
    if(f==NULL)
        exit(-1);
    mat=leggiFile(s, f);

    printf("---PROBLEMA DI VERIFICA---\n");
    if(verificaSchema(&s, &p, mat)==VERO){
        printf("Soluzione valida.\n\n");
    }
    else{
        printf("Soluzione non valida.\n\n");
    }

    printf("---PROBLEMA DI RICERCA---\n");
    solve(&s, &p);

    free2D(mat, s.nr);
    SCHEMAclear(s);
    PAROLEclear(p);
    return 0;
}




void getParola(char *parola, char **m, int nr, int nc, int lun, int rI, int cI, char dir){
	int riga, colonna, index=0;
	switch(dir){
          case 'V':
            for(riga=rI; riga<rI+lun; riga++){
                  parola[index++]=m[riga][cI];
            }
            parola[index]='\0';
            break;
          case 'O':
            for(colonna=cI; colonna<cI+lun; colonna++)
                  parola[index++]=m[rI][colonna];
            parola[index]='\0';
            break;
      }
}




int verificaSchema(Schema *s, Parole *p, char **m){
	int i;
	char parola[MAX+1];
	for(i=0; i<s->dim; i++){
		getParola(parola, m, s->nr, s->nc, s->posizioni[i].lun, s->posizioni[i].r, s->posizioni[i].c, s->posizioni[i].dir);
        if(WORDLUNisThere(p->parole[strlen(parola)-1], WORDcrea(parola))==FALSO)
            return FALSO;
	}
	return VERO;
}




char **leggiFile(Schema s, FILE *f){
    char **mat;
    int i, j;
    mat=malloc2D(s.nr, s.nc);
    for(i=0; i<s.nr; i++){
        for(j=0; j<s.nc; j++){
            fscanf(f, "%c", &mat[i][j]);
        }
        fscanf(f, "%*c");
    }
    return mat;
}



char **malloc2D(int nr, int nc){
    char **m;
    int i;
    m=(char**)malloc(nr*sizeof(char*));
    if(m==NULL)
        exit(EXIT_FAILURE);
    for(i=0; i<nr; i++){
        m[i]=(char*)malloc(nc*sizeof(char));
        if(m[i]==NULL)
            exit(EXIT_FAILURE);
    }
    return m;
}



void free2D(char **mat, int nr){
    int i;
    if(mat!=NULL){
        for(i=0; i<nr; i++){
            if(mat[i]!=NULL)
                free(mat[i]);
        }
        free(mat);
    }
    return;
}




//HO USATO LE DISPOSIZIONI SEMPLICI IN QUANTO L'ORDINE DI INSERIMENTO DI UNA PAROLA CONTA E ALL'INTERNO DELLA GRIGLIA OGNI PAROLA PUO COMPARIRE UNA SOLA VOLTA
void solve(Schema *s, Parole *p){
	char **griglia=malloc2D(s->nr, s->nc);
	int i, j;
	Soluzione sol;
	int trovato=FALSO;

	for(i=0; i<s->nr; i++)
         for(j=0; j<s->nc; j++)
              griglia[i][j]=' ';

	sol.words=(Word*)malloc(s->dim*sizeof(Word));
	if(sol.words==NULL)
		exit(-1);
	solve_r(s, p, &sol, griglia, 0, &trovato);
	if(trovato==VERO){
		printf("Soluzione trovata.\n");
        printf("\nElenco parole:\n");
        for(i=0; i<s->dim; i++){
            printf("%s ", sol.words[i].parola);
		}
        printf("\n\nGriglia:\n");
		for(i=0; i<s->nr; i++){
            for(j=0; j<s->nc; j++){
                printf("%c", griglia[i][j]);
            }
            printf("\n");
		}
	}
	else
		printf("soluzione inesistente.");

    free(sol.words);
    free2D(griglia, s->nr);
    return;
}




void solve_r(Schema *s, Parole *p, Soluzione *sol, char **griglia, int pos, int *trovato){
	int i, nParole;
	char parolaMatrice[MAX+1];
	int lunghezza, rI, cI;
	char dir;
	Word *words;

	if(pos>=s->dim){
		(*trovato)=VERO;
		return;
	}

	lunghezza=s->posizioni[pos].lun;
	rI=s->posizioni[pos].r;
	cI=s->posizioni[pos].c;
	dir=s->posizioni[pos].dir;
	getParola(parolaMatrice, griglia, s->nr, s->nc, lunghezza, rI, cI, dir);
	words=WORDLUNgetParole(p->parole[lunghezza-1]);
	nParole=WORDLUNgetNumParole(p->parole[lunghezza-1]);
	for(i=0; i<nParole; i++){
		if(words[i].preso==VERO || checkSol(s, sol, parolaMatrice, words[i].parola, lunghezza)==FALSO)
            continue;
        words[i].preso=VERO;
        sol->words[pos]=words[i];
        copiaParolaGriglia(griglia, rI, cI, lunghezza, dir, words[i].parola);
        solve_r(s, p, sol, griglia, pos+1, trovato);
        if(*trovato==VERO){
            break;
        }
        words[i].preso=FALSO;
        copiaParolaGriglia(griglia, rI, cI, lunghezza, dir, parolaMatrice);
    }
	return;
}




int checkSol(Schema *s, Soluzione *sol, char *parolaMatrice, char *scelta, int lun){
	int i;
	for(i=0; i<lun; i++){
		if(isalpha(parolaMatrice[i]) && parolaMatrice[i]!=scelta[i])
			return FALSO;
	}
	return VERO;

}



void copiaParolaGriglia(char **m, int rI, int cI, int lun, char dir, char *str){
	int riga, colonna;
	int index=0;
	switch(dir){
		case 'O':
			for(colonna=cI; colonna<cI+lun; colonna++){
                m[rI][colonna]=str[index++];
			}
			break;
		case 'V':
			for(riga=rI; riga<rI+lun; riga++){
                m[riga][cI]=str[index++];
			}
			break;
	}
      return;
}
