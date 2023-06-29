#include <stdio.h>
#include <stdlib.h>
#include "prodotti.h"
#include "categorie.h"

typedef enum{ins_prod, cerca_prod_code, cerca_prod_code_cat, stampa_prod_cat, cerca_prod_nome, check_ord, fine}Comando;

Comando leggiComando();
Comando fromStringToEnum(char *comando);
Boolean checkOrder(Prodotti pr, Categorie c, FILE *f, float *prize);

int main()
{
    Categorie c;
    Prodotti p, ricerca;
    Comando comando_e;
    char codeProdotto[MAXC], nomeProdotto[MAX], categoria[MAXC], ordinamento[MAXC];
    float prezzo;
    int disponibilita;
    Categoria *ca;
    Prodotto *pr;
    FILE *f;


    c=CATEGORIEinit();
    p=PRODOTTIinit();

    do{
       comando_e=leggiComando();
       switch(comando_e){
           case ins_prod:
               printf("\nInserisci il codice del prodotto: ");
               gets(codeProdotto);
               pr=PRODOTTIsearch(p, codeProdotto);
               if(pr==NULL){
                    printf("Inserisci il nome del prodotto: ");
                    gets(nomeProdotto);
                    printf("Inserisci la categoria del prodotto: ");
                    gets(categoria);
                    printf("Inserisci la disponibilita': ");
                    scanf("%d%*c", &disponibilita);
                    printf("Inserisci Il prezzo: ");
                    scanf("%f%*c", &prezzo);
                    PRODOTTIinsert(p, PRODOTTOcrea(codeProdotto, nomeProdotto, categoria, prezzo, disponibilita));
                    ca=CATEGORIEsearch(c, categoria);
                    if(ca==NULL){
                        CATEGORIEinsert(c, CATEGORIAcrea(categoria));
                        ca=CATEGORIEsearch(c, categoria);
                        CATEGORIAinsertProdotto(ca, PRODOTTOcrea(codeProdotto, nomeProdotto, categoria, prezzo, disponibilita));
                    }
                    else{
                       CATEGORIAinsertProdotto(ca, PRODOTTOcrea(codeProdotto, nomeProdotto, categoria, prezzo, disponibilita));
                    }
               }
               else{
                    printf("Inserisci la quantita': ");
                    scanf("%d%*c", &disponibilita);
                    PRODOTTOsetDisponibilita(pr, (pr->disponibilita+disponibilita));
               }
               break;


           case cerca_prod_code:
               if(PRODOTTIgetSize(p)==0){
                    printf("\nIl catalogo e' vuoto.\n");
                    break;
               }
               printf("\nInserisci il codice del prodotto: ");
               gets(codeProdotto);
               pr=PRODOTTIsearch(p, codeProdotto);
               if(pr==NULL){
                    printf("\nIl prodotto %s non e' presente nel catalogo.\n", codeProdotto);
               }
               else{
                    printf("\nIl prodotto cercato e': ");
                    PRODOTTOprint(*pr, stdout);
               }
               break;


           case cerca_prod_code_cat:
               if(PRODOTTIgetSize(p)==0){
                    printf("\nIl catalogo e' vuoto.\n");
                    break;
               }
               printf("\nInserisci il codice del prodotto: ");
               gets(codeProdotto);
               printf("Inserisci la categoria: ");
               gets(categoria);
               ca=CATEGORIEsearch(c, categoria);
               if(ca==NULL){
                    printf("\nLa categoria %s non esiste.\n", categoria);
               }
               else{
                    pr=CATEGORIAsearchProdotto(*ca, codeProdotto);
                    if(pr==NULL){
                        printf("\nIl prodotto %s non appartiene alla categoria %s.\n", codeProdotto, categoria);
                    }
                    else{
                        printf("\nIl prodotto cercato e': ");
                        PRODOTTOprint(*pr, stdout);
                    }
               }
               break;


           case stampa_prod_cat:
               if(PRODOTTIgetSize(p)==0){
                    printf("\nIl catalogo e' vuoto.\n");
                    break;
               }
               printf("\nInserisci la categoria: ");
               gets(categoria);
               ca=CATEGORIEsearch(c, categoria);
               if(ca==NULL){
                    printf("\nLa categoria %s non esiste.\n", categoria);
               }
               else{
                   printf("\nDigita:\n");
                   printf("1) 'nome' se vuoi che i prodotti siano stampati ordinati per nome;\n");
                   printf("2) 'codice' se vuoi che i prodotti siano stampati ordinati per codice.\n");
                   printf("Come vuoi ordinare i prodotti? ");
                   gets(ordinamento);
                   printf("\nI prodotti della categoria %s sono:\n", categoria);
                   CATEGORIAstampaProdotti(*ca, ordinamento, stdout);
               }
               break;


           case cerca_prod_nome:
               if(PRODOTTIgetSize(p)==0){
                    printf("\nIl catalogo e' vuoto.\n");
                    break;
               }
               printf("\nInserisci il nome del prodotto: ");
               gets(nomeProdotto);
               ricerca=PRODOTTIsearchByName(p, nomeProdotto);
               if(PRODOTTIgetSize(ricerca)==0){
                  printf("\nNon esiste alcun prodotto avente nome %s.\n", nomeProdotto);
               }
               else{
                   printf("\nI prodotti avente nome %s sono:\n", nomeProdotto);
                   PRODOTTIprint(ricerca, stdout);
               }
               PRODOTTIfree(ricerca);
               break;


           case check_ord:
               if(PRODOTTIgetSize(p)==0){
                    printf("\nIl catalogo e' vuoto.\n");
                    break;
               }
               f=fopen("ordine.txt", "r");
               if(f==NULL) exit(EXIT_FAILURE);
               if(checkOrder(p, c, f, &prezzo)==VERO){
                    printf("\nL'ordine è eseguibile. Il prezzo totale e': %.2f\n", prezzo);
               }
               else{
                    printf("\nImpossibile eseguire l'ordine.\n");
               }
               fclose(f);
               break;


           case fine:
               printf("\nProgramma terminato.\n");
               break;


           default:
               printf("\nComando errato. Reinseriscilo.\n");

       }
       printf("\n");
    }while(comando_e!=fine);

    return 0;
}




