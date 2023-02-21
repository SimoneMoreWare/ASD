#include <stdio.h>
#include <stdlib.h>
#define N 10

/*FUNZIONE_1*/
void leggiMatr(int matr[][N],int *nr,int *nc);

/*FUNZIONE_2*/
void SommaDiagonali(int matr[][N],int nr,int nc,int x,int y,int *somma_diagonali);

int main()
{
    int i,j,matr[N][N],nr,nc,somma_diagonali=0;
    int x_top,y_top;
    int somma_MAX=-1;
    leggiMatr(matr,&nr,&nc);
    for(i=0;i<nr;i++){
        for(j=0;j<nc;j++){
            if(matr[i][j]==0){
            SommaDiagonali(matr,nr,nc,i,j,&somma_diagonali);
            if(somma_MAX==-1 || somma_MAX<somma_diagonali){
                somma_MAX=somma_diagonali;
                x_top=i;
                y_top=j;
                }
            }
        }
    }
    printf("Casella migliore:\n");
    printf("x->%d , y->%d\n",x_top,y_top);
    printf("Somma_MAX->%d\n",somma_MAX);
    return 0;
}

/*FUNZIONE_1*/
void leggiMatr(int matr[][N],int *nr,int *nc){
  int i,j;
  FILE *fp=fopen("s.txt","r");
  if(fp==NULL){
      fclose(fp);
      exit(-1);
  }
  fscanf(fp,"%d",nr);
  *nc=*nr;
  for(i=0;i<*nr;i++){
      for(j=0;j<*nr;j++){
          fscanf(fp,"%d ",&matr[i][j]);
      }
  }
  fclose(fp);
  return;
}

/*FUNZIONE_2*/
void SommaDiagonali(int matr[][N],
 int nr,int nc,int x,int y,
 int *somma_diagonali){

  int x_tmp=x;
  int y_tmp=y;

  int somma_1=0;
  int somma_2=0;
  int somma_3=0;
  int somma_4=0;

  int somma_diag_1=0;
  int somma_diag_2=0;

  while(x>=0 && y>=0){
      somma_1=somma_1+matr[x][y];
      x--;
      y--;
  }

  x=x_tmp;
  y=y_tmp;

  while(x<nr && y<nc){
      somma_2=somma_2+matr[x][y];
      x++;
      y++;
  }

  x=x_tmp;
  y=y_tmp;

  somma_diag_1=(somma_1+somma_2)-matr[x][y];

  while(x>=0 && y<nc){
      somma_3=somma_3+matr[x][y];
      x--;
      y++;
      }

  x=x_tmp;
  y=y_tmp;

  while(x<nr && y>=0){
      somma_4=somma_4+matr[x][y];
      x++;
      y--;
  }

  x=x_tmp;
  y=y_tmp;

  somma_diag_2=(somma_3+somma_4)-matr[x][y];

  *somma_diagonali=somma_diag_1+somma_diag_2;

  return;
}
