/*   queue.h
 *   @author  : Gabriele Iurlaro
 *   @  site  : http://iurlaro.com
 *   @Modified: 21/12/2020, 18:29:33
*/

#ifndef QUEUE_H
#define QUEUE_H

#include "grafo.h"

typedef struct queue *Q;

Q QUEUEinit(int maxN);
void QUEUEput(Q q, Edge e);
int QUEUEempty(Q q);
Edge QUEUEget(Q q);
#endif 
