#ifndef _SCI_INCLUDED
#define _SCI_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ST.h"
#include "skilift.h"

typedef struct user *skier;

skier SKIERnew(int id, int n_skys);
void  SKIERfree(skier s);
void  SKIERprint(FILE *fin, skier s);
int   SKIERid(skier s);
void  SKIERsetTime(skier s, int time, int indice_skilift);
int   SKIERgetTime(skier s, int indice_skilift);
void  SKIERlistSkilifts(skier s, ST skilift);
#endif
