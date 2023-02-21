#ifndef _DATO_INCLUDED
#define _DATO_INCLUDED

#define MAXC 21
#define START 10

typedef struct item* Item;
typedef int Key;
typedef char* Id;

Item ITEMnew();
void ITEMfree(Item val);
Item ITEMscan();
void ITEMstore(FILE *fp, Item val);
int  ITEMless(Item val1, Item val2);
int  ITEMgreater(Item val1, Item val2);
void ITEMchange(Item val1, Item val2, float ratio);
int  ITEMzero(Item val);

int  KEYcompare(Key k1, Key k2);
Key  KEYget(Item val);
Id   GETid(Item val);
Id   SCANid();
int  IDcompare(Id i1, Id i2);

#endif

