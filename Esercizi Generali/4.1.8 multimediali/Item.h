#ifndef ITEM_H
#define ITEM_H

#define MAXC 26

typedef char* Key;

typedef struct listNode *listLink;

typedef struct {
    char  id[MAXC];
    char  name[MAXC];
    char  surname[MAXC];
    int   numAccess;
    int   totKB;
    int   totTime;
    char  cat[MAXC];
    listLink  customerList;
} Item;

struct listNode { char surname[MAXC];  listLink next; };

Item ITEMscan(FILE *fp);
Item ITEMsetNull();
Item ITEMsetCat(Key k);
int  ITEMcheckNullCust(Item val);
int  ITEMcheckNullCat(Item val);
void ITEMstoreCust(FILE *fout, Item val);
void ITEMstoreCat(FILE *fout, Item val);
void ITEMinsertInList(Item *pval1, Item val2);
void ITEMfree(Item val1);
void CustomerListfree(listLink customerList);
Key  KEYgetId(Item *pval);
Key  KEYgetSurname(Item *pval);
Key  KEYgetCat(Item *pval);
int  KEYcompare(Key k1, Key k2);

#endif


