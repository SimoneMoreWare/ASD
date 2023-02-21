#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 *
 *                  #(20)
                  /       \
             #(12)         #(8)
            /     \        /     \
          A(6)     C(6) E(5)     #(3)
                                 /   \
                             B(1)    D(2)
 */
typedef struct Nodo{
    char carattere;
    int peso;
    struct Nodo *sinistro, *destro;
} nodo;

typedef nodo *H;

char *decode(H h, char *str) {
    int i = 0;
    int str_len = (int) strlen(str); //tramite la lunghezza della stringa capisco quante iterazioni devo fare
    int k = 0;
    char *output = malloc(sizeof(char) * str_len);

    H temp = h;//parto dalla radice
    while (i < str_len) {
        if (str[i] == '0') { //se il carattere attuale della stringa è 0 mi sposto a sinistra
            temp = temp->sinistro;
        } else { //se il carattere attuale della stringa è 1 mi sposto a destra
            temp = temp->destro;
        }
        //ma quando mi fermo? mi fermo nel momento in cui arrivo a una foglia
        //come posso capire quando arrivo a una foglia? arrivo ad una foglia
        // nel momento in cui il figlio destro e sinitro del nodo attuale
        //arrivando a una foglia siginifica che sono arrivato ad un carattere 
        //che posso inserire nella stringa
        if (temp->sinistro == NULL && temp->destro == NULL) {
            output[k++] = temp->carattere; //inserisco carattere della foglia nel risultato
            temp = h; //resetto il nodo temporale con la radice dell albero
        }
        i++;//scorro nella sequenza
    }
    output[k] = '\0';//aggiungo carattere di terminazione
    return output;
    
    /*
     * riepilogo
     * vedo quante iterazioni fare, vedendo quanto è lunga la stringa
     * itero sulla sequenza
     * in base al valore della sequenza nell-iesima posizione capisco dove spostarmi sull albero
     * mi fermo quando arrivo una foglia aggiungendo il valore della foglia al risultato
     * resetto il nodo temporale alla radice dell albero
     */
}

int main() {
    H h = malloc(sizeof(nodo));
    h->carattere='#';
    h->peso=20;

    h->sinistro=malloc(sizeof(nodo));
    h->sinistro->carattere='#';
    h->sinistro->peso=12;

    h->sinistro->sinistro = malloc(sizeof(nodo));
    h->sinistro->sinistro->peso = 6;
    h->sinistro->sinistro->carattere = 'A';
    h->sinistro->sinistro->sinistro=NULL;
    h->sinistro->sinistro->destro=NULL;

    h->sinistro->destro = malloc(sizeof(nodo));
    h->sinistro->destro->peso=6;
    h->sinistro->destro->carattere='C';
    h->sinistro->destro->sinistro=NULL;
    h->sinistro->destro->destro=NULL;

    h->destro = malloc(sizeof(nodo));
    h->destro->carattere='#';
    h->destro->peso = 8;

    h->destro->sinistro=malloc(sizeof(nodo));
    h->destro->sinistro->peso=5;
    h->destro->sinistro->carattere='E';
    h->destro->sinistro->sinistro=NULL;
    h->destro->sinistro->destro=NULL;

    h->destro->destro = malloc(sizeof(nodo));
    h->destro->destro->carattere = '#';
    h->destro->destro->peso = 3;

    h->destro->destro->sinistro=malloc(sizeof(nodo));
    h->destro->destro->sinistro->carattere='B';
    h->destro->destro->sinistro->peso=1;
    h->destro->destro->sinistro->sinistro=NULL;
    h->destro->destro->sinistro->destro=NULL;

    h->destro->destro->destro=malloc(sizeof(nodo));
    h->destro->destro->destro->peso=2;
    h->destro->destro->destro->carattere='D';
    h->destro->destro->destro->destro=NULL;
    h->destro->destro->destro->sinistro=NULL;

    char *str = "0000000000001100101010101011111111010101010";
    char *output = decode(h, str);
    printf("%s\n", output);
    free(output);
    free(h->sinistro);
    free(h->destro);
    free(h);
    return 0;
}
