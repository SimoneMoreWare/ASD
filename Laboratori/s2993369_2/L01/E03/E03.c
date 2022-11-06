//si puo fare con formula zaffiri + smeraldi + 2*minimo(topazio,rubino) + minimo(abs(topazi-rubini),1) con vari corner case

#include <stdio.h>
#include <stdlib.h>

typedef enum {
    zaffiro,rubino,topazio,smeraldo
} Item;

int disp_rip(int pos,int *mark,int *sol,int n,int k,int prec, int found);
int check(int prec,int att);

int main(){
    int val[4]={2 ,1, 2, 2};
    int mark[4]={2 ,1, 2, 2};
    int k=val[0]+val[1]+val[2]+val[3];
    int *sol;
    int n=4;
    int pos=0;
    int i;
    int found=0;
    int prec=-1;
    sol=(int *) malloc(k*sizeof(int));
    for(i=k;i>=1 && found==0;i--) found=disp_rip(pos,mark,sol,n,i,prec,found);
    printf("TEST \nzaffiro = %d, rubino = %d, topazio = %d, smeraldo = %d, TOT = %d\n",
           val[zaffiro],
           val[rubino],
           val[topazio],
           val[smeraldo],
           k);
    printf("Collana massima di lunghezza %d\n",i+1);
    free(sol);
    return 0;
}

int disp_rip(int pos,int *mark,int *sol,int n,int k,int prec,int found){
    int i;
    if (pos >= k) {//terminazione
        for (i=0; i<k; i++) printf("%d ", sol[i]);
        printf("\n");
        return 1;
    }
    for (i = 0; i < n; i++) {//iterazioni sulle scelte
        if (mark[i] > 0 && check(prec,i)) {//mark non registra l uso o non l uso ma registra quante sono le sitanze disponibili da utilizzare, se c'è ne ancora una significa che la prendiamo
            mark[i]--;//scelta decrementate
            sol[pos] = i;//scelta e poi vado sulla successiva
            if(disp_rip(pos+1, mark, sol, n, k,i,found)) return 1;//backtrack implicit
            mark[i]++;//fase backtrack, annullo ultima scelta, rimetto in gioco quella scelta, incremento il vettore mark nella posizione i
        }
    }
    return 0;
}

int check(int prec,int att){
    if(prec==-1
    || ((prec==zaffiro) && (att==zaffiro || att==rubino))
    ||  ((prec==smeraldo) && (att==smeraldo || att==topazio))
    ||  ((prec==rubino) && (att==smeraldo || att==topazio))
    ||  ((prec==topazio) && (att==zaffiro || att==rubino))) return 1;
    return 0;
}
