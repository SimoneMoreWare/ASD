#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define N_R 4
#define N_C 5

void apri_file(char mat[N_R][N_C]);
int leggi_stringa(char mat[N_R][N_C],char s[],int r,int c,int n);

int main(){
char mat[N_R][N_C],str[]="foo";
int i,j,n=0;
int conta_str=0;
apri_file(mat);
n=strlen(str);
for(i=0;i<N_R;i++){
    for(j=0;j<N_C;j++){
        conta_str+=leggi_stringa(mat,str,i,j,n);
    }
}
printf("conta_finale->%d\n",conta_str);
return 0;
}

void apri_file(char mat[N_R][N_C]){
int i=0;
FILE *fp=fopen("c.txt","r");
if(fp==NULL){
    fclose(fp);
    exit(-1);
}
while(fscanf(fp,"%s",&mat[i])!=EOF){
    printf("%s\n",mat[i]);
    i++;
}printf("\n");
fclose(fp);
return;
}


int leggi_stringa(char mat[N_R][N_C],char s[],int r,int c,int n){
int conta_str=0;
int i=r;
int j=c;
int pos=0;

printf("CASELLA DI COORDINATE\n");
printf("i->%d , j->%d\n",r,c);

/*Riga alto->basso*/
printf("---Riga alto->basso---\n");
while(mat[i][c]==s[pos] && pos<n && i<N_R){
    printf("mat[%d][%d]->%c = s[%d]->%c\n",i,c,mat[i][c],pos,s[pos]);
    pos++;
    printf("pos->%d\n",pos);
    i++;
    printf("i->%d\n",i);
    }
i=r;
if(pos==n){
    conta_str++;
    printf("conta_str FINORA->%d\n",conta_str);
    }
pos=0;
/*Riga basso->alto*/
printf("---Riga basso->alto---\n");
while(mat[i][c]==s[pos] && pos<n && i>=0){
    printf("mat[%d][%d]->%c = s[%d]->%c\n",i,c,mat[i][c],pos,s[pos]);
    pos++;
    printf("pos->%d\n",pos);
    i--;
    printf("i->%d\n",i);
    }
i=r;
if(pos==n){
    conta_str++;
    printf("conta_str FINORA->%d\n",conta_str);
    }
pos=0;
/*Colonna sx->dx*/
printf("---Colonna sx->dx---\n");
while(mat[r][j]==s[pos] && pos<n && j<N_C){
    printf("mat[%d][%d]->%c = s[%d]->%c\n",r,j,mat[r][j],pos,s[pos]);
    pos++;
    printf("pos->%d\n",pos);
    j++;
    printf("j->%d\n",j);
    }
j=c;
if(pos==n){
    conta_str++;
    printf("conta_str FINORA->%d\n",conta_str);
    }
pos=0;
/*Colonna dx->sx*/
printf("---Colonna dx->sx---\n");
while(mat[r][j]==s[pos] && pos<n && j>=0){
    printf("mat[%d][%d]->%c = s[%d]->%c\n",r,j,mat[r][j],pos,s[pos]);
    pos++;
    printf("pos->%d\n",pos);
    j--;
    printf("j->%d\n",j);
    }
j=c;
if(pos==n){
    conta_str++;
    printf("conta_str FINORA->%d\n",conta_str);
    }
pos=0;
return conta_str;
}
