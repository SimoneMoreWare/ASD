#ifndef ITEM_H_INCLUDED
#define ITEM_H_INCLUDED

typedef struct item { int low; int high; } Item;

Item 	ITEMscan();
Item    ITEMsetNull();
int     ITEMcheckNull(Item val);
void    ITEMstore(Item val);
int		ITEMhigh();
int 	ITEMlow();
int 	ITEMoverlap(Item val1, Item val2);
int 	ITEMeq(Item val1, Item val2);
int 	ITEMlt(Item val1, Item val2);
int 	ITEMlt_int(Item val1, int val2);
#endif

