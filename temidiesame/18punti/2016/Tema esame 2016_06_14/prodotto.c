#include "prodotto.h"

Prodotto PRODOTTOcrea(char *id, char *nome, char *categoria, float prezzo, int disp){
   Prodotto p;
   strcpy(p.id, id);
   strcpy(p.nome, nome);
   strcpy(p.categoria, categoria);
   p.prezzo=prezzo;
   p.disponibilita=disp;
   return p;
}


void PRODOTTOsetDisponibilita(Prodotto *p, int disp){
   p->disponibilita=disp;
   return;
}


void PRODOTTOprint(Prodotto p, FILE *f){
   fprintf(f, "%s %s %s %.2f %d\n", p.id, p.nome, p.categoria, p.prezzo, p.disponibilita);
   return;
}
