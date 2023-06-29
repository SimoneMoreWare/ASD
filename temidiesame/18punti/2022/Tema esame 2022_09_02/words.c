#include "words.h"

Word WORDread(FILE *f){
    Word w;
    fscanf(f, "%s %d", w.parola, &w.valore);
    return w;
}

Words WORDScrea(int dim){
    Words w;
    w.nParole=dim;
    w.parole=(Word*)malloc(dim*sizeof(Word));
    if(w.parole==NULL)
       exit(EXIT_FAILURE);
    return w;
}

Words WORDSread(FILE *f){
    Words w;
    int nParole, i;
    fscanf(f, "%d", &nParole);
    w=WORDScrea(nParole);
    for(i=0; i<nParole; i++)
       w.parole[i]=WORDread(f);
    return w;
}

static void merge(Word *w, Word *B, int left, int right, int mezzo){
    int i, j, k;

    i=left;
    j=mezzo+1;

    for(k=left; k<=right; k++){
        if(i>mezzo)
          B[k]=w[j++];
        else if(j>right)
            B[k]=w[i++];
        else if(w[i].valore > w[j].valore)
            B[k]=w[i++];
        else
           B[k]=w[j++];
    }
    for(k=left; k<=right; k++){
        w[k]=B[k];
    }
    return;
}

static void mergeSortR(Word *w, Word *B, int left, int right){
    int mezzo;
    if(left==right)
        return;
    mezzo=(left+right)/2;
    mergeSortR(w, B, left, mezzo);
    mergeSortR(w, B, mezzo+1, right);
    merge(w, B, left, right, mezzo);
    return;
}

void WORDSorder(Words w){
    Word *B;
    B=(Word*)malloc(w.nParole*sizeof(Word));
    if(B==NULL)
        exit(EXIT_FAILURE);
    mergeSortR(w.parole, B, 0, w.nParole-1);
    return;
}

void WORDSclear(Words w){
    if(w.parole!=NULL)
       free(w.parole);
    return;
}

