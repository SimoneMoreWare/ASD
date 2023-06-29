#ifndef TRIANGLEPACKING_H_INCLUDED
#define TRIANGLEPACKING_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>

//V
typedef struct{
   int vertici[3];
}V;

typedef enum{VERO, FALSO}Boolean;

V Vread(FILE *f);
V Vcreate(int *vertici);
Boolean VisDisgiunti(V v1, V v2);
Boolean VcontieneVerticiDiversi(V v);
Boolean VareThereRealVertex(V v, int numVertici);
Boolean VareThereRealEdges(V v, int **archi);
void Vprint(V v, FILE *f);


//TP
typedef struct trianglePacking *TP;

TP TPinit(int max);
void TPinsert(TP tp, V insieme);
void TPelimina(TP tp);
TP TPread(FILE *f);
Boolean TPisTrianglePacking(TP tp, int **archi, int nVertici);
Boolean TPisDisgiunto(TP tp);
void TPprint(TP tp, FILE *f);
void TPcopia (TP tp1, TP tp2);
void TPfree(TP tp);

#endif // TRIANGLEPACKING_H_INCLUDED
