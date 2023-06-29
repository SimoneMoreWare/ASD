#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#define MAXC 9

typedef enum{VERO, FALSO}Boolean;
typedef enum{VERIFICA, RICERCA}Problema;

Boolean verifica(char *op1Lett, char *op2Lett, char *resLett, char *op1Num, char *op2Num, char *resNum);
int max(int a, int b);
void solve(char *op1Lett, char *op2Lett, char *resLett);
Boolean findCorrispondenze(char *val, int dimVal, char *op1Lett, int lenOp1, char *op2Lett, int lenOp2, char *resLett, int lenRes, int *mark, int *corrispondenze, int pos);
Boolean checkSolution(char *op1Lett, int lenOp1, char *op2Lett, int lenOp2, char *resLett, int lenRis, int *corrispondenze, char *op1Num, char *op2Num, char *resNum);

int main(){
    char op1Lett[MAXC], op2Lett[MAXC], resLett[MAXC+1];
    char op1Num[MAXC], op2Num[MAXC], resNum[MAXC+1];
    Problema problema;

    problema=VERIFICA;

    printf("Inserisci il primo operando letterale: ");
    gets(op1Lett);
    printf("\nInserisci il secondo operando letterale: ");
    gets(op2Lett);
    printf("\nInserisci il risultato letterale: ");
    gets(resLett);

    switch(problema){
        case VERIFICA:
            printf("\n---PROBLEMA DI VERIFICA---\n");
            printf("Inserisci il primo operando numerico: ");
            gets(op1Num);
            printf("\nInserisci il secondo operando numerico: ");
            gets(op2Num);
            printf("\nInserisci il risultato numerico: ");
            gets(resNum);

            if(verifica(op1Lett, op2Lett, resLett, op1Num, op2Num, resNum)==VERO){
                printf("\nSoluzione valida. %s + %s = %s (%s + %s = %s)\n", op1Lett, op2Lett, resLett, op1Num, op2Num, resNum);
            }
            else{
                printf("\nSoluzione non valida.\n");
            }
            break;
        case RICERCA:
            printf("\n---PROBLEMA DI RICERCA---\n");
            solve(op1Lett, op2Lett, resLett);
            break;
    }
    return 0;
}




Boolean verifica(char *op1Lett, char *op2Lett, char *resLett, char *op1Num, char *op2Num, char *resNum){
    int corrispondenze[26];
    int i, lenRis, lenOp1, lenOp2, op1, op2, res;

    if(strlen(op1Lett)!=strlen(op1Num) || strlen(op2Lett)!=strlen(op2Num) || strlen(resLett)!=strlen(resNum))
       return FALSO;
    if(op1Num[0]=='0' || op2Num[0]=='0' || resNum[0]=='0')
       return FALSO;

    lenRis=strlen(resLett);
    lenOp1=strlen(op1Lett);
    lenOp2=strlen(op2Lett);

    if(lenOp1==lenOp2 && lenRis!=lenOp1 && lenRis!=(lenOp1+1))
       return FALSO;
    if(lenOp1!=lenOp1 && lenRis!=max(lenOp1, lenOp2) && lenRis!=1+max(lenOp1, lenOp2))
       return FALSO;

    for(i=0; i<26; i++){
       corrispondenze[i]=-1;
    }

    for(i=0; i<lenOp1; i++){
       if(!isalpha(op1Lett[i]))
          return FALSO;
       if(!isdigit(op1Num[i]))
          return FALSO;
       if(corrispondenze[toupper(op1Lett[i])-'A']!=-1 && corrispondenze[toupper(op1Lett[i])-'A']!=(op1Num[i]-'0'))
          return FALSO;
       if(corrispondenze[toupper(op1Lett[i])-'A']==-1)
          corrispondenze[toupper(op1Lett[i])-'A']=(op1Num[i]-'0');
    }

    for(i=0; i<lenOp2; i++){
       if(!isalpha(op2Lett[i]))
          return FALSO;
       if(!isdigit(op2Num[i]))
          return FALSO;
       if(corrispondenze[toupper(op2Lett[i])-'A']!=-1 && corrispondenze[toupper(op2Lett[i])-'A']!=(op2Num[i]-'0'))
          return FALSO;
       if(corrispondenze[toupper(op2Lett[i])-'A']==-1)
          corrispondenze[toupper(op2Lett[i])-'A']=(op2Num[i]-'0');
    }

    for(i=0; i<lenRis; i++){
       if(!isalpha(resLett[i]))
          return FALSO;
       if(!isdigit(resNum[i]))
          return FALSO;
       if(corrispondenze[toupper(resLett[i])-'A']!=-1 && corrispondenze[toupper(resLett[i])-'A']!=(resNum[i]-'0'))
          return FALSO;
       if(corrispondenze[toupper(resLett[i])-'A']==-1)
          corrispondenze[toupper(resLett[i])-'A']=(resNum[i]-'0');
    }

    op1=atoi(op1Num);

    op2=atoi(op2Num);

    res=atoi(resNum);

    if((op1+op2)!=res)
       return FALSO;
    return VERO;
}

