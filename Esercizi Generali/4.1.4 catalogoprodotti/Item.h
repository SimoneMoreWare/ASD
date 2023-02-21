#ifndef ITEM_H
#define ITEM_H

#define MAXC 21

typedef struct item* Item;
typedef char *Id;
typedef float Key;

Item ITEMnew();
void ITEMfree(Item val);
Item ITEMscan(FILE *fin);
Item ITEMfill(char *str, float price);
void ITEMstore(FILE *fout, Item val);
Item ITEMsetNull();
int  ITEMcheckNull(Item val);
int  ITEMcompare(Item val1, Item val2);
int  KEYcompare(Key k1, Key k2);
Key  KEYget(Item val);
int  IDcompare(Item val1, Item val2);

#endif

