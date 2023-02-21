#include <stdio.h>
#include <stdlib.h>

#define N 3

typedef struct treeNode treeNode;
typedef treeNode* nTREE;


struct treeNode {
    int value;
    nTREE children[N];
};

nTREE createTreeNode(int value);
void countIf(nTREE t, int* count1, int* count2, int* count3);
void visit(struct treeNode *root,int **count1,int **count2,int **count3);

nTREE createTreeNode(int value) {
    nTREE node = (nTREE) malloc(sizeof(treeNode));
    node->value = value;
    return node;
}

int main() {
    nTREE root = createTreeNode(1);
    root->children[0] = createTreeNode(2);
    root->children[1] = createTreeNode(3);
    root->children[2] = createTreeNode(4);

    root->children[0]->children[0] = createTreeNode(5);
    root->children[0]->children[0]->children[0] = NULL;
    root->children[0]->children[0]->children[1] = NULL;
    root->children[0]->children[0]->children[2] = NULL;
    root->children[0]->children[1] = createTreeNode(6);
    root->children[0]->children[1]->children[0] = NULL;
    root->children[0]->children[1]->children[1] = NULL;
    root->children[0]->children[1]->children[2] = NULL;
    root->children[0]->children[2] = NULL;

    root->children[1]->children[0] = createTreeNode(7);
    root->children[1]->children[0]->children[0] = NULL;
    root->children[1]->children[0]->children[1] = NULL;
    root->children[1]->children[0]->children[2] = NULL;
    root->children[1]->children[1] = NULL;
    root->children[1]->children[2] = NULL;

    root->children[2]->children[0] = createTreeNode(8);
    root->children[2]->children[0]->children[0] = NULL;
    root->children[2]->children[0]->children[1] = NULL;
    root->children[2]->children[0]->children[2] = NULL;
    root->children[2]->children[1] = createTreeNode(9);
    root->children[2]->children[1]->children[0] = NULL;
    root->children[2]->children[1]->children[1] = NULL;
    root->children[2]->children[1]->children[2] = NULL;
    root->children[2]->children[2] = createTreeNode(10);
    root->children[2]->children[2]->children[0] = NULL;
    root->children[2]->children[2]->children[1] = NULL;
    root->children[2]->children[2]->children[2] = NULL;


    int count1 = 0, count2 = 0, count3 = 0;
    countIf(root, &count1, &count2, &count3);

    printf("Number of nodes with 1 child: %d\n", count1);
    printf("Number of nodes with 2 children: %d\n", count2);
    printf("Number of nodes with 3 children: %d\n", count3);

    return 0;
}

void countIf(nTREE t, int* count1, int* count2, int* count3){
    visit(t,&(count1),&(count2),&(count3));
}

void visit(struct treeNode *root,int **count1,int **count2,int **count3){

    int i;
    int cnt=0;
    if(root==NULL) return;

    for(i=0;i<N;i++) if(root->children[i]!=NULL) cnt++;

    if(cnt==1) (**count1)++;
    else if(cnt==2) ((**count2))++;
    else if(cnt==3) ((**count3))++;

    for(i=0;i<N;i++) visit(root->children[i],count1,count2,count3);

}
