#include <stdio.h>
#include <stdlib.h>

#include <stdlib.h>

typedef struct node* link;
struct node {
    int item;
    link left;
    link right;
};

link NEW(int key, link left, link right) {
    link x = malloc(sizeof *x);
    x->item = key;
    x->left = left;
    x->right = right;
    return x;
}

int search(int in[], int start, int end, int key) {
    int i;
    for (i = start; i <= end; i++) {
        if (in[i] == key)
            break;
    }
    return i;
}

link buildTree1(int in[], int pre[], int inStrt, int inEnd) {
    static int preIndex = 0;

    if (inStrt > inEnd)
        return NULL;

    link tNode = NEW(pre[preIndex++], NULL, NULL);

    if (inStrt == inEnd)
        return tNode;

    int inIndex = search(in, inStrt, inEnd, tNode->item);

    tNode->left = buildTree1(in, pre, inStrt, inIndex - 1);
    tNode->right = buildTree1(in, pre, inIndex + 1, inEnd);

    return tNode;
}

link buildTree(int in[], int pre[], int n) {
    return buildTree1(in, pre, 0, n - 1);
}


void visitTree(link root){
    if (root == NULL) return;

    visitTree(root->left);
    visitTree(root->right);
    printf("%d ", root->item);
}


int main() {
    int pre[8] = {18,10,1,15,12,17,20,23};
    int in[8] = {1,10,12,15,17,18,20,23};
    link  p = buildTree(in,pre,8);


    visitTree(p);

    return 0;
}
