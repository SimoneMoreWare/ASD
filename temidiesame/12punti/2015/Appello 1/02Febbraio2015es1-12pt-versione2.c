#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 12

void eraseDuplicate(char *str);

int main()
{
    char str[N] = "aaa;;;bbbab";

    printf("str before eraseDuplicate: %s\n", str);

    eraseDuplicate(str);

    printf("str after eraseDuplicate: %s\n", str);

    return 0;
}

void eraseDuplicate(char *str){
    int i=0,j,notFound;
    char str2[N] = "";

    while(str[i]!='\0'){
        j=0;
        notFound = 1;
        //if the second string is empty, directly insert the first element of the first string
        if(strcmp(str2,"")==0){
            //i and j are equal to 0
            str2[j]=str[i];
        }else {
            for(j=0; str2[j]!='\0' && notFound; j++){
                if(str[i]==str2[j]){
                    notFound = 0;
                }
            }
            if(notFound)
                str2[j]=str[i];
        }
        i++;
    }
    
    strcpy(str,str2);
    
    return;
}
