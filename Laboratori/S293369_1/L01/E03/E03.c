/*
 //aggiungere maiuscola e minuscola indifferente
 */
#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAXN 30
#define maxrighe 1000
#define filename "corse.txt"

typedef enum comando {r_stampa, r_ordina_data, r_ordina_tratta, r_ordina_partenza, r_ordina_arrivo, r_cerca, r_fine, r_err}comando_e;

struct tratte {
    char codicetratta[MAXN];
    char partenza[MAXN];
    char destinazione[MAXN];
    char data[MAXN];
    char orapartenza[MAXN];
    char oraarrivo[MAXN];
    int ritardo;
};

comando_e leggicomando(void);
void strtolower(char s[]);
void menuparola(struct tratte tratta[],struct tratte *trattaptr[][maxrighe],int dim);
void ordinatratta(struct tratte *trattaptr[maxrighe],int dim);
void ordinapartenza(struct tratte *trattaptr[maxrighe],int dim);
void ordinaarrivo(struct tratte *trattaptr[maxrighe],int dim);



int main(){
    FILE *fpin;
    struct tratte tratta[maxrighe],*trattaptr[r_cerca][maxrighe];//ogni riga è un vettore di puntatori con lunghezza maxrighe
    int i,j,dim;
    fpin=fopen(filename,"r");
    if(fpin!=NULL){
        fscanf(fpin,"%d",&dim);
        i=0;
        while(!feof(fpin)){
                fscanf(fpin,"%s %s %s %s %s %s %d",tratta[i].codicetratta,tratta[i].partenza,tratta[i].destinazione,tratta[i].data,tratta[i].orapartenza,tratta[i].oraarrivo,&tratta[i].ritardo);
                i++;
            }
        //creo vettori di puntatori
        for(j=0;j<dim;j++) trattaptr[0][j]=trattaptr[1][j]=trattaptr[2][j]=trattaptr[3][j]=trattaptr[4][j]=trattaptr[5][j]=&tratta[j];
        menuparola(tratta,trattaptr,dim);
    }
    fclose(fpin);
    return 0;
}

void menuparola(struct tratte tratta[],struct tratte *trattaptr[][maxrighe],int dim){
    comando_e codicecomando;
    //char riga[MAXN];
    int continua=1;

    while(continua){
        codicecomando=leggicomando();
        //fflush(stdin);
        //scanf("%s",riga);//resto della riga

        switch (codicecomando){
            case r_stampa:
                //date(tratta,dim);
                break;
            case r_ordina_data:
                //partenza(tratta,dim);
                break;
            case r_ordina_tratta:
                ordinatratta(trattaptr[2],dim);
                break;
            case r_ordina_partenza:
                ordinapartenza(trattaptr[3],dim);
                break;
            case r_ordina_arrivo:
                ordinaarrivo(trattaptr[4],dim);
                break;
            case r_cerca:
                //function
                break;
            case r_fine:
                printf("fine\n");
                continua=0;
                break;
            default:
                printf("comando errato");
        }
    }
}

comando_e leggicomando(void){
    comando_e c;
    char cmd[MAXN];
    char *tabella[7]={
            "stampa", "ordina_data", "ordina_tratta", "ordina_partenza", "ordina_arrivo", "cerca", "fine"
    };
    printf("Comando (stampa/ordina_data/ordina_tratta/ordina_partenza/ordina_arrivo/cerca): ");
    fflush(stdin);
    scanf("%s",cmd);
    strtolower(cmd);
    c=r_stampa;
    while(c<r_fine && strcmp(cmd,tabella[c])!=0){
        c++;
    }
    return c;
}

void strtolower(char s[]){
    int i;
    for(i=0;s[i]!='\0';i++){
        s[i]=tolower(s[i]);
    }
}

void ordinatratta(struct tratte *trattaptr[maxrighe],int dim){
    struct tratte *tmp;
    int i,j;
    //printf("%s ",trattaptr[0]->codicetratta);


    //ordinamento in ordine alfabetico, inserction sort
    for(i=1;i<dim;i++){
        tmp=trattaptr[i];
        j=i-1;
        while(j>=0 && strcmp(tmp->codicetratta,trattaptr[j]->codicetratta)<0){
            trattaptr[j+1]=trattaptr[j];
            j--;
        }
        trattaptr[j+1]=tmp;
    }
    
    //stampa
    for(i=0;i<dim;i++){
        printf("%s %s %s %s %s %s %d",trattaptr[i]->codicetratta,trattaptr[i]->partenza,trattaptr[i]->destinazione,trattaptr[i]->data,trattaptr[i]->orapartenza,trattaptr[i]->oraarrivo,trattaptr[i]->ritardo);
        printf("\n");
    }
}

void ordinapartenza(struct tratte *trattaptr[maxrighe],int dim){
    struct tratte *tmp;
    int i,j;
    //printf("%s ",trattaptr[0]->codicetratta);
    //ordinamento in ordine alfabetico, inserction sort, scambio puntatori
    for(i=1;i<dim;i++){
        tmp=trattaptr[i];
        j=i-1;
        while(j>=0 && strcmp(tmp->partenza,trattaptr[j]->partenza)<0){
            trattaptr[j+1]=trattaptr[j];
            j--;
        }
        trattaptr[j+1]=tmp;
    }
    
    //stampa
    for(i=0;i<dim;i++){
        printf("%s %s %s %s %s %s %d",trattaptr[i]->codicetratta,trattaptr[i]->partenza,trattaptr[i]->destinazione,trattaptr[i]->data,trattaptr[i]->orapartenza,trattaptr[i]->oraarrivo,trattaptr[i]->ritardo);
        printf("\n");
    }
}

void ordinaarrivo(struct tratte *trattaptr[maxrighe],int dim){
    struct tratte *tmp;
    int i,j;
    //printf("%s ",trattaptr[0]->codicetratta);


    //ordinamento in ordine alfabetico, inserction sort
    for(i=1;i<dim;i++){
        tmp=trattaptr[i];
        j=i-1;
        while(j>=0 && strcmp(tmp->destinazione,trattaptr[j]->destinazione)<0){
            trattaptr[j+1]=trattaptr[j];
            j--;
        }
        trattaptr[j+1]=tmp;
    }
    
    //stampa
    for(i=0;i<dim;i++){
        printf("%s %s %s %s %s %s %d",trattaptr[i]->codicetratta,trattaptr[i]->partenza,trattaptr[i]->destinazione,trattaptr[i]->data,trattaptr[i]->orapartenza,trattaptr[i]->oraarrivo,trattaptr[i]->ritardo);
        printf("\n");
    }
}
