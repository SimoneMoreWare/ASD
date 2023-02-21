#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_STRING 26

typedef struct node node_t;

struct node {
    char *substr;
    node_t *next;
};

typedef struct List{
   node_t *head;
}list;

node_t *splitStr(char *str);
void insertNode(list *l, char *substr);

int main()
{
    list l;
    node_t *x;
    char str[MAX_STRING] = "a.bb.ccc.dddd.eeeee.fffff";

    l.head = splitStr(str);

    printf("[HEAD] -> ");
    for(x = l.head; x!=NULL; x = x->next)
        printf("[%s] -> ", x->substr);
    printf("NULL");

    return 0;
}

node_t *splitStr(char *str){
    char tmp[MAX_STRING] = "";
    int i=0, j=0, k;
    list *l = malloc(sizeof(*l));
    l->head = NULL;

    while(str[i]!='\0'){
        while(str[j]!= '.' && str[j]!='\0')
            j++;

        for(k=0;k<j-i;k++){
            tmp[k] = str[i+k];
        }
        tmp[k+1] = '\0';

        insertNode(l, tmp);

        if(str[j]=='.')
            j++;

        i = j;
    }

    return l->head;
}

void insertNode(list *l, char *substr){
    node_t *x = malloc(sizeof(*x));
    x->next = NULL;
    x->substr = strdup(substr);

    if(l->head!=NULL)
        x->next = l->head;
    l->head = x;
}
