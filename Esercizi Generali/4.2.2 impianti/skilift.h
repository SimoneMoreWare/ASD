#ifndef _SKI_INCLUDED
#define _SKI_INCLUDED

#define MAX 11

typedef struct ski_lift* skilift;

skilift SKILIFTnew(char *str, int time, int index);
void    SKILIFTfree(skilift s);
char   *SKILIFTid(skilift s);
int     SKILIFTinterval(skilift s);
int     SKILIFTindex(skilift s);

#endif
