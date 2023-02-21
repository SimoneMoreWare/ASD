#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
  char *s;
  int dim_s;
}Riga;

int trova_sigle(int pos,Riga *val,char *sol,int dim_sol,int n_sol){
  int i;
  if(pos>=dim_sol){
      for(i=0;i<=pos;i++){
          printf("%c",sol[i]);
          }printf("\n");
      return n_sol+1;
      }
  for(i=0;i<val[pos].dim_s;i++){
      sol[pos]=val[pos].s[i];
      n_sol=trova_sigle(pos+1,val,sol,dim_sol,n_sol);
      }
  return n_sol;
}

int main()
{
  int n_sol,dim_sol,dim_str,i=0;
  FILE *fp=fopen("fp.txt","r");
  if(fp==NULL){
      return NULL;
  }
  fscanf(fp,"%d",&dim_sol);
  Riga *v_in=malloc(dim_sol*sizeof(Riga));
  char *sol=malloc(dim_sol*sizeof(char));
  char str_tmp[dim_sol];

  while(fscanf(fp,"%s",str_tmp)==1){
      v_in[i].s=strdup(str_tmp);
      v_in[i].dim_s=strlen(str_tmp);
      i++;
  }

  n_sol=trova_sigle(0,v_in,sol,dim_sol,0);
  printf("Soluzioni:%d\n",n_sol);

  fclose(fp);
  free(sol);
  free(v_in);
  return 0;
}
