#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void solve(char *str, char dict[8][5], int n, int k);
int solveR(char *str, char dict[8][5], int n, int k,int *sol,int pos,int term,int *mark);
int check(int *sol,int term,char dict[8][5],char *str);
int main(){
    char str[] = "abracadabra";
    int n=8;
    int k=6;
    /*char dict[8][5]= {
            {"a"},
            {"ab"},
            {"cada"},
            {"abra"},
            {"ra"},
            {"da"},
            {"ca"},
            {"bra"}
    };*/
    char dict[8][5]= {
            {"p"},
            {"pp"},
            {"ppp"},
            {"pp"},
            {"pp"},
            {"p"},
            {"p"},
            {"p"}
    };
    solve(str,dict,n,k);
    return 0;
}

void solve(char *str, char dict[8][5], int n, int k){
    int *sol=(int *) malloc(n*sizeof(int));
    int pos=0;
    int i;
    int *mark = (int *) calloc(n,sizeof(int));
    //disp ripetute per diversi valori di k
    int res;
    for(i=1;i<n && res==0;i++) res=solveR(str,dict,n,k,sol,pos,i,mark);
    free(sol);
    free(mark);
}

int solveR(char *str, char dict[8][5], int n, int k,int *sol,int pos,int term,int *mark){
    int i;
    if(pos>=term){
        if(check(sol,term,dict,str)){
            for(i=0;i<term;i++) printf("%s ",dict[sol[i]]);
            printf("\n");
            return 1;
        }
        return 0;
    }

    for(i=0;i<n;i++){
        if(mark[i]<k){ //si può aggiungere del pruning, lo lascio vuoto, una idea potrebbe essere di controllare ogni volte le prima celle pos-esime per verificare che non ci sono incongruenze
            mark[i]++;
            sol[pos]=i;
            if(solveR(str,dict,n,k,sol,pos+1,term,mark)) return 1;
            mark[i]--;
        }
    }
    return 0;
}

int check(int *sol,int term,char dict[8][5],char *str){

    int i,j;
    int k=0;
    int lunghezzastr=(int) strlen(str);
    for(i=0;i<term;i++){
        for(j=0;j<(int)strlen(dict[sol[i]]);j++){
            if(dict[sol[i]][j] != str[k]) return 0;
            k++;
            if(k>lunghezzastr) return 0;
        }
    }
    if(k==lunghezzastr) return 1;
    return 0;
}
