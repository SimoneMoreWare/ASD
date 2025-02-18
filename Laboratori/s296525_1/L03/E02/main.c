#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LENGTH 255+1
#define nomeFile "brani.txt"
int k = 1;

/*
 * Note: 
 * - il caso del Calcolo Combinatorio è del tipo moltiplicativo
 * - è stata utilizzata una lista di tipo FIFO
 */

/*
 * Nodo della lista contenente i brani
 *
 * brano = stringa contenente il brano
 * next = puntatore al prossimo nodo
 */
typedef struct node node, *link;

struct node {
    char brano[MAX_LENGTH];
    node *next;
};

/*
 * crea un nuovo nodo in testa alla lista
 *
 * string = valore del nodo da inserire
 * next = puntatore al nodo cui attaccare il nuovo nodo
 * 
 * ritorna il nodo creato se l'operazione ha avuto successo,
 * altrimenti ritorna NULL
 */
link newNode(char* string, link next);

/*
 * rimuove un elemento in testa alla lista
 *
 * h = puntatore alla testa della lista
 * 
 * ritorna il nuovo nodo della testa
 */
link listDelHead(link h);

/*
 * stampa una lista
 *
 * l = puntatore al primo elemento della lista da stampare
 */
void printList(link l);

/*
 * stampa tutte le combinazioni di playlist
 * 
 * l = vettore di puntatori al primo elemento delle liste
 * playlist = puntatore alla playlist da stampare se arrivati
 *            al caso di terminazione
 * A = quantità di elementi in l
 */
void printPlaylists(link* l, link playlist, int A);

int main() {
    FILE* file;
    if ((file = fopen(nomeFile, "r")) == NULL) {
        printf("Non e' stato possibile aprire il file.");
        return -1;
    } else if (feof(file)) {
        printf("Il file è vuoto.");
        return -1;
    }

    int A, C, i, j;
    char brano[MAX_LENGTH];
    fscanf(file, "%d", &A);
    
    link* proposte = (link*) malloc(A*sizeof(link));
    for(i = 0; i < A; i++) {
        proposte[i] = NULL;
        fscanf(file, "%d", &C);
        for(j = 0; j < C; j++) {
            fscanf(file, "%s", brano);
            proposte[i] = newNode(brano, proposte[i]);
        }
    }

    link playlist = NULL;
    printPlaylists(proposte, playlist, A);

    for(i = 0; i < A; i++) {
        while(proposte[i] != NULL) {
            listDelHead(proposte[i]);
        }
    }
    free(proposte);
    return 0;
}

link newNode(char* string, link next) {
    link x = (link) malloc(sizeof(node));
    if (x == NULL) {
        return NULL;
    }
    else {
        strcpy(x->brano, string);
        x->next = next;
    }
    return x;
}

link listDelHead(link h) {
    link t = h;
    if (h == NULL)
        return NULL;
    h = h->next;
    free(t);
    return h;
}

void printList(link l) {
    link x;
    for(x = l; x != NULL; x = x->next) {
        printf("Brano: %s\n", x->brano);
    }
}

void printPlaylists(link* l, link playlist, int A) {
    link x;
    if(A == 1) {
        for(x = l[0]; x != NULL; x = x->next) {
            playlist = newNode(x->brano, playlist);
            printf("Playlist %d: \n", k);
            printList(playlist);
            printf("\n");
            k++;
            playlist = listDelHead(playlist);
        }
        return;
    }

    for(x = l[0]; x != NULL; x = x->next) {
        playlist = newNode(x->brano, playlist);
        printPlaylists(l+1, playlist, A-1);
        playlist = listDelHead(playlist);
    }
    return;
}