Comando leggiComando(){
    char comando[MAX];
    int i;
    char *menu[7]={"'ins_prod' per inserire un nuovo prodotto o aggiungere unita' disponibili per un prodotto gia' esistente;",
                   "'cerca_prod_code' per cercare un prodotto nel catalogo dato il codice;",
                   "'cerca_prod_code_cat' per cercare un prodotto nel catalogo dato il codice e la categoria;",
                   "'stampa_prod_cat' per stampare i prodotti di una data categoria;",
                   "'cerca_prod_nome' per cercare un prodotto dato il nome;",
                   "'check_ord' per calutare la soddisfacibilita' di un ordine;",
                   "'fine' per terminare."};

    printf("Scrivi:\n");
    for(i=0; i<7; i++){
        printf("%d) %s\n", i+1, menu[i]);
    }
    printf("\nChe cosa vuoi fare? ");
    gets(comando);
    return fromStringToEnum(comando);
}




Comando fromStringToEnum(char *comando){
    if(strcmp(comando, "ins_prod")==0)
        return ins_prod;
    if(strcmp(comando, "cerca_prod_code")==0)
        return cerca_prod_code;
    if(strcmp(comando, "cerca_prod_code_cat")==0)
        return cerca_prod_code_cat;
    if(strcmp(comando, "stampa_prod_cat")==0)
        return stampa_prod_cat;
    if(strcmp(comando, "cerca_prod_nome")==0)
        return cerca_prod_nome;
    if(strcmp(comando, "check_ord")==0)
        return check_ord;
    if(strcmp(comando, "fine")==0)
        return fine;
    return -1;
}




Boolean checkOrder(Prodotti pr, Categorie c, FILE *f, float *prize){
   char codice[MAX];
   int quantita, N, i;
   Prodotto *p, *ordine;
   Categoria *ca;
   (*prize)=0;
   fscanf(f, "%d", &N);
   ordine=(Prodotto*)malloc(N*sizeof(Prodotto));
   if(ordine==NULL) exit(EXIT_FAILURE);
   for(i=0; i<N; i++){
      fscanf(f, "%s %d", codice, &quantita);
      p=PRODOTTIsearch(pr, codice);
      if(p==NULL)
         return FALSO;
      if(p->disponibilita<quantita)
         return FALSO;
      (*prize)= (p->prezzo*quantita) + (*prize);
      ordine[i]=PRODOTTOcrea(codice, p->nome, p->categoria, p->prezzo, quantita);
   }
   for(i=0; i<N; i++){
      p=PRODOTTIsearch(pr, ordine[i].id);
      PRODOTTOsetDisponibilita(p, (p->disponibilita-ordine[i].disponibilita));
      ca=CATEGORIEsearch(c, p->categoria);
      p=CATEGORIAsearchProdotto(*ca, p->id);
      PRODOTTOsetDisponibilita(p, (p->disponibilita-ordine[i].disponibilita));
   }
   return VERO;
}
