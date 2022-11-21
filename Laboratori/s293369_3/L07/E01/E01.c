#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXE    5
#define MAXDIAG 3
#define DIFFICULT_EXTREME 8

typedef enum {transizione, indietro, avanti} tipologia;
typedef enum {spalle, fronte} direzione;
typedef enum {no_seguito, seguito} precendenza;
typedef enum {FALSE, TRUE} finale;

typedef struct {
    char * nome;
    tipologia tipo;
    direzione ingresso, uscita;
    precendenza prec;
    finale fin;
    float val;
    int difficolta;
} element;
typedef struct {
    int indexElement[MAXE];
    int n;
    float val;
    int difficolta;
} diagonal;

int leggifile(FILE *fp, element ** p_elemento);
void elementRead(FILE *fp, element * elemento);
void elementFree(element *elemento);
void listaFree(element * elementi, int n);

int generazione(diagonal  ** p_diag, element * elemento, int n_el, int DD, int * p_ndiagMAX);
void reallocazione_totale(diagonal ** p_diag, int * p_ndiagMAX);
void disp_rip(element * elemento, diagonal ** p_diag, diagonal * p_diagTMP, int * p_ndiagMAX, int * p_n_actual, int n_el, int DD, int pos);
int compatible_diagonal(diagonal * p_diagTMP, int pos, element * elemento, int i, int DD);
int see_acrobatic( diagonal * p_diagTMP, element * elemento, int j);
void find_sol(diagonal * diag, element * elemento, int ndiagEFF, int DP);
void powerset_r(diagonal **b_diag, diagonal **tmp_diag, int j, diagonal *diag, element * elemento,
                int ndiagEFF, int DP, int pos, float *p_b_val);
int check_sol_prob(diagonal ** tmp_diag, element * elemento, int N, int DP);
float calculate_val(diagonal ** tmp_diag, element * elemento, int N);
void stampa_elemento(element * elemento);
void stampadiag(diagonal * diag, element  * elemento);

int main() {
    element * elemento;
    int n, ndiagMAX=MAXDIAG, ndiagEFF, DD, DP;
    char nomefile[100];
    FILE *fp;
    diagonal * diag;

    printf("Inserisci nome del file:\t");
    scanf("%s", nomefile);

    if((fp=fopen(nomefile,"r"))==NULL)
        return 1;

    n=leggifile(fp, &elemento);
    fclose(fp);

    printf("Inserisci valore DD:\t");
    scanf("%d", &DD);

    printf("Inserisci valore DP:\t");
    scanf("%d", &DP);

    ndiagEFF= generazione(&diag, elemento, n, DD, &ndiagMAX);

    printf("Le diagonali totali sono %d, ne ho allocate %d", ndiagEFF, ndiagMAX);

    find_sol(diag, elemento, ndiagEFF, DP);

    listaFree(elemento, n);
    free(diag);

    return 0;
}

int leggifile(FILE * fp, element ** p_elemento){
    int i, n;
    element * elementTMP;

    fscanf(fp,"%d",&n);

    elementTMP=malloc(n * sizeof(element));

    for(i=0; i<n; i++)
        elementRead(fp, &elementTMP[i]);

    *p_elemento=elementTMP;
    return n;
}
void elementRead(FILE *fp, element * elemento){
    char stringaTMP[100];

    fscanf(fp, "%s ", stringaTMP);
    elemento->nome=strdup(stringaTMP);

    fscanf(fp, "%d %d %d %d %d %f %d", &elemento->tipo, &elemento->ingresso, &elemento->uscita, &elemento->prec, &elemento->fin, &elemento->val, &elemento->difficolta);
}
void elementFree(element *elemento){
    free(elemento->nome);
}
void listaFree(element * elementi, int n){
    int i;
    for(i=0; i<n; i++)
        elementFree(&elementi[i]);

    free(elementi);
}
void stampadiag(diagonal * diag, element  * elemento){
    int i;
    for(i=0; i< diag->n; i++)
        stampa_elemento(&elemento[diag->indexElement[i]]);
    printf("\n");
}
void stampa_elemento(element * elemento){
    printf("%s %.3f\t",elemento->nome, elemento->val);
}
void reallocazione_totale(diagonal ** p_diag, int * p_ndiagMAX){
    *p_diag=realloc( *p_diag, (*p_ndiagMAX)*2 * sizeof(diagonal) );
    *p_ndiagMAX=(*p_ndiagMAX)*2;
}


int generazione(diagonal  ** p_diag, element * elemento, int n_el, int DD, int * p_ndiagMAX){
    int n_actual=0;

    diagonal * diag=    malloc((*p_ndiagMAX) * sizeof(diagonal));
    diagonal diagTMP;

    diagTMP.difficolta=0;
    diagTMP.val=0;
    disp_rip(elemento, &diag, &diagTMP, p_ndiagMAX, &n_actual, n_el, DD, 0);

    *p_diag=diag;
    return n_actual;
}

