#ifndef QUEUE_H
#define QUEUE_H

typedef struct queue *Q;

Q       Qinit();
void    Qfree(Q q);
int     Qempty(Q q);
void    Qput (Q q, int e);
int    Qget(Q q);


#endif
