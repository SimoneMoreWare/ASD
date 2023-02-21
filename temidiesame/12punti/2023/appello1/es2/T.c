#include "T.h"

typedef struct node *link;

struct node{
    int data;
    link *children;
    int N;
};

struct tree{
    link root;
};

static void fR(link root,int *maxpath,int valpath);
link initTreeNode(int value, int childrenCount);
int f(TREE t) {
    int maxpath=0;
    int valpath=0;
    fR(t->root,&maxpath,valpath);
    return maxpath-1;
}

void fR(link root,int *maxpath,int valpath){
    int i;
    if(root==NULL){
        return;
    }



    if(root->data>=0) valpath++;
    else valpath=0;
    for(i=0;i<root->N;i++) fR(root->children[i],maxpath,valpath);
    if(valpath>(*maxpath)) (*maxpath)=valpath;






}

TREE init(){
    TREE t = malloc(sizeof(TREE));
    t->root= initTreeNode(-1,3);
    t->root->children[0]= initTreeNode(-12,0);
    t->root->children[1]= initTreeNode(-3,1);
    t->root->children[1]->children[0] = initTreeNode(-4,0);
    t->root->children[2]= initTreeNode(-15,2);
    t->root->children[2]->children[0] = initTreeNode(6,0);
    t->root->children[2]->children[1] = initTreeNode(7,1);
    t->root->children[2]->children[1]->children[0] = initTreeNode(14,1);
    t->root->children[2]->children[1]->children[0]->children[0] = initTreeNode(14,0);
    return t;

}

link initTreeNode(int value, int childrenCount) {
    link node = (link) malloc(sizeof(struct node));
    node->data = value;
    node->N = childrenCount;
    node->children = (link*) malloc(childrenCount * sizeof(link));
    return node;
}
