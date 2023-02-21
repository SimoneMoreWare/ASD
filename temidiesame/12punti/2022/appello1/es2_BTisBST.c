/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 
 //--------------------------
 /* File BT.h* */
 //typedef struct bt *BT

/* File BT.c */
//typedef struct node *link
/*
struct node{
  int value;
  link l, r;
}

struct bt{
  link root, z;
}
 provato su leetcode e funziona */
 */

void visitinorder(struct TreeNode* root,int *ordertree,int *k){
    if(root==NULL) return;
    visitinorder(root->left,ordertree,k);
    ordertree[(*k)++]=root->val;
    visitinorder(root->right,ordertree,k);
}

int count(struct TreeNode* root) {
    if (root == NULL)
    return 0;
    return count(root->left) + count(root->right) + 1;
}

bool isValidBST(struct TreeNode* root){
    int numbernode;
    numbernode = count(root);
    int k=0;
    int i;
    int *ordertree = (int *) malloc(numbernode*sizeof(int));
    
    visitinorder(root,ordertree,&k);
    for(i=0;i<k-1;i++) if(ordertree[i]>=ordertree[i+1]) return 0;
    free(ordertree);
    return 1;
}
