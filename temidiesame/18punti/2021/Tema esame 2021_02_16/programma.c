#include "programma.h"
#include <string.h>

Programma PROGRAMMAcrea(int nr, int nc, int empty){
    Programma p;
    int i, j;
    p.mat=(int**)malloc(nr*sizeof(int*));
    if(p.mat==NULL)
        exit(EXIT_FAILURE);
    for(i=0; i<nr; i++){
        p.mat[i]=(int*)malloc(nc*sizeof(int));
        if(p.mat[i]==NULL)
            exit(EXIT_FAILURE);
    }
    p.nr=nr;
    p.nc=nc;
    for(i=0; i<nr; i++)
        for(j=0; j<nc; j++)
            p.mat[i][j]=empty;
    return p;
}

Boolean PROGRAMMAcheck(int nr, int nc, int empty, Articoli ar, char *nomeFile){
    FILE *f;
    Programma p;
    int nArticoli, articolo, room, slot, nSlot, i, j;
    Articolo a, prec,succ;

    f=fopen(nomeFile, "r");
    if(f==NULL) exit(EXIT_FAILURE);

    p=PROGRAMMAcrea(nr, nc, empty);

    fscanf(f, "%d", &nArticoli);
    if(nArticoli!=ARTICOLIgetNumArticoli(ar))
        return FALSO;

    for(i=0; i<nArticoli; i++){
        articolo=i;
        a=ARTICOLIgetArticolo(ar, articolo);
        fscanf(f, "%d %d %d", &room, &slot, &nSlot);
        if(a.slot!=nSlot)
            return FALSO;
        if(room<0 || room>=nr)
            return FALSO;
        if(slot<0 || slot>=nc)
            return FALSO;
        if(slot+nSlot>nc)
            return FALSO;
        if(p.mat[room][slot]!=empty)
            return FALSO;
        if(nSlot>1){
            for(j=slot+1; j<slot+nSlot; j++){
                if(p.mat[room][j]!=empty)
                    return FALSO;
            }
        }
        if(room>0 && p.mat[room-1][slot]!=empty){
            prec=ARTICOLIgetArticolo(ar, p.mat[room-1][slot]);
            if(strcmp(a.relatore, prec.relatore)==0){
                return FALSO;
            }
        }
        if(room<(nr-1) && p.mat[room+1][slot]!=empty){
            succ=ARTICOLIgetArticolo(ar, p.mat[room+1][slot]);
            if(strcmp(a.relatore, succ.relatore)==0){
                return FALSO;
            }
        }
        PROGRAMMAinsertArticolo(&p, articolo, room, slot, nSlot);
    }
    return VERO;
}

void PROGRAMMAinsertArticolo(Programma *p, int articolo, int room, int slot, int nSlot){
    int i;
    for(i=slot; i<slot+nSlot; i++)
        p->mat[room][i]=articolo;
    return;

}

void PROGRAMMAeliminaArticolo(Programma *p, int empty, int room, int slot, int nSlot){
    int i;
    for(i=slot; i<slot+nSlot; i++)
        p->mat[room][i]=empty;
}

static int argomentiDistintiStanza(int *stanza, int dim, ST argomenti, Articoli ar){
    int *occ, nArgomenti, NA_i=0, i;
    Articolo a;

    nArgomenti=STcount(argomenti);
    occ=(int*)calloc(nArgomenti, sizeof(int));
    if(occ==NULL)
        exit(EXIT_FAILURE);

    for(i=0; i<dim; i++){
        a=ARTICOLIgetArticolo(ar, stanza[i]);
        occ[STsearch(argomenti, a.argomento)]++;
    }
    for(i=0; i<nArgomenti; i++){
        if(occ[i]!=0)
            NA_i++;
    }
    return NA_i;
}

int PROGRAMMAargomentiDistinti(Programma p, ST argomenti, Articoli ar){
    int NA=0, i;
    for(i=0; i<p.nr; i++){
        NA=NA+argomentiDistintiStanza(p.mat[i], p.nc, argomenti, ar);
    }
    return NA;
}

int PROGRAMMAslotVuoti(Programma p, int empty){
    int riga, colonna, lastArticolo, count=0;
    for(riga=0; riga<p.nr; riga++){
        lastArticolo=empty;
        for(colonna=(p.nc-1); colonna>=0; colonna--){
            if(lastArticolo==empty && p.mat[riga][colonna]!=empty){
                lastArticolo=p.mat[riga][colonna];
            }
            else if(lastArticolo!=empty && p.mat[riga][colonna]==empty)
                count++;
            else if(lastArticolo==empty && p.mat[riga][colonna]==empty)
                continue;
         }
     }
     return count;
}

void PROGRAMMAprint(Programma p, Articoli a, int empty, FILE *f){
    int i, j;
    Articolo ar;

    for(j=0; j<p.nc; j++){
        for(i=0; i<p.nr; i++){
            if(p.mat[i][j]==empty)
                fprintf(f, "---\t");
            else{
                ar=ARTICOLIgetArticolo(a, p.mat[i][j]);
                ARTICOLOprint(ar, f);
                fprintf(f, "\t", p.mat[i][j]);
            }
        }
        fprintf(f, "\n");
    }
    return;
}

void PROGRAMMAclear(Programma p){
    int i;
    if(p.mat!=NULL){
        for(i=0; i<p.nr; i++){
            if(p.mat[i]!=NULL)
                free(p.mat[i]);
        }
        free(p.mat);
    }
    return;
}
