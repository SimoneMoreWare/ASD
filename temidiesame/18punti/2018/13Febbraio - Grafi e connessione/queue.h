/*   queue.h
 *   @author  : Gabriele Iurlaro
 *   @  site  : http://iurlaro.com
 *   @Modified: 22/12/2020, 19:45:38
*/
#ifndef APATEMI_QUEUE_H
#define APATEMI_QUEUE_H

#include "Grafo.h"

typedef struct queue *Q;

Q QUEUEinit();
void QUEUEput(Q q, Edge e);
int QUEUEempty(Q q);
Edge QUEUEget(Q q);
#endif //APATEMI_QUEUE_H
