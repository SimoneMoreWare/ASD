int distance (nnode_t *root, int key1, int key2){
    if(root->NULL) return -1; //albero vuoto
    if(BSTsearch(root,key1)==-1 || BSTSearch(root,key2) return -1; //key 1 o key2 non ci sono
    if(key1>key2){
        int tmp = key1;
        key1=key2;
        key 2 = tmp;
    }
    int res=0;
    distanceR(root,key1,key2,&res);
    return res;
}

void distanceR(nndode_t *root,int key1,int key2,int *res){
    if(root->NULL) return;
    if(root->key > key1 && root->key < key2){
        //function per contare le distanze
        *res = calcolo(root->left,key1);
        *res = *res + calcolo(root->right,key2);
    }
    
    if(key1 < root->key && key2 < root->key) distanceR(root->left,key1,key2,res);
    if(key1 >= root->key && key2 >= root->key) distanceR(root->right,key1,key2,res);
}

int calcolo(nnode_t *root,int val){
    int res;
    if(root->key == val) return res;
    if(val < root->key){
        res=res+1;
        calcolo(root->left,val);
    }else{
        res=res+1;
        calcolo(root->right,val);
    }
}
