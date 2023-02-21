/*   main.c
 *   @author  : Gabriele Iurlaro
 *   @  site  : http://iurlaro.com
 *   @Modified: 22/12/2020, 19:42:12
*/
#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int n;
    int *len;
}vincolo;

typedef struct{
    int N,M;
    vincolo *riga;
    vincolo *colonna;
    int **tab;
}Nonogram;

Nonogram readFile(FILE *in){
    Nonogram table;
    int i,j;
    fscanf(in, "%d",&(table.N));
    table.riga = malloc(table.N* sizeof(vincolo));
    for(i=0; i<table.N; i++){
        fscanf(in,"%d",&(table.riga[i].n));
        table.riga[i].len = malloc(table.riga[i].n* sizeof(int));
        for(j=0; j<table.riga[i].n; j++)
            fscanf(in, "%d", &(table.riga[i].len[j]));
    }
    fscanf(in, "%d", &(table.M));
    table.colonna = malloc(table.M* sizeof(vincolo));
    for(i=0; i<table.M; i++){
        fscanf(in,"%d",&(table.colonna[i].n));
        table.colonna[i].len = malloc(table.colonna[i].n* sizeof(int));
        for(j=0; j<table.colonna[i].n; j++)
            fscanf(in, "%d", &(table.colonna[i].len[j]));
    }
    table.tab = malloc(table.N* sizeof(int));
    for(i=0; i < table.N; i++)
        table.tab[i] = malloc(table.M* sizeof(int));
    return table;
}

int check(Nonogram t,int **sol, int n, int m){
    int righeok = 1, colonneok = 1;
    //TODO scrivere funzione di check
    return (righeok && colonneok);
}

int generaSoluzioneR(int pos, Nonogram t){
    int i,j;
    if(pos == t.N*t.M){
        return check(t,t.tab,t.N,t.M);
    }
    i = pos / t.N;
    j = pos%t.M;
    t.tab[i][j] = 1;
    if(generaSoluzioneR(pos+1, t))
        return 1;
    t.tab[i][j] = 0;
    if(generaSoluzioneR(pos+1, t))
        return 1;
    return 0;
}
void generaSoluzione(Nonogram t){
    int i,j;
    generaSoluzioneR(0, t);
    for(i=0; i<t.N; i++){
        for(j=0; j<t.M; j++)
            printf("%d ",t.tab[i][j]);
        printf("\n");
    }
}
int main(int argc, char **argv){
    Nonogram tabella;
    int **sol,n,m,i,j;
    FILE *in;
    in = fopen("file.txt", "r");
    tabella = readFile(in);
    fclose(in);
    in = fopen("soluzione.txt", "r");
    fscanf(in, "%d %d", &n, &m);
    sol = malloc(n*sizeof(int*));
    for(i=0; i<n; i++){
        sol[i] = malloc(m* sizeof(int));
    }
    for(i=0; i<n; i++)
        for(j=0; j<m; j++)
            fscanf(in, "%d", &sol[i][j]);
    fclose(in);
    if(check(tabella, sol, n, m))
        printf("Soluzione valida\n");
    else
        printf("soluzione non valida\n");
    printf("Genero una soluzione:\n\n");
    generaSoluzione(tabella);
    return 0;
}