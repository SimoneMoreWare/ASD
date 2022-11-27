#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "ST.h"

struct symboltable {char **vectname; char**vectsubnet; int maxN; int N;};


ST STinit(int maxN) {
    ST st;
    st = malloc(sizeof (*st));
    if (st == NULL) {
        printf("Memory allocation error\n");
        return NULL;
    }
    st->vectname = calloc(maxN, sizeof(char *));
    if (st->vectname == NULL) {
        printf("Memory allocation error\n");
        free(st);
        return NULL;
    }
    st->vectsubnet = calloc(maxN, sizeof(char *));
    if (st->vectsubnet == NULL) {
        printf("Memory allocation error\n");
        free(st);
        return NULL;
    }
    st->maxN = maxN;
    st->N = 0;
    return st;
}



void STfree(ST st) {
    int i;
    if (st==NULL) return;
    for (i=0; i<st->N; i++){
        if (st->vectname[i] != NULL) free(st->vectname[i]);
        if (st->vectsubnet[i] != NULL) free(st->vectsubnet[i]);
    }
    free(st->vectname);
    free(st->vectsubnet);
    free(st);
}

int STsize(ST st) {
    return st->N;
}

int STinsert(ST st, char *name,char *subnet) {
    if(st->N == st->maxN) {
        st->maxN *= 2;
        st->vectname = realloc(st->vectname, st->maxN * sizeof(char *));
        st->vectsubnet = realloc(st->vectsubnet, st->maxN * sizeof(char *));
    }
    st->vectname[st->N] = strdup(name);
    st->vectsubnet[st->N] = strdup(subnet);
    st->N++;
    return st->N - 1;
}

int stgetindex(ST st, char *name) {
    for(int i = 0; i < st->N; i++) {
        if(strcmp(name, st->vectname[i]) == 0)
            return i;
    }

    //fprintf(stderr,"Nome non trovato.\n");
    return -1;
}
int STsearch(ST st, char *str) {
    int i;
    for (i = 0; i  < st->N; i++)
        if (st->vectname[i]!=NULL && strcmp(str, st->vectname[i])==0)
            return i;
    return -1;
}

char *STsearchByIndexName(ST st, int i){
    if (i < 0 || i >= st->N)
        return NULL;
    return (st->vectname[i]);
}

char *STsearchByIndexSubnet(ST st, int i){
    if (i < 0 || i >= st->N)
        return NULL;
    return (st->vectsubnet[i]);
}

void STsort(ST st,int *v){
    int i,j,temp,n= STsize(st);

    for(i=0;i<n;i++) v[i]=i;
    for(i = 0; i < n - 1; i++) {
        for(j = 0; j < n - 1 - i; j++) {
            //printf("comparing %s and %s, ret = %d\n",st->vect_name[v[j]],st->vect_name[v[j+1]], strcmp(st->vect_name[j],st->vect_name[j+1]));
            if(strcmp(st->vectname[v[j]],st->vectname[v[j+1]]) >= 0) {
                //printf("swapping j=%d and %d\n",j,j+1);
                temp = v[j];
                v[j] = v[j+1];
                v[j+1] = temp;
            }
        }
    }
}
