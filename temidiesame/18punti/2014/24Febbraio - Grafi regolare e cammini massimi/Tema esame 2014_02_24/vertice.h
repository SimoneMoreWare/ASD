#ifndef VERTICE_H_INCLUDED
#define VERTICE_H_INCLUDED
#define MAX 21
#include <string.h>

typedef struct{
   char vertice[MAX];
   int inDegree, outDegree;
}Vertice;

Vertice VERTICEcrea(char *vertice);
void VERTICEincrementaOutDegree(Vertice *v);
void VERTICEincrementaInDegree(Vertice *v);

#endif // VERTICE_H_INCLUDED
