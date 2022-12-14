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
#include <string.h>
#include "personaggi.h"

#define MAXL 50
typedef enum comando{
    r_leffiilepersonaggio,
    r_aggiungipersonaggio,
    r_eliminapersonaggio,
    r_ricercacodicepersonaggio,
    r_leggifileinventario,
    r_stampadettaglioggetto,
    r_ricercanomeoggetto,
    r_aggiungiequipaggiamento,
    r_rimuoviequipaggiamento,
    r_calcolostat,
    r_stampadettaglipersonaggio,
    r_fine
} comando_e;

void menuparola();
comando_e leggicomando(void);

int main(void){
    menuparola();
    return 0;
}

void menuparola(void){
    comando_e codicecomando;
    int continua=1;
    tabPg *tabp;
    int indexsearchname;
    tabInv_t *tabi=NULL;
    tabp=allocazioneinizialepersonaggio();

    while(continua){
        codicecomando=leggicomando();
        //fflush(stdin);
        //scanf("%s",riga);//resto della riga

        switch (codicecomando){
            case r_leffiilepersonaggio:
                tabp=leggifilepersonaggi(tabp);
                break;
            case r_aggiungipersonaggio:
                tabp= leggitastierapersonaggio(tabp);
                break;
            case r_eliminapersonaggio:
                eliminapersonaggio(tabp);
                break;
            case r_ricercacodicepersonaggio:
                ricercacodicepersonaggio(tabp);
                break;
            case r_leggifileinventario:
                tabi=leggifileinventario();
                break;
            case r_stampadettaglioggetto:
                if(tabi==NULL) printf("inventario vuoto\n");
                else stampainventario(tabi);
                break;
            case r_ricercanomeoggetto:
                indexsearchname=ricercanomeoggetto(tabi);
                stampaoggettotrovato(tabi,indexsearchname);
                break;
            case r_aggiungiequipaggiamento:
                if(tabp!=NULL && tabi!=NULL){
                    tabp=aggiungereequipaggiamento(tabp,tabi);
                }else{
                    printf("Devi caricare prima la lista dei personaggi e l'inventario\n");
                }
                break;
            case r_rimuoviequipaggiamento:
                if(tabp!=NULL && tabi!=NULL){
                    tabp=rimuovereequipaggiamento(tabp,tabi);
                }else{
                    printf("Devi caricare prima la lista dei personaggi e l'inventario\n");
                }
                break;
            case r_calcolostat:
                calcolostat(tabp);
                break;
            case r_stampadettaglipersonaggio:
                stampapersonaggi(tabp);
                break;
            case r_fine:
                //aggiungere le free
                freeTabella(tabp);
                printf("fine\n");
                continua=0;
                break;
            default:
                printf("comando errato\n");
        }
    }
}

comando_e leggicomando(void){
    comando_e c;
    char cmd[MAXL];
    char *tabella[r_fine+1]={
            "0","1","2","3","4","5","6","7","8","9","10"
    };
    printf("Inserisci comando\n"
           "0 per inserire personaggi da file\n"
           "1 per aggiungere un personaggio\n"
           "2 per eliminare un personaggio\n"
           "3 per ricerca codice personaggio\n"
           "4 per inserire inventario da file\n"
           "5 per stampare dettagli oggetto\n"
           "6 per ricercare oggetto per nome\n"
           "7 per aggiungere oggetto nell'equipaggiamento di un personaggio\n"
           "8 per rimuovere oggetto nell'equipaggiamento di un personaggio\n"
           "9 per calcolare le stat di un personaggio\n"
           "10 per stampare personaggio\n");
    fflush(stdin);
    scanf("%s",cmd);
    c=r_leffiilepersonaggio;
    while(c<r_fine && strcmp(cmd,tabella[c])!=0) c++;
    return c;
}
