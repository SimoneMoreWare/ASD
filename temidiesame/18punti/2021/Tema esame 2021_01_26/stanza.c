#include "stanza.h"

Stanza STANZAread(FILE *f){
      Stanza s;
      fscanf(f, "%s %d %d %d", s.nome, &s.livello, &s.V, &s.O);
      return s;
}


char* STANZAgetNome(Stanza *s){
    return s->nome;
}


void STANZAprint(Stanza s, FILE *f){
	fprintf(f, "%s", s.nome);
      return;
}
