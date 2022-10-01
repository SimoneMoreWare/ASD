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
void menuparola(struct tratte tratta[],int dim);
void strlower(char s[]);
void print_rides_in_range_date(struct tratte tratta[],int dim);
void print_rides_fromstop(struct tratte tratta[],int dim);
void print_rides_fromend(struct tratte tratta[],int dim);
void print_rides_in_range_date_delay(struct tratte tratta[],int dim);
void print_rides_id_totdelay(struct tratte tratta[],int dim);

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
    int continua=1;

    while(continua){
        codicecomando=leggicomando();
        //fflush(stdin);

        switch (codicecomando){
            case r_date:
                print_rides_in_range_date(tratta,dim);
                break;
            case r_partenza:
                print_rides_fromstop(tratta,dim);
                break;
            case r_capolinea:
                print_rides_fromend(tratta,dim);
                break;
            case r_ritardo:
                print_rides_in_range_date_delay(tratta,dim);
                break;
            case r_ritardo_tot:
                print_rides_id_totdelay(tratta,dim);
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

void print_rides_in_range_date(struct tratte tratta[], int dim){
    char date1[MAXN],date2[MAXN];
    int i;
    
    //input date
    fflush(stdin);
    printf("inserisci data 1 e data2\n");
    scanf("%s %s",date1,date2);
    
    //scorro su tutta la struct e confronto le date delle corse con le date inserite dagli utenti verificando se sono contenute tra esse. Per il confronto posso usare strcmp in quanto basta capire "quale sia quella che viene prima in ordine alfabetico"
    //problema nel confrontare date come 2017/12/01 - 2018/01/31 , possibile slz: https://stackoverflow.com/questions/37310050/date-comparison-in-c
    for(i=0;i<dim;i++){
    	if(strcmp(tratta[i].data,date1)>0 && strcmp(tratta[i].data,date2)<0){
    	    printf("\n%s %s %s %s %s\n",tratta[i].partenza,tratta[i].destinazione,tratta[i].data,tratta[i].orapartenza,tratta[i].oraarrivo);
    	}
    }
  
} 

void print_rides_fromstop(struct tratte tratta[],int dim){
    char namebusStop[MAXN];
    int i;
    
    //input
    fflush(stdin);
    printf("inserisci partenza\n");
    scanf("%s ",namebusStop);
    
    for(i=0;i<dim;i++){
        if(strcmp(tratta[i].partenza,namebusStop)==0){
            printf("%s %s %s %s %s\n",tratta[i].partenza,tratta[i].destinazione,tratta[i].data,tratta[i].orapartenza,tratta[i].oraarrivo);
        }
    }
    
}

void print_rides_fromend(struct tratte tratta[],int dim){
    char nameendStop[MAXN];
    int i;
    
    //input
    fflush(stdin);
    printf("inserisci capolinea\n");
    scanf("%s ",nameendStop);
    
    for(i=0;i<dim;i++){
        if(strcmp(tratta[i].destinazione,nameendStop)==0){
            printf("%s %s %s %s %s\n",tratta[i].partenza,tratta[i].destinazione,tratta[i].data,tratta[i].orapartenza,tratta[i].oraarrivo);
        }
    }
  
}

void print_rides_in_range_date_delay(struct tratte tratta[],int dim){
    char date1[MAXN],date2[MAXN];
    int i;
    
    //input date
    fflush(stdin);
    printf("inserisci data 1 e data2\n");
    scanf("%s %s",date1,date2);
    
    for(i=0;i<dim;i++){
    	if((strcmp(tratta[i].data,date1)>0 && strcmp(tratta[i].data,date2)<0) && tratta[i].ritardo>0){
    	    printf("\n%s %s %s %s %s\n",tratta[i].partenza,tratta[i].destinazione,tratta[i].data,tratta[i].orapartenza,tratta[i].oraarrivo);
    	}
    }
  
}

void print_rides_id_totdelay(struct tratte tratta[],int dim){
    char idbus[MAXN];
    int i,delay=0;
    
    //input
    fflush(stdin);
    printf("inserisci id bus \n");
    scanf("%s ",idbus);
    
    for(i=0;i<dim;i++){
        if(strcmp(tratta[i].codicetratta,idbus)==0 && tratta[i].ritardo>0) delay+=tratta[i].ritardo;
    }
  
    printf("ritardo cmplessivo %s e' di: %d",idbus,delay);
  
}
