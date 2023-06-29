#include "vincolo.h"

Vincolo VINCOLOread(FILE*f){
   Vincolo v;
   int i;
   fscanf(f, "%d", &v.nGruppi);
   v.dim=(int*)malloc(v.nGruppi*sizeof(int));
   if(v.dim==NULL) exit(EXIT_FAILURE);
   for(i=0; i<v.nGruppi; i++)
      fscanf(f, "%d", &v.dim[i]);
   v.nGruppiInseriti=0;
   return v;
}


void VINCOLOclear(Vincolo v){
   if(v.dim!=NULL)
      free(v.dim);
   return;
}
