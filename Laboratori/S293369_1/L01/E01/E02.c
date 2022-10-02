/*
 //aggiungere maiuscola e minuscola indifferente
 */
#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAXN 30
#define maxrighe 1000

typedef enum comando {r_date, r_partenza, r_capolinea,
    r_ritardo, r_ritardo_tot, r_fine}comando_e;

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
void menuparola(struct tratte tratta[],int dim);
void date(struct tratte tratta[], int dim);
void partenza(struct tratte tratta[], int dim);
void capolinea(struct tratte tratta[], int dim);
void destinazioneritardo(struct tratte tratta[], int dim);
void ritardotot(struct tratte tratta[], int dim);

int main(){
    FILE *fpin;
    struct tratte tratta[maxrighe];
    int i,dim;
    fpin=fopen("corse.txt","r");
    if(fpin!=NULL){
        fscanf(fpin,"%d",&dim);
        i=0;
        while(!feof(fpin)){
                fscanf(fpin,"%s %s %s %s %s %s %d",tratta[i].codicetratta,tratta[i].partenza,tratta[i].destinazione,tratta[i].data,tratta[i].orapartenza,tratta[i].oraarrivo,&tratta[i].ritardo);
                i++;
            }
        menuparola(tratta,dim);
    }
    fclose(fpin);
    return 0;
}

void menuparola(struct tratte tratta[], int dim){
    comando_e codicecomando;
    //char riga[MAXN];
    int continua=1;

    while(continua){
        codicecomando=leggicomando();
        //fflush(stdin);
        //scanf("%s",riga);//resto della riga

        switch (codicecomando){
            case r_date:
                date(tratta,dim);
                break;
            case r_partenza:
                partenza(tratta,dim);
                break;
            case r_capolinea:
                capolinea(tratta,dim);
                break;
            case r_ritardo:
                destinazioneritardo(tratta,dim);
                break;
            case r_ritardo_tot:
                ritardotot(tratta,dim);
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
    char *tabella[r_fine]={
            "date","partenza","capolinea","ritardo","ritardo_tot"
    };
    printf("inserisci comando\n");
    fflush(stdin);
    scanf("%s",cmd);
    strtolower(cmd);
    c=r_date;
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

void date(struct tratte tratta[],int dim){
    int i;
    char datacheckstart[MAXN];
    char datacheckend[MAXN];
    fflush(stdin);
    printf("inserisci date\n");
    scanf("%s %s",datacheckstart,datacheckend);
    //scorro su tutta la struct e confronto le date delle corse con le date inserite dagli utenti verificando se sono contenute tra esse. Per il confronto posso usare strcmp in quanto basta capire "quale sia quella che viene prima in ordine alfabetico"
    for(i=0;i<dim;i++){
        if((strcmp(datacheckstart,tratta[i].data)<0) && (strcmp(datacheckend,tratta[i].data)>0)){
            printf("%s %s %s %s %s %s %d",tratta[i].codicetratta,tratta[i].partenza,tratta[i].destinazione,tratta[i].data,tratta[i].orapartenza,tratta[i].oraarrivo,tratta[i].ritardo);
            printf("\n");
        }
    }
}

void partenza(struct tratte tratta[], int dim){
    int i;
    char partenzacheck[MAXN];
    fflush(stdin);
    printf("inserisci partenza\n");
    scanf("%s",partenzacheck);
    for(i=0;i<dim;i++){
        if(strcmp(partenzacheck,tratta[i].partenza)==0){//aggiungere confronto maiuscola e minuscolo che sia indiferrente
            printf("%s %s %s %s %s %s %d",tratta[i].codicetratta,tratta[i].partenza,tratta[i].destinazione,tratta[i].data,tratta[i].orapartenza,tratta[i].oraarrivo,tratta[i].ritardo);
            printf("\n");
        }
    }
}

void capolinea(struct tratte tratta[], int dim){
    int i;
    char capolineacheck[MAXN];
    fflush(stdin);
    printf("inserisci capolinea\n");
    scanf("%s",capolineacheck);
    for(i=0;i<dim;i++){
        if(strcmp(capolineacheck,tratta[i].destinazione)==0){//aggiungere confronto maiuscola e minuscolo che sia indiferrente
            printf("%s %s %s %s %s %s %d",tratta[i].codicetratta,tratta[i].partenza,tratta[i].destinazione,tratta[i].data,tratta[i].orapartenza,tratta[i].oraarrivo,tratta[i].ritardo);
            printf("\n");
        }
    }
}

void destinazioneritardo(struct tratte tratta[],int dim){
    int i;
    char datacheckstart[MAXN];
    char datacheckend[MAXN];
    fflush(stdin);
    printf("inserisci date\n");
    scanf("%s %s",datacheckstart,datacheckend);
    for(i=0;i<dim;i++){
        if((strcmp(datacheckstart,tratta[i].data)<0) && (strcmp(datacheckend,tratta[i].data)>0)){
            if(tratta[i].ritardo>0){
                printf("%s %s %s %s %s %s %d",tratta[i].codicetratta,tratta[i].partenza,tratta[i].destinazione,tratta[i].data,tratta[i].orapartenza,tratta[i].oraarrivo,tratta[i].ritardo);
                printf("\n");
            }
        }
    }
}

void ritardotot(struct tratte tratta[],int dim){
    int i;
    int delay=0;
    char codicetratta_check[MAXN];
    fflush(stdin);
    printf("inserisci codice tratta\n");
    scanf("%s",codicetratta_check);
    for(i=0;i<dim;i++){
        if((strcmp(codicetratta_check,tratta[i].codicetratta)==0)){//aggiungere maiuscola e minuscola indifferente
            delay=delay+tratta[i].ritardo;
        }
    }
    printf("%s %d\n",codicetratta_check,delay);
}
