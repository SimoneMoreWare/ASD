#include "modello.h"

struct mod_s{
    char nome[MAX];
    Accessori accessori;
};


Modello MODELLOinit(){
    Modello m;
    m=(Modello)malloc(sizeof(struct mod_s));
    if(m==NULL) exit(EXIT_FAILURE);
    m->accessori=ACCESSORIinit();
    return m;
}


Modello MODELLOread(FILE *f){
   Modello m=MODELLOinit();
   char nomeFile[MAX];
   FILE *fi;
   if(fscanf(f, "%s %s", m->nome, nomeFile)==2){
      fi=fopen(nomeFile, "r");
      if(fi==NULL) exit(EXIT_FAILURE);
      m->accessori=ACCESSORIread(fi);
      return m;
   }
   return MODELLOsetNull();
}


void MODELLOprint(Modello m, FILE *f){
    fprintf(f, "\t%s\n", m->nome);
    fprintf(f, "\t\t---ACCESSORI---\n");
    if(ACCESSORIsize(m->accessori)>0)
       ACCESSORIprint(m->accessori, f);
    else
       fprintf(f, "\t\tNessun accessorio presente.\n");
    return;
}


Modello MODELLOsetNull(){
    return NULL;
}


Boolean MODELLOisNull(Modello m){
    if(m==NULL)
       return VERO;
    return FALSO;
}


char *MODELLOgetNome(Modello m){
    return m->nome;
}


Accessori MODELLOgetAccessori(Modello m){
    return m->accessori;
}


void MODELLOfree(Modello m){
    if(m!=NULL){
       ACCESSORIfree(m->accessori);
       free(m);
    }
    return;
}
