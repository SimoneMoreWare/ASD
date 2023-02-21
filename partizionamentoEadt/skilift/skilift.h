#ifndef SKILIFT
#define SKILIFT

typedef struct ski_lift *skilift;

skilift SKILIFTnew(char *str, int time, int index);
void SKILIFTfree(skilift s);
char *SKILIFTid(skilift s);
int SKILIFTinterval(skilift s);
int SKILIFTindex(skilift s);
void SKILIFTprint(skilift s, FILE *fp);
skilift SKILIFTNULL();

#endif
