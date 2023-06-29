#include "word.h"
#include <string.h>

Word WORDcrea(char*parola){
    Word w;
	strcpy(w.parola, parola);
	w.preso=FALSO;
	return w;
}

Simboli WORDcompare(Word w1, Word w2){
	if(strcmp(w1.parola, w2.parola)==0)
		return UGUALE;
	if(strcmp(w1.parola, w2.parola)<0)
		return PRIMA;
	return DOPO;
}
