#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define maxLength 50

/*
 * Definizione della lista di anagrafiche
 *
 * code = codice univoco (AXXXX)
 * name = nome di massimo maxLength caratteri
 * surname = cognome di massimo maxLength caratteri
 * birth_date = data di nascita (GG/MM/AAAA)
 * st = via di massimo maxLength caratteri
 * city = città di massimo maxLength caratteri
 * cap = CAP come intero
 */
typedef struct node node_t, *link;

struct node {
    char code[6];
    char name[maxLength];
    char surname[maxLength];
    char birth_date[11];
    char st[maxLength];
    char city[maxLength];
    int cap;
    link next;
};

/*
 * Definizione delle scelte
 * 
 * end_prog = termina il programma
 * ins_keyboard = inserisci nella lista da tastiera
 * ins_file = importa nella lista da file
 * src_code = ricerca nella lista con il codice
 * extr_code = estrai dalla lista con il codice
 * extr_date = estrai dalla lista con un intervallo di date
 * prnt_list = stampa la lista
 */
typedef enum {
    end_prog = 1,
    ins_keyboard,
    ins_file,
    src_code,
    extr_code,
    extr_date,
    prnt_list
} tipo_scelta;

/*
 * Ottiene il formato "YYYY/MM/DD" della data dai valori interi
 * 
 * g = giorno
 * m = mese
 * y = anno
 * 
 * Ritorna la data ottenuta
 */
char* obtain_date(int g, int m, int y) {
    char* birth_date = (char*)malloc(11*sizeof(char));
    if (m < 10)
        if (g < 10)
            snprintf(birth_date, 11, "%d/0%d/0%d", y, m, g);
        else
            snprintf(birth_date, 11, "%d/0%d/%d", y, m, g);
    else
        if (g < 10)
            snprintf(birth_date, 11, "%d/%d/0%d", y, m, g);
        else
            snprintf(birth_date, 11, "%d/%d/%d", y, m, g);
    
    return birth_date;
}

/*
 * Crea un nodo della lista
 * 
 * code = codice
 * name = nome
 * surname = cognome
 * g = giorno della data di nascita
 * m = mese della data di nascita
 * y = anno della data di nascita
 * st = via
 * city = città
 * cap = CAP
 * 
 * Ritorna il nodo creato
 */
link create_node(char* code, char* name, char* surname, int g, int m, int y, char* st, char* city, int cap) {
    link newNode = (link)malloc(sizeof(node_t));
    
    strcpy(newNode->code, code);
    strcpy(newNode->name, name);
    strcpy(newNode->surname, surname);
    
    char* birth_date = obtain_date(g, m, y);
    strcpy(newNode->birth_date, birth_date);
    free(birth_date);

    strcpy(newNode->st, st);
    strcpy(newNode->city, city);
    newNode->cap = cap;
    newNode->next = NULL;
    return newNode;
}

/*
 * Inserisce un nodo in una lista
 * 
 * head = inizio della lista
 * node = nodo da inserire
 * 
 * Ritorna il primo elemento alla lista aggiornata
 */
link insert_node(link head, link node) {
    link x;
    if(head == NULL)
        head = node;
    else if(strcmp(head->birth_date, node->birth_date) < 0) {
        node->next = head;
        head = node;
    } else {
        for(x = head;
            x->next != NULL && strcmp(x->next->birth_date, node->birth_date) > 0;
            x = x->next);
        node->next = x->next;
        x->next = node;
    }
    return head;
}

/*
 * Stampa un nodo
 *
 * node = nodo da stampare
 */
void print_node(link node) {
    printf( "Codice: %s\n"
            "Nome: %s\n"
            "Cognome: %s\n"
            "Data di nascita: %s\n"
            "Via: %s\n"
            "Citta': %s\n"
            "CAP: %d\n",
            node->code, node->name, node->surname, node->birth_date, node->st, node->city, node->cap);
}

/*
 * Libera la memoria occupata dal nodo
 *
 * node = nodo da liberare
 */
void free_node(link node) {
    free(node);
}

/*
 * Stampa la lista
 *
 * head = inizio della lista
 */
void print_list(link head) {
    if(head == NULL) {
        printf("La lista e' vuota.\n");
        return;
    }

    link x;
    int i;
    for(x = head, i = 1; x != NULL; x = x->next, i++) {
        printf("ANAGRAFICA %d: \n", i);
        print_node(x);
        printf("\n");
    }
}

