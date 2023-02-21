#include <stdio.h>
#include <string.h>
int conta(char matrice[4][5], int n, int m, char *stringa) {

    int i, j;
    int k;
    char firstchar = stringa[0];
    int lunghezzastringa = (int) strlen(stringa);
    int flag;
    int cnt;
    int res = 0;
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {

            if (firstchar == matrice[i][j]) {

                flag = 1;
                cnt = 1;
                if (i + lunghezzastringa <= n) {
                    for (k = i + 1; k < i + lunghezzastringa && flag == 1; k++) {
                         if (matrice[k][j] == stringa[cnt]) {
                            cnt++;
                        } else {
                            flag = 0;
                        }
                    }
                    if (cnt == lunghezzastringa) res++;
                }

                flag = 1;
                cnt = 1;
                if (j + lunghezzastringa <= m) {
                    for (k = j + 1; k < j + lunghezzastringa && flag == 1; k++) {
                        if (matrice[i][k] == stringa[cnt]) {
                            cnt++;
                        } else {
                            flag = 0;
                        }
                    }
                    if (cnt == lunghezzastringa) res++;
                }
            }
        }
    }
    return res;
}

int main(){
    char matrice[4][5] = {
            {'x','c','e','c','a'},
            {'w','a','e','c','q'},
            {'d','t','p','a','z'},
            {'p','c','a','t','f'}
    };
    int n=4;
    int m=5;
    char stringa[]="cat";
    int res;
    res=conta(matrice,n,m,stringa);
    printf("%d ",res);
    return 0;
}
