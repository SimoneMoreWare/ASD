#include "vincoli.h"

Vincoli VINCOLIread(FILE *f){
   Vincoli v;
   int i;
   fscanf(f, "%d", &v.dim);
   v.vincoli=(Vincolo*)malloc(v.dim*sizeof(Vincolo));
   if(v.vincoli==NULL) exit(EXIT_FAILURE);
   for(i=0; i<v.dim; i++)
      v.vincoli[i]=VINCOLOread(f);
   return v;
}


void VINCOLIclear(Vincoli v){
   int i;
   if(v.vincoli!=NULL){
     for(i=0; i<v.dim; i++)
        VINCOLOclear(v.vincoli[i]);
     free(v.vincoli);
   }
   return;
}
