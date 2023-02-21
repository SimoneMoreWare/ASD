/*
    matrice di caratteri mat
    r righe
    c colonne
    string s
    la funzione conti quante volte la stringa appare in orizzontale o verticale
*/

#include <stdio.h>
#include <string.h>

int mat_search (char mat[4][5], int r, int c, char *s){
    int i,j,k;
    char first = s[0];
    int start_riga,start_colonna;
    int lenstringa = (int) strlen(s);
    int res=0;
    int countciclo;
    int flagstop;
    int count_char;

    for(i=0;i<r;i++){
        for(j=0;j<c;j++){
            if(mat[i][j] == first){
                start_riga = i;
                start_colonna = j;

                count_char = 1;
                flagstop=0;
                for(k=start_riga+1,countciclo=1;countciclo<lenstringa && k<r;countciclo++ && flagstop==0,k++){
                    if(mat[k][j] == s[count_char]) count_char ++;
                    else flagstop=1;
                }
                if(count_char==lenstringa) res++;

                count_char = 1;
                flagstop=0;
                for(k=start_riga-1 , countciclo=1 ;countciclo<lenstringa && k>=0 && flagstop==0; k--,countciclo++){
                    if(mat[k][j] == s[count_char]) count_char ++;
                    else flagstop=1;
                }
                if(count_char==lenstringa) res++;

                count_char=1;
                flagstop=0;
                for(k=start_colonna+1,countciclo=1;countciclo<lenstringa && k<c && flagstop==0; k++,countciclo++){
                    if(mat[i][k] == s[count_char]) count_char++;
                    else flagstop=1;
                }
                if(count_char==lenstringa) res++;

                count_char=1;
                flagstop=0;
                for(k=start_colonna-1,countciclo=1;countciclo<lenstringa && k>=0 && flagstop==0; k--,countciclo++){
                    if(mat[i][k] == s[count_char]) count_char++;
                    else flagstop=1;
                }
                if(count_char==lenstringa) res++;

            }
        }
    }

    return res;
}

int main(){
    char mat[4][5] = {
            {'x','f','o','o','x'},
            {'y','o','x','z','f'},
            {'x','o','2','f','o'},
            {'g','f','o','o','o'}
    };

    int r=4;
    int c=5;
    char s[]="foo";
    int res;
    res= mat_search(mat,r,c,s);
    printf("%d",res);
    return  0;
}