void disp_rip(element * elemento, diagonal ** p_diag, diagonal * p_diagTMP, int * p_ndiagMAX, int * p_n_actual, int n_el, int DD, int pos){
    int i;

    if(see_acrobatic(p_diagTMP, elemento, pos)) {
        if (*p_n_actual == (*p_ndiagMAX - 1))
            reallocazione_totale(p_diag, p_ndiagMAX);

        p_diagTMP->n=pos;

        (*p_diag)[(*p_n_actual)] = *p_diagTMP;

        (*p_n_actual)++;
    }

    if(pos==MAXE)
        return;

    for(i=0; i<n_el; i++)
        if(compatible_diagonal(p_diagTMP, pos, elemento, i, DD)) {
            p_diagTMP->indexElement[pos]=i;

            p_diagTMP->difficolta+=elemento[i].difficolta;
            p_diagTMP->val+=elemento[i].val;

            disp_rip(elemento, p_diag, p_diagTMP, p_ndiagMAX, p_n_actual, n_el, DD, pos + 1);

            p_diagTMP->difficolta-=elemento[i].difficolta;
            p_diagTMP->val-=elemento[i].val;
        }
}
int compatible_diagonal(diagonal * p_diagTMP, int pos, element * elemento, int i, int DD){
    if(pos==0) {
        if (elemento[i].prec == no_seguito && elemento[i].ingresso == fronte && elemento[i].difficolta <= DD)
            return 1;
        return 0;
    }

    if( elemento[ p_diagTMP->indexElement[pos-1] ].fin==FALSE &&
        elemento[ p_diagTMP->indexElement[pos-1] ].uscita == elemento[i].ingresso  &&
        (elemento[i].difficolta + p_diagTMP->difficolta) <=DD)
        return 1;

    return 0;
}
int see_acrobatic( diagonal * p_diagTMP, element * elemento, int j){
    int i;

    for(i=0; i<j; i++)
        if(elemento[p_diagTMP->indexElement[i]].tipo==indietro ||
           elemento[p_diagTMP->indexElement[i]].tipo== avanti)
            return 1;

    return 0;
}
void find_sol(diagonal * diag, element * elemento, int ndiagEFF, int DP){
    diagonal * b_diag[MAXDIAG];
    diagonal * tmp_diag[MAXDIAG];
    float b_val=0;
    int i;

    powerset_r(b_diag, tmp_diag, MAXDIAG, diag, elemento, ndiagEFF, DP, 0, &b_val);

    printf("\n\nSTAMPA PROGRAMMA CON VALORE:\t%.3f\n", b_val);
    for(i=0; i<MAXDIAG; i++)
        stampadiag(b_diag[i], elemento);
}
void powerset_r(diagonal **b_diag, diagonal **tmp_diag, int j, diagonal *diag, element * elemento,
                int ndiagEFF, int DP, int pos, float *p_b_val){
    int i;
    float val;

    if(pos==j){
        if(check_sol_prob(tmp_diag, elemento, j, DP)) {
            val = calculate_val(tmp_diag, elemento, j);
            if (*p_b_val < val) {
                *p_b_val = val;
                printf("\nBest %f", *p_b_val);
                //questa serve per scaricare il buffer di stdout, altrimenti sembra che ci stia un casino
                //a calcolare le diagonali, quando in realtà impiega tantissimo tempo per il calcolo del programma finale (3 diag)

                for (i = 0; i < j; i++)
                    b_diag[i] = tmp_diag[i];
            }
        }
        return ;
    }

    for(i=0; i<ndiagEFF; i++){
        tmp_diag[pos]=&diag[i];
        powerset_r(b_diag, tmp_diag, j, diag, elemento, ndiagEFF, DP, pos+1,  p_b_val);
    }
}
int check_sol_prob(diagonal ** tmp_diag, element * elemento, int N, int DP) {
    int check_2_seq_acrob=0, check_avanti=0, check_indietro=0, i, j, totalDifficult=0;

    for(i=0; i< N; i++)
        totalDifficult+=tmp_diag[i]->difficolta;

    if(totalDifficult>DP)
        return 0;

    for (i = 0; i < N; i++) {
        for (j = 0; j < tmp_diag[i]->n; j++) {
            if (elemento[tmp_diag[i]->indexElement[j]].tipo != transizione){

                if(check_avanti!=1 && elemento[tmp_diag[i]->indexElement[j]].tipo== avanti)
                    check_avanti=1;
                else if(check_indietro!=1)
                    check_indietro=1;

                if( check_2_seq_acrob!=1 &&
                    (j < (tmp_diag[i]->n - 1)) &&
                    elemento[tmp_diag[i]->indexElement[j+1]].tipo != transizione)
                    check_2_seq_acrob=1;

                if(check_avanti==1 && check_indietro==1 && check_2_seq_acrob==1)
                    return 1;
            }
        }
    }
    return 0;
}
float calculate_val(diagonal ** tmp_diag, element * elemento, int N){
    int i;
    float val=0;

    for(i=0; i<N-1; i++)
        val+=tmp_diag[i]->val;

    if(elemento[tmp_diag[i]->indexElement[ (tmp_diag[i]->n) -1 ]].difficolta>= DIFFICULT_EXTREME)
        val+= 1.5 * (tmp_diag[i]->val);
    else val+= tmp_diag[i]->val;

    return val;
}
