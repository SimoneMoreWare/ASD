//
// Created by simone on 11/11/22.
//

#ifndef UNTITLED3_INVENTARIO_H
#define UNTITLED3_INVENTARIO_H
/*
typedef struct node *linkO;
typedef struct{
    char nome[MAXN];
    char tipologia[MAXN];
    int stat[6];
}ItemO;*/

typedef struct nodeO *linkO;
struct nodeO{
    int val;
    linkO next;
};

void listInsHeadO(linkO *head,int newval);
void listDisplayO(linkO p);


#endif //UNTITLED3_INVENTARIO_H
