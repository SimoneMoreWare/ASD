#define DIMSET 8
#define U {1,2,3,4,5,6,7,8}
	
void cover(int S[][9],int n,int k){
     int *sol;
     int pos=0;
     int start=0;
     sol=(int *) malloc(k*sizeof(int));
     combinazionesemplici(S,n,k,start,pos,sol);
}

vodi combinazionisemplici(int S[][9],int n,int k,int start,int pos,int *sol){
    int i;
    if(pos>=k){
        //inserire check
        if(check(S,sol,k)) for(i=0;i<k;i++) printf("Insieme -> %d\n",sol[i]);
        printf("\n");
        return;
    }
    
    for(i=start;i<n;i++){
        sol[pos]=i;
        combinazionisemplici(S,n,k,i+1,pos+1,sol);
    }
}

int check(int S[][9],int *sol,int k){
    int *tmp;
    int i,j,k=0;
    tmp=(int *) malloc(n*sizeof(int));
   
    for(i=0;i<k;i++){
       for(j=0;j<n && mat[sol[i]][j]!=0;j++){
           tmp[k++]=mat[sol[i]][j];
       }
    }
    
     qsort(tmp, DIMSET, sizeof(int), cmpfunc);
     
     for(i=0;i<DIMSET;i++) if(tmp[i]!=U[i]) return 0;
     
     return 1;

}

int cmpfunc (const void * a, const void * b) {
   return ( *(int*)a - *(int*)b );
}
