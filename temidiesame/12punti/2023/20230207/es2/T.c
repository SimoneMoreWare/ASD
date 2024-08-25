
#include "T.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct node *link;

struct node{
    int data;
    link children[3];
};

struct tree{
    link root;
};

link NEW(int n);
static void fR(link root,int *maxpath,int valpath);

int f(T t) {
    int maxpath=0;
    int valpath=0;
    fR(t->root,&maxpath,valpath);
    return maxpath;
}

void fR(link root,int *maxpath,int valpath){
    int i;

    if(root==NULL){
        return;
    }

    if(root->data>=0)
        valpath++;
    else{
        return;
    }

    if(valpath>(*maxpath))
        (*maxpath)=valpath;

    for(i=0;i<3;i++){
        fR(root->children[i],maxpath,valpath);
    }


}


link NEW(int n){
    int i;
    link x=malloc(sizeof(*x));
    x->data=n;
    for(i=0;i<3;i++){
        x->children[i]=NULL;
    }
    return x;

}

T init(){
    T t = malloc(sizeof(*t));
    t->root=NULL;
    return t;

}

void initTreeNode(T t) {

    t->root=NEW(1);

    t->root->children[0]=NEW(2);
    t->root->children[1]=NEW(3);
    t->root->children[2]=NEW(4);

    t->root->children[0]->children[0]=NEW(5);
    t->root->children[0]->children[1]=NEW(6);

    t->root->children[1]->children[0]=NEW(7);
    t->root->children[1]->children[0]->children[0]=NEW(-12);
    t->root->children[1]->children[0]->children[0]->children[0]=NEW(13);

    t->root->children[2]->children[0]=NEW(8);
    t->root->children[2]->children[1]=NEW(-9);
    t->root->children[2]->children[2]=NEW(10);

    t->root->children[2]->children[1]->children[0]=NEW(11);
    t->root->children[2]->children[1]->children[0]->children[0]=NEW(14);

}
