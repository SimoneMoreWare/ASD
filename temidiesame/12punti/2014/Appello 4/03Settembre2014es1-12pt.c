#include <stdio.h>
#include <stdlib.h>

void searchStr(char *str, int *start, int *length);

int main()
{
    char str[15] = "abbcccddddeeeee";
    int start = 0, length = 0;

    searchStr(str,&start,&length);

    printf("start: %d - length: %d", start, length);

    return 0;
}

void searchStr(char *str, int *start, int *length){
    int i=0, j=0;

    while(str[i]!='\0'){
        while(str[j]==str[i])
            j++;
        if(j-i > *length){
            *length = j-i;
            *start = i;
        }
        i=j;
    }
}