int max(int a, int b){
    if(a>b)
       return a;
     return b;
}


void solve(char *op1Lett, char *op2Lett, char *resLett){
    int mark[10], i;
    int corrispondenze[26];
    char val[MAXC+MAXC+MAXC+1];

    for(i=0; i<10; i++){
        mark[i]=0;
    }

    for(i=0; i<26; i++){
       corrispondenze[i]=-1;
    }

    strcpy(val, "");
    strcat(val, op1Lett);
    strcat(val, op2Lett);
    strcat(val, resLett);

    if(findCorrispondenze(val, strlen(val), op1Lett, strlen(op1Lett), op2Lett, strlen(op2Lett), resLett, strlen(resLett), mark, corrispondenze, 0)==FALSO)
        printf("Soluzione non trovata.\n");
}

Boolean findCorrispondenze(char *val, int dimVal, char *op1Lett, int lenOp1, char *op2Lett, int lenOp2, char *resLett, int lenRes, int *mark, int *corrispondenze, int pos){
    int number;
    char op1Num[MAXC], op2Num[MAXC], resNum[MAXC+1];

    if(pos>=dimVal){
        if(checkSolution(op1Lett, lenOp1, op2Lett, lenOp2, resLett, lenRes, corrispondenze, op1Num, op2Num, resNum)==VERO){
            printf("Solution: %s + %s = %s (%s + %s = %s)\n", op1Lett, op2Lett, resLett, op1Num, op2Num, resNum);
            return VERO;
        }
        return FALSO;
    }

    if(corrispondenze[toupper(val[pos])-'A']!=-1){
        if(findCorrispondenze(val, dimVal, op1Lett, lenOp1, op2Lett, lenOp2, resLett, lenRes, mark, corrispondenze, pos+1)==VERO)
            return VERO;
        return FALSO;
    }

    for(number=0; number<10; number++){
        if(mark[number]==0){
            if((pos==0 || pos==lenOp1 || pos==lenOp2) && number==0)
                continue;
            mark[number]=1;
            corrispondenze[toupper(val[pos])-'A']=number;
            if(findCorrispondenze(val, dimVal, op1Lett, lenOp1, op2Lett, lenOp2, resLett, lenRes, mark, corrispondenze, pos+1)==VERO)
                return VERO;
            mark[number]=0;
            corrispondenze[toupper(val[pos])-'A']=-1;
        }
    }
    return FALSO;
}


Boolean checkSolution(char *op1Lett, int lenOp1, char *op2Lett, int lenOp2, char *resLett, int lenRis, int *corrispondenze, char *op1Num, char *op2Num, char *resNum){
    int i, op1, op2, res;

    if(lenOp1==lenOp2 && lenRis!=lenOp1 && lenRis!=(lenOp1+1))
       return FALSO;

    if(lenOp1!=lenOp1 && lenRis!=max(lenOp1, lenOp2) && lenRis!=1+max(lenOp1, lenOp2))
       return FALSO;

    for(i=0; i<lenOp1; i++){
        op1Num[i]=(corrispondenze[toupper(op1Lett[i])-'A']+'0');
    }
    op1Num[lenOp1]='\0';

    for(i=0; i<lenOp2; i++){
        op2Num[i]=(corrispondenze[toupper(op2Lett[i])-'A']+'0');
    }
    op2Num[lenOp2]='\0';

    for(i=0; i<lenRis; i++){
        resNum[i]=(corrispondenze[toupper(resLett[i])-'A']+'0');
    }
    resNum[lenRis]='\0';

    if(op1Num[0]=='0' || op2Num[0]=='0' || resNum[0]=='0')
       return FALSO;

    op1=atoi(op1Num);

    op2=atoi(op2Num);

    res=atoi(resNum);

    if((op1+op2)!=res)
       return FALSO;
    return VERO;
}
