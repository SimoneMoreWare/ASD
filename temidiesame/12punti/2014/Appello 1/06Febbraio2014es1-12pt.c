#include <stdio.h>
#include <stdlib.h>

int * merge3(int *a, int *b, int *c, int na, int nb, int nc);

int main()
{
    int na,nb,nc,*vett,i,*a,*b,*c,tot;

    printf("inserisci numero di elementi di a: ");
    scanf("%d", &na);
    a = malloc(na*sizeof(int));
    printf("inserisci numero di elementi di b: ");
    scanf("%d", &nb);
    b = malloc(nb*sizeof(int));
    printf("inserisci numero di elementi di c: ");
    scanf("%d", &nc);
    c = malloc(nc*sizeof(int));

    printf("\ninserisci elementi di a: \n");
    for(i=0; i<na;i++){
        printf("na[%d]: ", i);
        scanf("%d", &a[i]);
    }
    printf("\n");

    printf("\ninserisci elementi di b: \n");
    for(i=0; i<nb;i++){
        printf("nb[%d] : ", i);
        scanf("%d", &b[i]);
    }
    printf("\n");

    printf("inserisci elementi di c: \n");
    for(i=0; i<nc;i++){
        printf("nc[%d] : ", i);
        scanf("%d", &c[i]);
    }
    printf("\n");

    vett = merge3(a,b,c,na,nb,nc);

    tot=na+nb+nc;

    for(i=0;i<tot;i++)
        printf("%d ", vett[i]);

    return 0;
}

int * merge3(int *a, int *b, int *c, int na, int nb, int nc){
    int *vett, tot = na+nb+nc, i,j,k,l;

    vett = malloc(tot*sizeof(int));
    i=0; j=0; k=0;

    for(l=0; l<tot; l++){
        if(i>na && j>nb)
            vett[l]=c[k++];
        else if(i>na && k>nc)
            vett[l]=b[j++];
        else if(k>nc && j>nb)
            vett[l]=a[i++];
        else if(a[i]<=b[j]&&a[i]<=c[k])
            vett[l]=a[i++];
        else if(b[j]<=c[k]&&b[j]<=a[i])
            vett[l]=b[j++];
        else
            vett[l]=c[k++];
    }
    return vett;
}

