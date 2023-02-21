/*   main.c
 *   @author  : Gabriele Iurlaro
 *   @  site  : http://iurlaro.com
 *   @Modified: 22/12/2020, 19:40:22
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 10

typedef struct{
    char c;
    int val;
}alpha;

int alphaSearch(alpha *table, char c){
    int i;
    for(i=0; i<N; i++)
        if(table[i].c == c)
            return i;
    return -1;
}

int alphaRead(alpha *table, char *s1, char *s2, char *s3){
    int dim = 0,i;
    for(i=0; s1[i] != '\0'; i++){
        if(alphaSearch(table, s1[i]) == -1) {
            table[dim].c = s1[i];
            table[dim++].val = -1;
        }
    }
    for(i=0; s2[i] != '\0'; i++){
        if(alphaSearch(table, s2[i]) == -1) {
            table[dim].c = s2[i];
            table[dim++].val = -1;
        }
    }
    for(i=0; s3[i] != '\0'; i++){
        if(alphaSearch(table, s3[i]) == -1) {
            table[dim].c = s3[i];
            table[dim++].val = -1;
        }
    }
    return dim;
}

void fillTableManually(alpha *table, int dim){
    int i;
    for(i=0; i<dim; i++) {
        printf("%c: ", table[i].c);
        scanf("%d", &table[i].val);
    }
}

int stringToInteger(alpha *table, char *s){
    int i, val = 0;
    unsigned int len = strlen(s);
    for(i=0; i<strlen(s); i++){
        val = val*N + table[alphaSearch(table, s[i])].val;
    }
    return val;
}

int check(alpha *table, char *s1, char *s2, char *s3){
    int id1, id2, id3;
    if(table[alphaSearch(table, s1[0])].val == 0 || table[alphaSearch(table, s2[0])].val == 0 || table[alphaSearch(table, s2[0])].val == 0)
        return 0;
    id1 = stringToInteger(table, s1);
    id2 = stringToInteger(table, s2);
    id3 = stringToInteger(table, s3);
#ifdef DBG
    printf("%d + %d = %d",id1,id2, id3);
#endif
    return ((id1+id2)==id3);
}

int generaSoluzioneR(int pos, alpha *table, int n, int *mark, char *s1, char *s2, char *s3){
    int i;
    if(pos == n){
        if(check(table, s1, s2, s3)){
            for(i=0; i<n; i++){
                printf("%c: %d\n", table[i].c, table[i].val);
            }
            return 1;
        }
        return 0;
    }
    for(i=0; i<N; i++){
        if(mark[i]==0) {
            table[pos].val = i;
            mark[i] = 1;
            if(generaSoluzioneR(pos+1, table, n, mark, s1, s2, s3))
                return 1;
            table[pos].val = -1;
            mark[i] = 0;
        }
    }
    return 0;
}
void generaSoluzione(alpha *table, int dim, char *s1, char *s2, char *s3){
    int *mark, i;
    mark = malloc(N* sizeof(int));
    for(i=0; i<N; i++)
        mark[i] = 0;
    generaSoluzioneR(0, table, dim, mark, s1, s2, s3);
}
int main(){
    alpha table[N];
    int n;
    int scelta;
    char s1[11], s2[11], s3[11];
    printf("Inserire tre stringhe: ");
    scanf("%s %s %s", s1, s2, s3);
    n = alphaRead(table, s1, s2, s3);
    printf("Generare automaticamente la soluzione? [y1, n0]\n>");
    scanf("%d", &scelta);
    if(!scelta) {
        fillTableManually(table, n);
        if (check(table, s1, s2, s3))
            printf("La soluzione in input e' corretta.\n");
        else
            printf("La soluzione in input non e' corretta.\n");
    }
    generaSoluzione(table, n, s1, s2, s3);
}