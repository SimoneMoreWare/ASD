/*   main.c
 *   @author  : Gabriele Iurlaro
 *   @  site  : http://iurlaro.com
 *   @Modified: 22/12/2020, 19:46:32
*/
#include <stdio.h>
#include <stdlib.h>
#define DBG
typedef struct{
    char c1,c2;
    int val1,val2;
}tessera_t;

typedef struct{
    int t, r;
}casella_t;

tessera_t ruotaTessera(tessera_t t);
int calcolaPunteggio(tessera_t *tessere, int n, casella_t **board, int r, int c);
void risolvi(tessera_t *tessere, int n, casella_t **board, int r, int c, int *mark);
void risolviR(int pos, tessera_t *tessere, int *mark, int n, casella_t **board, int r, int c,casella_t **bestboard, int *valore);

int main(){
    FILE *in;
    int n,r,c,i,j,*mark;
    tessera_t *tessere;
    casella_t **m;
    in = fopen("tiles.txt","r");
    fscanf(in,"%d\n",&n);
    tessere = malloc(n* sizeof(tessera_t));
    mark = calloc(n, sizeof(int));
    for(i=0;i<n;i++){
        fscanf(in,"%c %d %c %d\n",&tessere[i].c1,&tessere[i].val1,&tessere[i].c2,&tessere[i].val2);
    }
#ifdef DBG
    printf("Tessere:\n");
    for(i=0;i<n;i++){
        printf("%c %d %c %d\n",tessere[i].c1,tessere[i].val1,tessere[i].c2,tessere[i].val2);
    }
#endif
    fclose(in);
    in = fopen("board.txt","r");
    fscanf(in, "%d %d",&r,&c);
    m = malloc(r* sizeof(casella_t*));
    for(i=0;i<r;i++)
        m[i] = malloc(c* sizeof(casella_t));
    for(i=0;i<r;i++)
        for(j=0;j<c;j++)
            fscanf(in, "%d/%d", &m[i][j].t,&m[i][j].r);
#ifdef DBG
    printf("Tavola:\n");
    for(i=0;i<r;i++){
        for(j=0;j<c;j++) {
            printf("%d/%d ", m[i][j].t, m[i][j].r);
            if(m[i][j].t != -1)
                mark[m[i][j].t] = 1;

        }
        printf("\n");
        }
    printf("\n\n\n");
#endif
    risolvi(tessere,n,m,r,c,mark);
    return 0;
}

void risolviR(int pos, tessera_t *tessere, int *mark, int n, casella_t **board, int r, int c,casella_t **bestboard, int *valore){
    int i,j,k,cpunteggio=0;
    i = pos / r;
    j = pos % c;
    if(pos >= r*c){
        cpunteggio = calcolaPunteggio(tessere,n,board,r,c);
        //printf("%d\n",cpunteggio);
        if(cpunteggio > *valore){
            *valore = cpunteggio;
            for(i=0;i<r;i++)
                for (j = 0; j < c; j++)
                    bestboard[i][j] = board[i][j];
        }
        return;
    }
    if(board[i][j].t != -1)
        return risolviR(pos + 1, tessere, mark, n, board, r, c, bestboard, valore);
    for(k=0;k<n;k++) {
        if (mark[k] == 0) {
            mark[k] = 1;
            board[i][j].t = k;
            board[i][j].r = 0;
            risolviR(pos + 1, tessere, mark, n, board, r, c, bestboard, valore);
            board[i][j].r = 1;
            risolviR(pos + 1, tessere, mark, n, board, r, c, bestboard, valore);
            board[i][j].t = -1;
            mark[k] = 0;
        }
    }
}

void risolvi(tessera_t *tessere, int n, casella_t **board, int r, int c,int *mark){
    casella_t **bestboard;
    int valore=0,i,j;
    bestboard = malloc(r* sizeof(casella_t*));
    for(i=0; i<r; i++)
        bestboard[i] = malloc(c* sizeof(casella_t));
    risolviR(0,tessere,mark,n,board,r,c,bestboard,&valore);
    printf("Soluzione migliore a punteggio: %d\n\n",valore);
    for(i=0;i<r;i++){
        for(j=0;j<c;j++)
            printf("%d/%d ",bestboard[i][j].t, bestboard[i][j].r);
        printf("\n");
    }
}

tessera_t ruotaTessera(tessera_t t){
    tessera_t tmp;
    tmp.c1 = t.c2;
    tmp.c2 = t.c1;
    tmp.val1 = t.val2;
    tmp.val2 = t.val1;
    return tmp;
}

int calcolaPunteggio(tessera_t *tessere, int n, casella_t **board, int r, int c){
    int pverticale=0,porizzontale=0;
    int i,j,count=0;
    tessera_t tmp[n];
    for(i=0;i<n;i++){
        tmp[i] = tessere[i];
    }
    for(i=0; i<r; i++)
        for(j=0; j<r; j++)
            if(board[i][j].r == 1)
                tmp[board[i][j].t] = ruotaTessera(tessere[board[i][j].t]);
    for(i=0; i<r; i++){
        count = 0;
        for(j=0; j<c; j++)
            if(tmp[board[i][j].t].c1 == tmp[board[i][0].t].c1)
                count++;
        if(count == c)
            for(j=0;j<c;j++)
                porizzontale += tmp[board[i][j].t].val1;
    }
    for(j=0; j<c; j++){
        count = 0;
        for(i=0; i<r; i++)
            if(tmp[board[i][j].t].c2 == tmp[board[0][j].t].c2)
                count++;
        if(count == r)
            for(i=0;i<r;i++)
                pverticale += tmp[board[i][j].t].val2;
    }
    return pverticale+porizzontale;
}

