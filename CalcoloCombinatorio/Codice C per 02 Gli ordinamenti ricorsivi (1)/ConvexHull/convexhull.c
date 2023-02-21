#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

typedef struct point *Point;
struct point {int x, y, flag;};

Point NEWpoint(int, int);
void ReadInputFile(char* );
void LookForP0(void);
void MergeSort(int, int);
void Merge(int, int, int);
int ComparePoints(Point,Point);
int MoreDistant(Point, Point);
int CrossProduct(Point, Point, Point);
void GrahanScan(void);
void WriteOutputFile(char *);

Point *P;
int N;

int main (int argc, char *argv[])
{
    if(argc<3){
        printf("Error in command line\n");
        exit(1);
    }
    ReadInputFile(argv[1]);
    GrahanScan();
    WriteOutputFile(argv[2]);
    return 0;
}

Point NEWpoint(int x, int y)
{
    Point p;
    p = malloc(sizeof(*p));
    p->x = x;
    p->y = y;
    p->flag = 1;
    return p;
}

void ReadInputFile(char* filein)
{
    FILE *fp;
    int i, x, y;
    fp = fopen(filein, "r");
    if(fp == NULL)
    {
        printf("Error opening input file\n");
        exit(0);
    }
    fscanf(fp, "%d", &N);
    P = malloc(N*sizeof(Point));
    for(i=0; i<N; i++)
    {
        fscanf(fp,"%d%d", &x, &y);
        P[i] = NEWpoint(x,y);
    }
    fclose(fp);
}

void LookForP0(void)
{
    int i, min = 0;
    Point tmp;
    for(i = 1; i < N; i++)
    {
        if(P[i]->y < P[min]->y)
            min = i;
        else if(P[i]->y == P[min]->y)
            if(P[i]->x < P[min]->x)
                min = i;
    }
    tmp = P[0];
    P[0] = P[min];
    P[min] = tmp;
    return;
}

void MergeSort(int l, int r)
{
    int q;
    if (l < r) {
        q = (l + r)/2;
        MergeSort(l, q);
        MergeSort(q+1, r);
        Merge(l, q, r);
   }
   return;
}

void Merge( int l, int q, int r)
{
    int i, j, k;
    Point Q[N];

    i = l;
    j = q+1;
    for(k = l; k <= r; k++)
        if (i > q)
            Q[k] = P[j++];
        else if (j > r)
            Q[k] = P[i++];
        else if (ComparePoints(P[i],P[j]) < 0)
            Q[k] = P[i++];
        else
            Q[k] = P[j++];

    for (k = l; k <= r; k++ )
        P[k] = Q[k];
    return;
}

int ComparePoints(Point p1, Point p2)
{
    int x = CrossProduct(P[0], p1, p2);
    if(x == 0)
    {
        if(MoreDistant(p1, p2))
        {
            p2->flag = 0;
            return 1;
        }
        else
        {
            p1->flag = 0;
            return -1;
        }
    }
    return -x;
}

int MoreDistant(Point p1,Point p2)
{
    int x1, x2, y1, y2, d1, d2;
    x1 = p1->x - P[0]->x;
    x2 = p2->x - P[0]->x;
    y1 = p1->y - P[0]->y;
    y2 = p2->y - P[0]->y;
    d1 = (x1 * x1) + (y1 * y1);
    d2 = (x2 * x2) + (y2 * y2);
    return d1 > d2;
}

int CrossProduct(Point p0, Point p1, Point p2)
{
    int x1, x2, y1, y2, prod;
    x1 = p1->x - p0->x;
    x2 = p2->x - p0->x;
    y1 = p1->y - p0->y;
    y2 = p2->y - p0->y;
    prod = (x1 * y2) - (x2 * y1);
    if(prod > 0)
        return 1;
    else if(prod < 0)
        return -1;
    return 0;
}

void GrahanScan(void)
{
    int i, j;
    LookForP0();
    MergeSort(1, N-1);
    STACKinit(N);
    STACKpush(P[0]);
    for(i = 1, j = 1; i < 3;)
        if(P[j]->flag)
        {
            i++;
            STACKpush(P[j++]);
        }
        else
            j++;
    for(i = j; i < N; i++)
    {
        if(P[i]->flag)
        {
            while(CrossProduct(STACKnext_to_top(),STACKtop(),P[i]) != 1)
                STACKpop();
        STACKpush(P[i]);
        }
    }
    return;
}

void WriteOutputFile(char *fileout)
{
    FILE *fp;
    Point q;
    int i, M = STACKsize();

    fp = fopen(fileout, "w");
    if(fp == NULL)
    {
        printf("Error opening output file\n");
        exit(1);
    }
    fprintf(fp, "%d\n", M);
    for(i = 0; i < M && !STACKempty(); i++)
    {
        q =(Point)STACKpop();
        fprintf(fp,"%d %d\n",q->x, q->y);
    }
    fclose(fp);
    return;
}
