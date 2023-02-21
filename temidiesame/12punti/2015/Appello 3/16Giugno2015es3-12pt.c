#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 30

//scusate i nomi mezzi inglesi e mezzi italiani...

struct node_prodotto{
    char *nome_prodotto;
    float prezzo;
    struct node_prodotto *next;
};

struct node_produttore{
    char *nome_produttore;
    struct node_produttore *next;
    struct node_prodotto *prodotti;
};

struct node_prodotto *createNewProduct(char *nome, float prezzo, struct node_prodotto *next);
struct node_produttore *createNewProducer(char *nome, struct node_produttore *next, struct node_prodotto *prodotto_head);
struct node_produttore *initializeListOflists();
void searchProduct(char *nomeProdotto, char *nomeProduttore, struct node_prodotto *prodotto, struct node_produttore *produttore);
void searchProdutcWrapper(char *nomeProdotto, char *nomeProduttore, struct node_produttore *produttore);

int main()
{
    struct node_produttore *head;
    char nomeProdotto[N], nomeProduttore[N];

    head = initializeListOflists();

    printf("Inserisci nome del prodotto: ");
    scanf("%s", nomeProdotto);
    printf("Inserisci nome del produttore: ");
    scanf("%s", nomeProduttore);

    searchProdutcWrapper(nomeProdotto, nomeProduttore, head);

    return 0;
}

struct node_prodotto *createNewProduct(char *nome, float prezzo, struct node_prodotto *next){
    struct node_prodotto *newProduct;

    newProduct = malloc(sizeof(*newProduct));

    newProduct->nome_prodotto = strdup(nome);
    newProduct->prezzo = prezzo;
    newProduct->next = next;

    return newProduct;
};

struct node_produttore *createNewProducer(char *nome, struct node_produttore *next, struct node_prodotto *prodotto_head){
    struct node_produttore *newProducer;

    newProducer = malloc(sizeof(*newProducer));

    newProducer->nome_produttore = strdup(nome);
    newProducer->next = next;
    newProducer->prodotti = prodotto_head;

    return newProducer;
};

/*struttura:

         HEAD
          |
          V
   || PRODUTTORE1 || -> | prodotto1 - 10.50 | -> | prodotto3 - 89.99 | -> | prodotto4 25.50 | -> NULL
          |
          V
   || PRODUTTORE2 || -> | prodotto0 - 30.56 | -> | prodotto3 - 91.30 | -> | prodotto5 103.60 | -> NULL
          |
          V
   || PRODUTTORE3 || -> | prodotto1 - 10.02 | -> | prodotto2 - 1.98 | -> | prodotto4 26.74 | -> NULL
          |
          V
         NULL
*/

struct node_produttore *initializeListOflists(){
    struct node_produttore *produttore1, *produttore2, *produttore3;
    struct node_prodotto *listaProdotti1_prodotto1, *listaProdotti1_prodotto2, *listaProdotti1_prodotto3;
    struct node_prodotto *listaProdotti2_prodotto1, *listaProdotti2_prodotto2, *listaProdotti2_prodotto3;
    struct node_prodotto *listaProdotti3_prodotto1, *listaProdotti3_prodotto2, *listaProdotti3_prodotto3;

    //AIUTO

    listaProdotti1_prodotto3 = createNewProduct("prodotto4", 25.50, NULL);
    listaProdotti1_prodotto2 = createNewProduct("prodotto3", 89.99, listaProdotti1_prodotto3);
    listaProdotti1_prodotto1 = createNewProduct("prodotto1", 10.50, listaProdotti1_prodotto2);

    listaProdotti2_prodotto3 = createNewProduct("prodotto5", 103.60, NULL);
    listaProdotti2_prodotto2 = createNewProduct("prodotto3", 91.30, listaProdotti2_prodotto3);
    listaProdotti2_prodotto1 = createNewProduct("prodotto0", 30.56, listaProdotti2_prodotto2);

    listaProdotti3_prodotto3 = createNewProduct("prodotto4", 26.74, NULL);
    listaProdotti3_prodotto2 = createNewProduct("prodotto2", 1.98, listaProdotti3_prodotto3);
    listaProdotti3_prodotto1 = createNewProduct("prodotto1", 10.02, listaProdotti3_prodotto2);

    produttore3 = createNewProducer("produttore3", NULL, listaProdotti3_prodotto1);
    produttore2 = createNewProducer("produttore2", produttore3, listaProdotti2_prodotto1);
    produttore1 = createNewProducer("produttore1", produttore2, listaProdotti1_prodotto1);

    return produttore1;
};

void searchProdutcWrapper(char *nomeProdotto, char *nomeProduttore, struct node_produttore *produttore){
    searchProduct(nomeProdotto, nomeProduttore, produttore->prodotti, produttore);
    return;
}

void searchProduct(char *nomeProdotto, char *nomeProduttore, struct node_prodotto *prodotto, struct node_produttore *produttore){
    if(prodotto == NULL){
        printf("Spiacenti, il prodotto specificato non esiste.\n");
        return;
    }

    if((strcmp(prodotto->nome_prodotto, nomeProdotto)==0) && (strcmp(produttore->nome_produttore, nomeProduttore)==0)){
        printf("Il prezzo del prodotto specificato e': %.2f\n", prodotto->prezzo);
        return;
    }

    if(strcmp(produttore->nome_produttore, nomeProduttore)!=0){
        if(produttore->next != NULL){
            searchProduct(nomeProdotto,nomeProduttore,produttore->next->prodotti,produttore->next);
        } else {
            printf("Spiacenti, il produttore specificato non esiste.\n");
            return;
        }
    } else {

        if(strcmp(prodotto->nome_prodotto, nomeProdotto)!=0){
            searchProduct(nomeProdotto,nomeProduttore,prodotto->next,produttore);
        }
    }

    return;
}