/*
 * Libera la memoria occupata dalla lista 
 *
 * head = inizio della lista
 */
void free_list(link head) {
    link to_free;
    while(head != NULL) {
        to_free = head;
        head = head->next;
        free_node(to_free);
    }
}

/*
 * Controlla che il codice abbia il formato corretto (AXXXX)
 * 
 * code = codice da controllare
 * 
 * Ritorna 0 se non è corretto, 1 se è corretto
 */
int check_code(char* code) {
    int i;
    if(code[0] == 'A') {
        for(i = 1; code[i] != '\0'; i++)
            if(code[i] < '0' || code[i] > '9' || i > 4)
                return 0;
    }
    if(i != 5)
        return 0;
    return 1;
}

/*
 * Ricerca un nodo tramite un codice
 *
 * head = inizio della lista
 * code = codice da ricercare
 * 
 * Ritorna il nodo se trovato, NULL altrimenti
 */
link search_code(link head, char* code) {
    for(link x = head; x != NULL; x = x->next) {
        if (strcmp(x->code, code) == 0) {
            return x;
        }
    }
    return NULL;
}

/*
 * Importa nodi nella lista da tastiera
 * 
 * head = inizio della lista
 * 
 * Ritorna la lista aggiornata
 */
link insert_from_keyboard(link head) {
    char code[6], name[maxLength], surname[maxLength], st[maxLength], city[maxLength];
    int cap, g, m, y, n;

    do {
        printf("Inserisci il numero di grafiche da inserire (n >= 0): \n");
        scanf("%d", &n);
    } while(n < 0);

    link node;
    for(int i = 0; i < n; i++) {
        link found;
        int check;
        do {
            printf("Inserisci il codice (AXXXX): \n");
            scanf("%s", code);
            if(!(check = check_code(code)) || (found = search_code(head, code)) != NULL)
                printf("Il valore inserito non e' valido oppure e' gia' presente nel database. \n");
        } while(!check || found != NULL);
        
        printf("Inserisci il nome: \n");
        scanf("%s", name);
        
        printf("Inserisci il cognome: \n");
        scanf("%s", surname);
        
        printf("Inserisci la data di nascita (GG/MM/AAAA): \n");
        scanf("%d/%d/%d", &g, &m, &y);
        
        printf("Inserisci la via: \n");
        scanf("%s", st);
        
        printf("Inserisci la citta': \n");
        scanf("%s", city);

        printf("Inserisci il CAP: \n");
        scanf("%d", &cap);
        
        node = create_node(code, name, surname, g, m, y, st, city, cap);
        head = insert_node(head, node);
    }
    return head;
}

/*
 * Importa nodi nella lista dal file
 * 
 * fileName = nome del file
 * head = inizio della lista
 * 
 * Ritorna la lista aggiornata
 */
link insert_from_file(char* fileName, link head) {
    FILE* file;
    char code[6], name[maxLength], surname[maxLength], st[maxLength], city[maxLength];
    int cap, g, m, y;

    if((file = fopen(fileName, "r")) == NULL) {
        printf("Non e' stato possibile aprire il file.\n");
        return head;
    }

    link node;
    while(!feof(file)) {
        fscanf(file,    "%s %s %s %d/%d/%d %s %s %d\n", 
                        code, name, surname, &g, &m, &y, st, city, &cap);
        if(!check_code(code) || search_code(head, code) != NULL) {
            printf("Il codice %s non e' valido oppure e' gia' presente nel database.\n", code);
        } else {
            node = create_node(code, name, surname, g, m, y, st, city, cap);
            head = insert_node(head, node);
        }
    }
    
    fclose(file);
    printf("File caricato con successo.\n");
    return head;
}

/*
 * Estrae un nodo dalla lista attraverso il codice
 * 
 * head = puntatore all'inizio della lista
 * code = codice da ricercare
 * 
 * Ritorna il nodo estratto
 */
link extract_by_code(link *head, char* code) {
    link x, extract = NULL, prev;
    for(x = *head; x != NULL; prev = x, x = x->next) {
        if(strcmp(x->code, code) == 0) {
            extract = x;
            if(x == *head) {
                *head = (*head)->next;
            } else {
                prev->next = prev->next->next;
            }
            extract->next = NULL;
        }
    }
    return extract;
}

