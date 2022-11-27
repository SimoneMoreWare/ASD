//
// Created by simone on 25/11/22.
//

#ifndef UNTITLED7_LISTADJ_H
#define UNTITLED7_LISTADJ_H
#include "ST.h"
//#include "Graph.h"
#include <stdlib.h>
#include <stdio.h>
#define MAXCL 50
typedef struct edgelist { int v; int w; int wt; } Edgelist;
typedef struct lisadj *Listaadj;

Listaadj LISTinit(int V);
void  LISTfree(Listaadj L);
void  LISTinsertL(Listaadj L, int id1, int id2, int wt);
void  LISTstore(Listaadj G, FILE *fout);
void  LISTedges(Listaadj G, Edgelist *a);
void STinsertWrapper(Listaadj L,char *name, char *subnet);
void check_sottografocompleto_list(Listaadj L);
#endif //UNTITLED7_LISTADJ_H
