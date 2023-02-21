#include <stdio.h>
#include <stdlib.h>

 typedef struct
 {
     int a;
     int b;
 }interv;

 //-----------------------------

 void intervSel(int n, interv* v);
 void disp(interv*, interv*, int, interv*, int*, int, int*, int*);
 void controllo(int n, interv* val, interv* sol, interv* solm, int* ns, int* max);

 //-----------------------------

int main()
{
    int n,i;
    FILE* fl=fopen("interv.txt","r");
    if(fl==NULL)
        return -1;

    fscanf(fl,"%d",&n);
    interv* v=malloc(n*sizeof(interv));
    for(i=0; i<n; i++)
    {
        fscanf(fl,"%d%d", &v[i].a, &v[i].b);
    }

    intervSel(n, v);


    return 0;
}

void intervSel(int n, interv* val)
{
    int ns=0,i,max=0;

    int *mark=malloc(n*sizeof(int));
    for(i=0; i<n; i++) mark[i]=1;

    interv *sol=malloc(n*sizeof(interv));
    interv *solm=malloc(n*sizeof(interv));

    disp(sol, val, n, solm, &ns, 0, mark, &max);

    stampasol(solm,ns);
}

disp(interv* sol, interv* val, int n, interv* solm, int* ns, int pos, int* mark, int* max)
{
    int i,j;

    if(pos>=n)
    {
        controllo(n, val, sol, solm, ns, max);
    }

    for(i=0; i<n; i++)
    {
        if(mark[i]!=0)
        {
            sol[pos]=val[i];
            mark[i]--;
            disp(sol, val, n, solm, ns, pos+1, mark, max);
            mark[i]++;
        }
    }

    return;
}

void controllo(int n, interv* val, interv* sol, interv* solm, int* ns, int* max)
{
    int i,j,d=0;

    for(i=0; i<n; i++)
    {
        d = d + sol[i].b - sol[i].a;

        if(i+1 < n && sol[i].b > sol[i+1].a)
        {
            assgsolmax(solm, ns, sol, i+1, max, d);
            return;
        }


    }

}

void assgsolmax(interv* solm, int* ns, interv* sol, int n2, int* max, int d)
{
    int i;

    if(d > *max)
        {
            for(i=0; i<n2; i++)
                {
                    solm[i]=sol[i];
                    *ns=n2;
                }
                *max=d;
        }
    return;
}

void stampasol(interv *solm, int ns)
{
    int i;

  for(i=0; i<ns; i++)
        printf("( %d , %d )", solm[i].a, solm[i].b);

    printf("\n");

  return;
}
