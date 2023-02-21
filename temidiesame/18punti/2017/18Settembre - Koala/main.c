/*   main.c
 *   @author  : Gabriele Iurlaro
 *   @  site  : http://iurlaro.com
 *   @Modified: 22/12/2020, 19:43:44
*/
#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int id;
    int n;
    int *habitat;
}koala_t;

typedef struct{
    int id;
    int n;
    int *membri;
}famiglia_t;

void leggiKoala(FILE *in, koala_t *koala, int N){
    int i, j, id, nalberi;
    for(i=0; i<N; i++){
        fscanf(in, "K%d %d", &id, &nalberi);
        koala[id].id = id;
        koala[id].n = nalberi;
        koala[id].habitat = malloc(nalberi* sizeof(int));
        for(j=0; j<nalberi; j++){
            fscanf(in, "%d", &koala[id].habitat[j]);
        }
    }
}

void leggiFamiglie(FILE *in, famiglia_t *famiglia, int S){
    int i,j, id, nkoala;
    for(i=0; i<S; i++){
        fscanf(in, "F%d %d", &id, &nkoala);
        famiglia[id].id = id;
        famiglia[id].n = nkoala;
        famiglia[id].membri = malloc(nkoala* sizeof(int));
        for(j=0; j<nkoala; j++)
            fscanf(in, "F%d", &famiglia[id].membri[j]);
    }
}

int **generaEnemies(FILE *in, int S){
    int **m,i,j;
    m = malloc(S* sizeof(int*));
    for(i=0; i<S; i++)
        m[i] = calloc(S, sizeof(int));
    while(fscanf(in,"F%d F%d",&i,&j) == 2){
        m[i][j] = 1;
        m[j][i] = 1;
    }
    return m;
}

int checkAlbero(koala_t koala, int albero){
    int i;
    for(i=0; i<koala.n; i++)
        if(albero == koala.habitat[i])
            return 1;
    return 0;
}

//TODO check se ci sono koala nemici sullo stesso albero
int checkSol(int *sol, koala_t *koala, famiglia_t* famiglie, int **enemies, int N, int S, int T, int m){
    int i, j, flag = 1, *t;
    t = calloc(T, sizeof(int));
    for(i=0; i<N; i++){
        t[sol[i]]++;
        if(!checkAlbero(koala[i], sol[i])){
            return 0;
        }
    }
    for(i=0; i<T; i++)
        if(t[i] > m)
            return 0;
    return 1;
}

int generaPartizioni(int pos,int *sol, int N, int S, int T, int m,int p, koala_t *koala, famiglia_t *famiglie, int **enemies){
    int i;
    if(pos >= N){
        if(checkSol(sol, koala, famiglie, enemies, N, S, T, m))
            return 1;
        return 0;
    }
    for(i=0; i<p; i++){
        sol[pos] = i;
        if(generaPartizioni(pos+1, sol, N, S, T, m, p, koala, famiglie, enemies))
            return 1;
    }
    if(generaPartizioni(pos+1, sol, N, S, T, m, p+1, koala, famiglie, enemies))
        return 1;
    return 0;
}

void generaSoluzione(koala_t *koala, famiglia_t *famiglie, int **enemies, int N, int S, int T, int m){
    int *sol,i;
    sol = malloc(N* sizeof(int));
    if(generaPartizioni(0, sol, N, S, T, m, 0, koala, famiglie, enemies))
        for(i=0; i<N; i++){
            printf("K%d %d\n",i, sol[i]);
        }
    free(sol);
}

int main(int argc, char **argv){
    int N, T, S, m;
    int i, *sol, id, t;
    koala_t *koala;
    famiglia_t *famiglie;
    int **enemies;
    FILE *in;
    N = atoi(argv[1]);
    T = atoi(argv[2]);
    S = atoi(argv[3]);
    m = atoi(argv[4]);
    koala = malloc(N * sizeof(koala_t));
    famiglie = malloc(S * sizeof(famiglia_t));
    sol = malloc(N* sizeof(int));
    in = fopen("habitat.txt", "r");
    leggiKoala(in, koala, N);
    fclose(in);
    in = fopen("families.txt", "r");
    leggiFamiglie(in, famiglie, S);
    fclose(in);
    in = fopen("enemies.txt", "r");
    enemies = generaEnemies(in, S);
    fclose(in);
    in = fopen("solution.txt", "r");
    for(i=0; i<N; i++) {
        fscanf(in, "%d %d", &id, &t);
        sol[id] = t;
    }
    fclose(in);
    if(checkSol(sol, koala, famiglie, enemies, N, S, m, T))
        printf("La soluzioen data in input è valida.\n");
    else
        printf("La soluzione in input non è valida. \n");
    generaSoluzione(koala, famiglie, enemies, N, S, T, m);
}