#include <stdio.h>
#include <stdlib.h>

/*typedef enum {
    zaffiro,rubino,topazio,smeraldo
} Item;*/

int disp_rip(int pos,int *val,int *sol,int n,int k,int *mark,int cnt);

int main(){
    int val[4]={2,1,2,2};
    int mark[4]={2,1,2,2};
    int k=val[0]+val[1]+val[2]+val[3];
    int *sol;
    int n=4;
    int pos=0;
    int cnt=0;
    sol=(int *) malloc(k*sizeof(int));
    cnt= disp_rip(pos,val,sol,n,k,mark,cnt);
    printf("%d",cnt);
    free(sol);
    return 0;
}

int disp_rip(int pos,int *val,int *sol,int n,int k,int *mark,int cnt){
    int i;
    if (pos >= k) {//terminazione
        for (i=0; i<k; i++) printf("%d ", sol[i]);
        printf("\n");
        return cnt+1;
    }
    for (i = 0; i < n; i++) {//iterazioni sulle scelte
        if (mark[i] > 0) {//mark non registra l uso o non l uso ma registra quante sono le sitanze disponibili da utilizzare, se c'è ne ancora una significa che la prendiamo
            mark[i]--;//scelta decrementate
            sol[pos] = i;//scelta e poi vado sulla successiva
            cnt = disp_rip(pos+1, val, sol, n, k,mark,cnt);//backtrack implicit
            mark[i]++;//fase backtrack, annullo ultima scelta, rimetto in gioco quella scelta, incremento il vettore mark nella posizione i
        }
    }
    return cnt;
}

