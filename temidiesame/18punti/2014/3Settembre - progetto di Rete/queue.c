/*   queue.c
 *   @author  : Gabriele Iurlaro
 *   @  site  : http://iurlaro.com
 *   @Modified: 21/12/2020, 18:29:18
*/
#include "queue.h"
#include <stdlib.h>

struct queue {   Edge *q;   int N, head, tail; };
Q QUEUEinit(int maxN){
    Q q = malloc(sizeof(*q));
    q->q = malloc(maxN*sizeof(Edge));
    q->N=maxN+1;
    q->head = q->N;
    q->tail = 0;
    return q;
}
void QUEUEput(Q q, Edge e){
    q->q[q->tail++] = e;
    q->tail = q->tail%(q->N);
}
int QUEUEempty(Q q){
    return (q->head)%(q->N) == q->tail;
}
Edge QUEUEget(Q q){
    q->head = q->head%(q->N);
    return q->q[q->head++];
}