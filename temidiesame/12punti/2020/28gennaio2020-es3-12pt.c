include <stdio.h>
#include <stdlib.h>
#define MAX 15 //somma di tutte le possibili disposizioni


//il programma è funzionante e permette di trovare la soluzione ottimale ma non è scritto nel modo più pulito

void stampaSoluzione(int n, int *optSol);
int *resto_macchina (int r,int n, int *val, int *disp);
void resto_macchina_R (int r,int n, int *val, int *disp,int *sol,  int *optimalsol, int pos, int tot);
void bestSol (int *sol, int *save, int n);

int main()
{
    int n = 3, *val,*disp, r = 30;

    val = malloc(n*sizeof(int));
    disp = malloc(n*sizeof(int));

    val[0] = 1;
    val[1] = 10;
    val[2] = 25;

    disp[0] = 10;
    disp[1] = 3;
    disp[2] = 2;

    int *sol=resto_macchina(r,n,val,disp);
    stampaSoluzione(n,sol);
    return 0;
}
void stampaSoluzione(int n, int *optSol){
    int i=0;

    printf("Soluzione: ");
    while(optSol[i]!=0){
        printf("%d ", optSol[i]);
        i++;
    }
    printf("\n");

    return;

}
void bestSol (int *sol, int *save, int n){
    int tmp=0;
    if(save[0]!=0)
        while(save[tmp]!=0)
            tmp++;
    else
        tmp=n;
    int i;
    if(tmp>=n)
        for(i=0;i<MAX;i++)
            if(i<n)
                save[i]=sol[i];
            else
                save[i]=0;
}

int *resto_macchina (int r,int n, int *val, int *disp){
	int *sol=(int *)malloc(MAX*sizeof(int));
	int *optimalsol=(int *)malloc(MAX*sizeof(int));
	resto_macchina_R(r,n,val,disp,sol,optimalsol,0,0);
    return optimalsol;
}

void resto_macchina_R (int r,int n, int *val, int *disp, int *sol, int *optimalsol, int pos, int tot){
	if(tot==r){
        bestSol(sol, optimalsol, pos);
		return ;
    }
	if(tot>r)
		return NULL;

	int i;
	for(i=n-1;i>=0;i--){
		if(disp[i]!=0){
			sol[pos]=val[i];
			disp[i]--;
			tot+=sol[pos];
			resto_macchina_R(r,n,val,disp,sol, optimalsol,pos+1,tot);
			disp[i]++;
			tot-=sol[pos];
			sol[pos]=0;
		}
	}
	return sol;
}
