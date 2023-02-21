#ifndef ITEM_H_INCLUDED
#define ITEM_H_INCLUDED

#define MAXC 21

#define START 10


typedef struct item {

  char name[MAXC];

  int value;

} Item;



typedef int Key;

typedef char Id[MAXC];



Item ITEMnew();

Item ITEMscan();

void ITEMstore(FILE *fp, Item val);

int  ITEMless(Item val1, Item val2);

int  ITEMgreater(Item val1, Item val2);

void ITEMchange(Item *val1, Item *val2, float ratio);
int  ITEMzero(Item val);



int  KEYcompare(Key k1, Key k2);

Key  KEYget(Item val);

void GETid(Item val, Id id);

void SCANid(Id id);

int  IDcompare(Id i1, Id i2);

#endif /* ITEM_H_INCLUDED */
