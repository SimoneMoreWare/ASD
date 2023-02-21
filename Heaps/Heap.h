#ifndef HEAP_H_DEFINED
#define HEAP_H_DEFINED

typedef struct heap *Heap;

Heap    HEAPinit(int maxN);
void    HEAPfree(Heap h);
void    HEAPfill(Heap h, Item val);
void    HEAPsort(Heap h);
void	HEAPdisplay(Heap h) ;

#endif
