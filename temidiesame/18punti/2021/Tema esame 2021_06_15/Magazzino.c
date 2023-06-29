#include "Magazzino.h"

struct magazzino_s{
    int nCorridoi;
    Corridoio *corridoi;
};



Magazzino MAGAZZINOinit(){
    Magazzino m;
    m=(Magazzino)malloc(sizeof(struct magazzino_s));
    if(m==NULL){
        printf("Errore di allocazione.");
        exit(EXIT_FAILURE);
    }
    m->corridoi=NULL;
    m->nCorridoi=0;
    return m;
}


Magazzino MAGAZZINOread(FILE *f){
    Magazzino m=MAGAZZINOinit();
    int i;
    fscanf(f, "%d", &m->nCorridoi);
    m->corridoi=(Corridoio*)malloc(m->nCorridoi*sizeof(Corridoio));
    if(m->corridoi==NULL){
        printf("Errore di allocazione.");
        exit(EXIT_FAILURE);
    }
    for(i=0; i<m->nCorridoi; i++){
        m->corridoi[i]=CORRIDOIOread(f);
    }
    return m;
}


Boolean MAGAZZINOinserisciPacco(Magazzino m, Pacco *pa, Posizione po){
    if(po.corridoio<0 || po.corridoio>=m->nCorridoi){
        printf("\nImpossibile posizionare il pacco %s: il corridoio %d non esiste.\n", PACCOgetCode(pa), po.corridoio);
        return FALSO;
    }
    return CORRIDOIOinserisciPacco(m->corridoi[po.corridoio], pa, po);
}


void MAGAZZINOspostaPacco(Magazzino m, Pacco *pa, Posizione po){
    Posizione p=PACCOgetPosizione(*pa);
    if(po.corridoio<0 || po.corridoio>=m->nCorridoi){
        printf("\nImpossibile spostare il pacco %s: il corridoio %d non esiste.\n", PACCOgetCode(pa), po.corridoio);
        return;
    }
    if(CORRIDOIOinserisciPacco(m->corridoi[po.corridoio], pa, po)==VERO){
        CORRIDOIOeliminaPacco(m->corridoi[p.corridoio], pa, p);
        PACCOsetPosizione(pa, po.corridoio, po.scaffale, po.slot);
        printf("\nSpostamento avvenuto con successo.\n");
    }
    return;
}


void MAGAZZINOeliminaPacco(Magazzino m, Pacco *pa){
    Posizione p;
    p=PACCOgetPosizione(*pa);
    if(POSIZIONEisEmpty(p)==VERO){
        printf("\nImpossibile estrarre il pacco %s in quanto non ancora posizionato nel magazzino.\n", PACCOgetCode(pa));
        return;
    }
    CORRIDOIOeliminaPacco(m->corridoi[p.corridoio], pa, p);
    printf("\nEstrazione avvenuta con successo.\n");
    return;
}


void MAGAZZINOcompattaScaffali(Magazzino m, int corridoio1, char *scaffale1, int corridoio2, char *scaffale2){
    Scaffale s1, s2;
    if(corridoio1<0 || corridoio1>=m->nCorridoi){
        printf("\nImpossibile compattare gli scaffali: il corridoio %d non esiste.\n", corridoio1);
        return;
    }
    if(corridoio2<0 || corridoio2>=m->nCorridoi){
        printf("\nImpossibile compattare gli scaffali: il corridoio %d non esiste.\n",  corridoio2);
        return;
    }
    s1=CORRIDOIOsearchScaffale(m->corridoi[corridoio1], scaffale1);
    if(SCAFFALEisEmpty(s1)==VERO){
        printf("\nImpossibile compattare gli scaffali in quanto %s non e' presente nel corridoio %d.\n", scaffale1, corridoio1);
        return;
    }
    s2=CORRIDOIOsearchScaffale(m->corridoi[corridoio2], scaffale2);
    if(SCAFFALEisEmpty(s2)==VERO){
        printf("\nImpossibile compattare gli scaffali in quanto %s non e' presente nel corridoio %d.\n",  scaffale2, corridoio2);
        return;
    }
    if(SCAFFALEcompatta(s1, corridoio1, s2, corridoio2)==VERO){
        printf("\nCompattazione avvenuta con successo.\n");
    }
    return;
}


void MAGAZZINOprint(Magazzino m, FILE *f){
    int i;
    for(i=0; i<m->nCorridoi; i++){
        CORRIDOIOprint(m->corridoi[i], f);
        fprintf(f, "\n");
    }
}


void MAGAZZINOfree(Magazzino m){
    int i;
    if(m!=NULL){
        for(i=0; i<m->nCorridoi; i++){
            CORRIDOIOfree(m->corridoi[i]);
        }
        free(m);
    }
    return;
}