/*
 * Estrae un nodo dalla lista attraverso un intervallo di date
 * 
 * head = puntatore all'inizio della lista
 * dateI = inizio dell'intervallo (la data più recente)
 * dateF = fine dell'intervallo (la data meno recente)
 * 
 * Ritorna il nodo estratto
 */
link extract_by_date(link *head, char* dateI, char* dateF) {
    
    if(strcmp(dateI, dateF) < 0) {
        char* dateSwap = (char*)malloc(11*sizeof(char));
        strcpy(dateSwap, dateI);
        strcpy(dateI, dateF);
        strcpy(dateF, dateSwap);
        free(dateSwap);
    }

    link x, extract = NULL, tmp = NULL, prev = *head;
    int flag = 0;

    for(x = *head; x != NULL; prev = x, x = x->next) {
        if(strcmp(x->birth_date, dateI) <= 0 && strcmp(x->birth_date, dateF) >= 0) {
            if(flag == 0) {
                if(x == *head) {
                    flag = 1;
                    extract = *head;
                } else {
                    tmp = prev;
                    flag = 2;
                    extract = x;
                }
            }
        } else if (flag != 0)
            break;
    }
    
    if(flag == 1)
        *head = prev->next;
    
    if(flag == 2)
        tmp->next = prev->next;
    
    prev->next = NULL;
    return extract;
}

int main() {
    link head = NULL, extracted;
    int scelta = 0;
    char code[6];
    do {
        printf(
                "1. Termina il programma; \n"
                "2. Inserisci delle anagrafiche da tastiera; \n"
                "3. Importa delle anagrafiche da file; \n"
                "4. Ricerca un'anagrafica attraverso il codice; \n"
                "5. Estrai un'anagrafica attraverso il codice; \n"
                "6. Estrai delle anagrafiche attraverso un intervallo di date di nascita; \n"
                "7. Stampa la lista delle anagrafiche con le relative informazioni. \n"
                "\nInserisci una scelta: "
                );
        scanf("%d", &scelta);
        switch(scelta) {
            case end_prog:
                free_list(head);
                printf("Terminando il programma...\n");
                break;

            case ins_keyboard:
                head = insert_from_keyboard(head);
                break;

            case ins_file:
                char fileName[maxLength];
                printf("Inserisci il nome del file da importare: ");
                scanf("%s", fileName);
                head = insert_from_file(fileName, head);
                break;

            case src_code:
                link found;
                printf("Inserisci il codice da ricercare (AXXXX): \n");
                scanf("%s", code);
                if(!check_code(code)) {
                    printf("Il valore inserito non e' valido. \n");
                    break;
                }
                if((found = search_code(head, code)) == NULL)
                    printf("Non e' stata trovata alcuna anagrafica con il codice %s.", code);
                else {
                    printf("E' stata trovata l'anagrafica: \n");
                    print_node(found);
                }
                break;

            case extr_code:
                printf("Inserisci il codice da ricercare (AXXXX): \n");
                scanf("%s", code);
                if(!check_code(code)) {
                    printf("Il valore inserito non e' valido. \n");
                    break;
                }
                if((extracted = extract_by_code(&head, code)) != NULL) {
                    printf("E' stata estratta l'anagrafica:\n");
                    print_node(extracted);
                    free_node(extracted);
                } else {
                    printf("Non e' stata trovata un'anagrafica con codice %s.", code);
                }
                break;

            case extr_date:
                int gI, mI, yI, gF, mF, yF;

                printf("Inserisci la data iniziale da cui ricercare (GG/MM/AAAA): ");
                scanf("%d/%d/%d", &gI, &mI, &yI);
                char* dateI = obtain_date(gI, mI, yI);
                
                printf("Inserisci la data finale da cui ricercare (GG/MM/AAAA): ");
                scanf("%d/%d/%d", &gF, &mF, &yF);
                char* dateF = obtain_date(gF, mF, yF);
                
                extracted = extract_by_date(&head, dateI, dateF);

                if(extracted != NULL) {
                    print_list(extracted);
                    free_list(extracted);
                } else {
                    printf("Non è stata trovata nessuna anagrafica in quell'intervallo di date.\n");
                }
                break;

            case prnt_list:
                print_list(head);
                break;

            default:
                printf("Il valore inserito non e' tra le scelte!\n");
        }
        printf("\n");
    } while(scelta != end_prog);
    return 0;
}