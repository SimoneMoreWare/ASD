#include "Corridoio.h"
#include <string.h>

struct corridoio_s{
    int id, nScaffali;
    Scaffale *scaffali;
};



Corridoio CORRIDOIOinit(){
    Corridoio c;
    c=(Corridoio)malloc(sizeof(struct corridoio_s));
    if(c==NULL){
        printf("Errore di allocazione.");
        exit(EXIT_FAILURE);
    }
    c->id=0;
    c->nScaffali=0;
    c->scaffali=NULL;
    return c;
}


Corridoio CORRIDOIOread(FILE *f){
    int i;
    Corridoio c=CORRIDOIOinit();
    fscanf(f, "%d", &c->id);
    fscanf(f, "%d", &c->nScaffali);
    c->scaffali=(Scaffale *)malloc(c->nScaffali*sizeof(Scaffale));
    if(c->scaffali==NULL){
        printf("Errore di allocazione.");
        exit(EXIT_FAILURE);
    }
    for(i=0; i<c->nScaffali; i++){
       c->scaffali[i]=SCAFFALEread(f);
    }
    return c;
}


Boolean CORRIDOIOinserisciPacco(Corridoio c, Pacco *pa, Posizione po){
    Scaffale s=CORRIDOIOsearchScaffale(c, po.scaffale);
    if(SCAFFALEisEmpty(s)==VERO){
        printf("\nImpossibile posizionare il pacco %s: lo scaffale %s non e' presente nel corridoio %d.\n", PACCOgetCode(pa), po.scaffale, c->id);
        return FALSO;
    }
    return SCAFFALEinserisciPacco(s, pa, po);
}


void CORRIDOIOeliminaPacco(Corridoio c, Pacco *pa, Posizione po){
    Scaffale s=CORRIDOIOsearchScaffale(c, po.scaffale);
    SCAFFALEeliminaPacco(s, pa, po);
    return;
}


void CORRIDOIOprint(Corridoio c, FILE *f){
    int i;
    fprintf(f, "CORRIDOIO: %d\n", c->id);
    if(c->nScaffali > 0){
       fprintf(f, "\tSCAFFALI: ");
       for(i=0; i<c->nScaffali; i++){
            SCAFFALEprint(c->scaffali[i], f);
            fprintf(f, "\n\t          ");
       }
    }
    return;
}


Scaffale CORRIDOIOsearchScaffale(Corridoio c, char *scaffale){
    int i;
    for(i=0; i<c->nScaffali; i++){
        if(strcmp(scaffale, SCAFFALEgetCode(c->scaffali[i]))==0){
            return c->scaffali[i];
        }
    }
    return SCAFFALEsetNull();
}


void CORRIDOIOfree(Corridoio c){
    int i;
    if(c!=NULL){
        for(i=0; i<c->nScaffali; i++){
            SCAFFALEfree(c->scaffali[i]);
        }
        free(c);
    }
    return;
}
