/*
 //aggiungere maiuscola e minuscola indifferente
 */
#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAXN 30
#define maxrighe 1000
#define filename "../corse.txt"

typedef enum comando{
    r_stampa,
    r_ordina_data,
    r_ordina_tratta,
    r_ordina_partenza,
    r_ordina_arrivo,
    r_cerca,
    r_fine,
} comando_e;

struct tratte{
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
void menuparola(struct tratte tratta[], struct tratte *trattaptr[][maxrighe], int dim);
void stampa(struct tratte tratta[], int dim);
void ordinadata(struct tratte *trattaptr[maxrighe], int dim);
int datatoint(char *data,char *ora);
void ordinatratta(struct tratte *trattaptr[maxrighe], int dim);
void ordinapartenza(struct tratte *trattaptr[maxrighe], int dim);
void ordinaarrivo(struct tratte *trattaptr[maxrighe], int dim);
void ricercalineare(struct tratte tratta[],int dim);

int main()
{
    FILE *fpin;
    struct tratte tratta[maxrighe], *trattaptr[r_cerca][maxrighe];
    int i, j, dim;
    fpin = fopen(filename, "r");
    if (fpin != NULL)
    {
        fscanf(fpin, "%d", &dim);
        i = 0;
        while (!feof(fpin))
        {
            fscanf(fpin, "%s %s %s %s %s %s %d", tratta[i].codicetratta, tratta[i].partenza, tratta[i].destinazione, tratta[i].data, tratta[i].orapartenza, tratta[i].oraarrivo, &tratta[i].ritardo);
            i++;
        }
        for (j = 0; j < dim; j++)
            trattaptr[0][j] = trattaptr[1][j] = trattaptr[2][j] = trattaptr[3][j] = trattaptr[4][j] = &tratta[j];
        menuparola(tratta, trattaptr, dim);
    }
    fclose(fpin);
    return 0;
}

void menuparola(struct tratte tratta[], struct tratte *trattaptr[][maxrighe], int dim){
    comando_e codicecomando;
    // char riga[MAXN];
    int continua = 1;

    while (continua){
        codicecomando = leggicomando();
        // fflush(stdin);
        // scanf("%s",riga);//resto della riga

        switch (codicecomando){
            case r_stampa:
                stampa(tratta, dim);
                break;
            case r_ordina_data:
                ordinadata(trattaptr[0],dim);
                break;
            case r_ordina_tratta:
                ordinatratta(trattaptr[1], dim);
                break;
            case r_ordina_partenza:
                ordinapartenza(trattaptr[2], dim);
                break;
            case r_ordina_arrivo:
                ordinaarrivo(trattaptr[3], dim);
                break;
            case r_cerca:
                ricercalineare(tratta,dim);
                break;
            case r_fine:
                printf("fine\n");
                continua = 0;
                break;
            default:
                printf("comando errato");
        }
    }
}

comando_e leggicomando(void){
    comando_e c;
    char cmd[MAXN];
    char *tabella[7] = {"stampa", "ordina_data", "ordina_tratta", "ordina_partenza", "ordina_arrivo", "cerca", "fine"};
    printf("Comando (stampa/ordina_data/ordina_tratta/ordina_partenza/ordina_arrivo/cerca): ");
    fflush(stdin);
    scanf("%s", cmd);
    strtolower(cmd);
    c = r_stampa;
    while (c < r_fine && strcmp(cmd, tabella[c]) != 0){
        c++;
    }
    return c;
}

void strtolower(char s[])
{
    int i;
    for (i = 0; s[i] != '\0'; i++){
        s[i] = tolower(s[i]);
    }
}

void stampa(struct tratte tratta[], int dim){
    int i;
    for (i = 0; i < dim; i++){
        printf("%s %s %s %s %s %s %d", tratta[i].codicetratta, tratta[i].partenza, tratta[i].destinazione, tratta[i].data, tratta[i].orapartenza, tratta[i].oraarrivo, tratta[i].ritardo);
        printf("\n");
    }
}

void ordinadata(struct tratte *trattaptr[maxrighe], int dim){
    struct tratte *tmp;
    int i, j;
    // printf("%s ",trattaptr[0]->codicetratta);

    // ordinamento in ordine alfabetico, inserction sort
    for (i = 1; i < dim; i++){
        tmp = trattaptr[i];
        j = i - 1;
        while (j >= 0 && datatoint(tmp->data,tmp->orapartenza)<datatoint(trattaptr[j]->data,trattaptr[j]->orapartenza)){
            trattaptr[j + 1] = trattaptr[j];
            j--;
        }
        trattaptr[j + 1] = tmp;
    }

    // stampa
    for (i = 0; i < dim; i++){
        printf("%s %s %s %s %s %s %d", trattaptr[i]->codicetratta, trattaptr[i]->partenza, trattaptr[i]->destinazione, trattaptr[i]->data, trattaptr[i]->orapartenza, trattaptr[i]->oraarrivo, trattaptr[i]->ritardo);
        printf("\n");
    }
}

int datatoint(char *data,char *ora){
    int res;
    //trasformo tutto in secondi
    res=365*(1000*(int)(data[0]-'0')+100*(int)(data[1]-'0')+10*(int)(data[2]-'0')+(int)(data[3]-'0'));
    res=res+30*(10*(int)(data[5]-'0')+(int)(data[6]-'0'));
    res=res+(10*(int)(data[8]-'0')+(int)(data[9]-'0'));
    res=res*24*60*60;
    res=res+3600*(10*(int)(ora[0]-'0')+(int)(ora[1]-'0'));
    res=res+60*(10*(int)(ora[3]-'0')+(int)(ora[4]-'0'));
    res=res+(10*(int)(ora[6]-'0')+(int)(ora[7]-'0'));
    return res;
}

void ordinatratta(struct tratte *trattaptr[maxrighe], int dim){
    struct tratte *tmp;
    int i, j;
    // printf("%s ",trattaptr[0]->codicetratta);

    // ordinamento in ordine alfabetico, inserction sort
    for (i = 1; i < dim; i++){
        tmp = trattaptr[i];
        j = i - 1;
        while (j >= 0 && strcmp(tmp->codicetratta, trattaptr[j]->codicetratta) < 0){
            trattaptr[j + 1] = trattaptr[j];
            j--;
        }
        trattaptr[j + 1] = tmp;
    }

    // stampa
    for (i = 0; i < dim; i++){
        printf("%s %s %s %s %s %s %d", trattaptr[i]->codicetratta, trattaptr[i]->partenza, trattaptr[i]->destinazione, trattaptr[i]->data, trattaptr[i]->orapartenza, trattaptr[i]->oraarrivo, trattaptr[i]->ritardo);
        printf("\n");
    }
}

void ordinapartenza(struct tratte *trattaptr[maxrighe], int dim){
    struct tratte *tmp;
    int i, j;
    // printf("%s ",trattaptr[0]->codicetratta);

    // ordinamento in ordine alfabetico, inserction sort
    for (i = 1; i < dim; i++){
        tmp = trattaptr[i];
        j = i - 1;
        while (j >= 0 && strcmp(tmp->partenza, trattaptr[j]->partenza) < 0){
            trattaptr[j + 1] = trattaptr[j];
            j--;
        }
        trattaptr[j + 1] = tmp;
    }

    // stampa
    for (i = 0; i < dim; i++){
        printf("%s %s %s %s %s %s %d", trattaptr[i]->codicetratta, trattaptr[i]->partenza, trattaptr[i]->destinazione, trattaptr[i]->data, trattaptr[i]->orapartenza, trattaptr[i]->oraarrivo, trattaptr[i]->ritardo);
        printf("\n");
    }
}

void ordinaarrivo(struct tratte *trattaptr[maxrighe], int dim){
    struct tratte *tmp;
    int i, j;
    // printf("%s ",trattaptr[0]->codicetratta);

    // ordinamento in ordine alfabetico, inserction sort
    for (i = 1; i < dim; i++){
        tmp = trattaptr[i];
        j = i - 1;
        while (j >= 0 && strcmp(tmp->destinazione, trattaptr[j]->destinazione) < 0){
            trattaptr[j + 1] = trattaptr[j];
            j--;
        }
        trattaptr[j + 1] = tmp;
    }

    // stampa
    for (i = 0; i < dim; i++){
        printf("%s %s %s %s %s %s %d", trattaptr[i]->codicetratta, trattaptr[i]->partenza, trattaptr[i]->destinazione, trattaptr[i]->data, trattaptr[i]->orapartenza, trattaptr[i]->oraarrivo, trattaptr[i]->ritardo);
        printf("\n");
    }
}

void ricercalineare(struct tratte tratta[],int dim){
    int i;
    char partenzaprefix[MAXN];
    int lenprefix;
    fflush(stdin);
    printf("inserisci partenza\n");
    scanf("%s",partenzaprefix);
    lenprefix=(int)strlen(partenzaprefix);
    //scorro su tutta la struct e in seguito effettuo una strncmp (che permette di confrontare una "sottostringa" con la stringa in cui prendo gli n caratteri iniziali
    for(i=0;i<dim;i++){
        if(strncmp(partenzaprefix,tratta[i].partenza,lenprefix)==0){
            printf("%s %s %s %s %s %s %d",tratta[i].codicetratta,tratta[i].partenza,tratta[i].destinazione,tratta[i].data,tratta[i].orapartenza,tratta[i].oraarrivo,tratta[i].ritardo);
            printf("\n");
        }
    }
}
