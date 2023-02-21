#include <stdio.h>

#define NR 11
#define NC 11
int areaTot(FILE *fp);
int main(){
    FILE *fp;
    int res;
    fp=fopen("../input.txt","r");
    res=areaTot(fp);
    printf("%d",res);
    return 0;
}

int areaTot(FILE *fp){
    int mat[NR][NC];
    int i,j;
    int res=0;
    int basso_x,basso_y,alto_x,alto_y;
    int start_x,start_y,end_x,end_y;
    for(i=0;i<NR;i++) for(j=0;j<NC;j++) mat[i][j]=0;

    while(fscanf(fp,"%d %d %d %d",&basso_x,&basso_y,&alto_x,&alto_y)== 4){
        basso_y=NR-basso_y-1;
        basso_x=basso_x;
        alto_y=NR-alto_y;
        alto_x=alto_x-1;
        start_x=basso_x;
        start_y=alto_y;
        end_x=alto_x;
        end_y=basso_y;
        for(i=start_x;i<=end_x;i++){
            for(j=start_y;j<=end_y;j++){
                if(mat[i][j]==0){
                    res++;
                    mat[i][j]=1;
                }
            }
        }
    }
    return res;
}


