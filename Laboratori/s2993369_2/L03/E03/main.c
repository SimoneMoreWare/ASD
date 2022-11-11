/*
 * file pg.txt
 * contiene dettagli di alcuni personaggi di un gioco di ruolo
 *      numero di personaggi presenti in lista non noto a priori
 *      i dettagli di ogni personaggi sono riportati in ragione di uno per riga
 *          in ogni riga sono presenti tre stringhe
 *              codice identificativo univoco
 *                  PGXXXX
 *                      rappresenta una cifra nell'intervallo 0-9
 *              nome del personaggio
 *                  stringa priva di spazi di max 50 caratteri
 *              sua classe
 *                  stinga priva di spazi di max 50 caratteri
 *              sestupla a rappresentare le statitistiche
 *                  <hp> <mp> <atk> <def> <mag> <spr>
 *                  staatistiche dei numeri interi positivi o nulli
 *
 * secondo file di testo
 *      inventario .txt
 *      memorizzati dettagli di una serie di oggetti
 *      a cui i personaggi del gioco hanno accesso
 *      file organizzato come segue
 *          prima riga numero di O oggetti
 *          sulle O righe succesive
 *              dettagli di ogni oggetto disponibile
 *              ogni oggetto caratterizato da
 *                  nome
 *                      stringa priva di spazi max 50 char
 *                  tipologia
 *                      stringa priva di spazi max 50 char
 *                  sestupla
 *                      rappresenta modificatori delle statitistiche base di un personaggio
 *                      numeri interi (anche potenzialmente negativi)
 *                          bonus o malus
 *
 *  ogni personaggi può fare uso degli oggetti disponibili nell'inventario e comporre liberatamente il proprio equipaggio, fino al massimo di 8 elementi
 *
 *  struttura dati come in figura
 *
 *  fare attenzione all'uso di strutture wrapper per memorizzare le collezione
 *      per personaggi oggetti equipaggiamenti
 *
 * scrivere
 *      caricare in una lista l'elenco di personaggi
 *      caricare in un vettore di strutture
 *          allocato dinamicamente
 *          l'eneco di oggetti
 *      aggiungere un nuovo personaggio
 *      eliminare un personaggio
 *      aggiugnere o rimuovere un oggetto dall'equipaggiamento di un personaggio
 *      calcolare le statitistiche di un personaggio tenendo in considerazione i suoi parametri base e l'equipaggimaneto corrente
 *          se una statitistica risultasse inferiore a 0 in seguito ad applicazione di malus si stampi 0
 *
 * organizzare codice in piu moduli
 *      modulo client per contentere il main e l'interfaccia utente menu
 *      modulo per la gestione dei personaggi
 *      modulo per la gestione dell'inventariato
 *
 * modulo per i personaggi deve fornire le funzionalità di
 *      acquisizione da file delle informazioni dei personaggi
 *          mantenendo la medesima struttura richiesta nel LAB 4
 *      inserimento e cancellazione di un personaggio
 *      ricerca per codice di un personaggio
 *      stampa dei dettagli di un personaggio e del relativo equipaggiamento se presente
 *      modifica dell'equipaggiamento di un personagigo
 *          aggiunta e rimozione di un oggetto
 *
 *      modulo dell'inventario deve fornire le funzionalità di
 *          acquisizione da file delle informaizoni relative agli oggetti disponibili
 *              mantenendo la medesima struttura a vettore richiesta nel laboratorio4
 *          ricerca di un oggetto per nome
 *          stampa dei dettagli di un oggetto
 *
 *      NB il modulo personaggi è client del modulo inventario in quanto ogni personaggio ha una collezione di riferimenti a dati contenuti nell'inventario
 *
 *
 *
 */

#include <stdio.h>
#include "personaggi.h"
#define MAXN 50

/*typedef enum{
    hp,mp,atk,def,mag,spr
} stat;*/

int main(void){
    linkP headP=NULL;
    linkO headO=NULL;
    int c=4;
    int b=5;
    int a=21;
    listInsHeadP(&headP,c);
    listDisplayP(headP);
    listInsHeadP(&headP,b);
    listDisplayP(headP);
    listInsHeadO(&headO,a);
    listDisplayO(headO);
    return 0;
}
