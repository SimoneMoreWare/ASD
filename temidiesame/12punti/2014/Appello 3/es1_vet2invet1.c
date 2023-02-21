#include <stdio.h>

int ricerca(int *vet1,int *vet2, int d1, int d2);

int main(){
    int vet1[]={27,7,0,15,12,21,7,25,32,1};
    int vet2[]={21,7,25};
    int d1=10;
    int d2=3;
    int res;
    res=ricerca(vet1,vet2,d1,d2);
    printf("%d ",res);
    return 0;
}

int ricerca(int *vet1,int *vet2,int d1,int d2){
    int res=-1;
    if(d1<d2) return res;
    int firstelementvet2=vet2[0];
    int flag;
    int count;
    int i,j;
    for(i=0;i<d1;i++){
        flag=1;
        count=0;
        if(vet1[i]==firstelementvet2){
            count++;
            for(j=i+1;j<d2+i && flag==1;j++){
                if(vet2[count++]!=vet1[j]) flag=0;
            }
            if(count==d2) res=i;
        }
    }
    return res;
}
