/*

vedi slide height
*/


int calculate_max_path(struct TreeNode* node, int* max_path)
{
    if (!node) return 0;
    int left  = calculate_max_path(node->left,  max_path);
    int right = calculate_max_path(node->right, max_path);
    if (right+left > *max_path)
        *max_path = right+left;
    if (right>left)
        return (right+1);
        
        return (left+1);
}

int diameterOfBinaryTree(struct TreeNode* root){
    int max_path = 0;
    calculate_max_path(root, &max_path);//calcolo l l'altezza
    return max_path;
}
