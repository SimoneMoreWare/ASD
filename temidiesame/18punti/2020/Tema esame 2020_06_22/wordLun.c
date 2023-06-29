#include "wordLun.h"

WordLun WORDLUNinit(){
    WordLun w;
    w.nParole=0;
    w.maxD=1;
    w.parole=(Word*)malloc(w.maxD*sizeof(Word));
    if(w.parole==NULL)
        exit(-1);
    return w;
}

void WORDLUNinsertWord(WordLun *wl, Word w){
    if(wl->maxD==wl->nParole){
        wl->maxD=(wl->maxD)*2;
        wl->parole=realloc(wl->parole, wl->maxD*sizeof(Word));
        if(wl->parole==NULL)
            exit(-1);
    }
	wl->parole[(wl->nParole)]=w;
	(wl->nParole)++;
	return;
}

int WORDLUNgetNumParole(WordLun w){
     return w.nParole;
}

Word *WORDLUNgetParole(WordLun w){
	return w.parole;
}

void WORDLUNfree(WordLun w){
	if(w.parole !=NULL)
        free(w.parole);
    return;
}

Boolean WORDLUNisThere(WordLun wl, Word w){
	int i;
	for(i=0; i<wl.nParole; i++){
        if(WORDcompare(wl.parole[i], w)==UGUALE)
			return VERO;
    }
	return FALSO;
}



void WORDLUNprint(WordLun w, FILE*f){
    int i;
    for(i=0; i<w.nParole; i++){
       fprintf(f, "%s\n", w.parole[i].parola);
    }
    return;
}
