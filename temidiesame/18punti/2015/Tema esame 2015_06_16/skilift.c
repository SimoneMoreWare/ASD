#include "skilift.h"

Skilift SKILIFTinit(){
   Skilift s;
   s.passaggi=AUTORIZZAZIONISKinit();
   return s;
}


Skilift SKILIFTread(FILE *f){
   Skilift s=SKILIFTinit();
   int timeInterval;
   char skiliftId[MAX];
   if(fscanf(f, "%s %d", skiliftId, &timeInterval)==2){
      strcpy(s.skiliftId, skiliftId);
      s.timeInterval=timeInterval;
      return s;
   }
   return SKILIFTsetNull();
}


Skilift SKILIFTsetNull(){
   Skilift s;
   strcpy(s.skiliftId, "");
   s.timeInterval=-1;
   return s;
}


Boolean SKILIFTisNull(Skilift s){
   if(strcmp(s.skiliftId, "")==0 && s.timeInterval==-1)
      return VERO;
   return FALSO;
}


void SKILIFTaddPassaggio(Skilift *s, AutorizzazioneSk as){
    (as.nVolte)++;
    AUTORIZZAZIONISKadd(s->passaggi, as);
    return;
}


AutorizzazioneSk *SKILIFTcercaPassaggioSciatore(Skilift s, long sciatore){
    return AUTORIZZAZIONISKsearch(s.passaggi, sciatore);
}


void SKILIFTprint(Skilift s, FILE *f){
    fprintf(f, "Skilift %s (intervallo: %d minuti):\n", s.skiliftId, s.timeInterval);
    fprintf(f, "\t---PASSAGGI---\n");
    if(AUTORIZZAZIONISKsize(s.passaggi)==0){
        fprintf(f,"\tNessuno sciatore passato.\n");
        return;
    }
    AUTORIZZAZIONISKprint(s.passaggi, f);
    return;
}


void SKILIFTclear(Skilift s){
   AUTORIZZAZIONISKfree(s.passaggi);
   return;
}
