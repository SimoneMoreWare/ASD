#include <stdio.h>
#include <string.h>

void swap(int *x,int *y);

struct person{
   int age;
   float weight;
};

int main(){
    //dichiarazione variabili
    int a=1;
    char b='a';
    
    //dichiarazione puntatori
    int *pa;
    char *pb;
    //i puntatori abbiamo detto che contengono un indrizzo
    //ma come faccio a mettere dentro pa l'indirizzo di a?
    // si usa la &
    pa=&a; //vai a prendere l'indirizzo di memoria in cui è contenuta la variabile a
    pb=&b; //vai a prendere l'indirizzo di memoria in cui è contenuto la variabile b

    printf("Indirizzo di memoria di a: %p - indirizzo di memoria di b: %p\n",pa,pb); // 0x7fffffffdc64 0x7fffffffdc63
    printf("Indirizzo di memoria di a: %p - indirizzo di memoria di b: %p\n",&a,&b); //0x7fffffffdc64 0x7fffffffdc63
    
    //utilizziamo l'indirizzo contenuton rispettivamente in a e b, e con * stampare il contenuto di a e b
    //prendo l'indirizzo, cerco nell'indirizzo il valore che devo utilizzare
    printf("Valore di a %d e valore di b %c\n",*pa,*pb); //1 a
    printf("Valore di a %d e valore di b %c\n",a,b); //1 a
    printf("indirizzo di memoria del puntatore a %p, indirizzo di memoria del puntatore b %p\n ",&pa,&pb); //0x7fffffffdc68 0x7fffffffdc70

    //se modifico il valore del dato puntato dal puntatore, o il valore della variabile a il puntatore punta verra modificato
    //entrambi 
    a=69;
    printf("valore di a %d, valore di pa %d\n",a,*pa); //69 69
    //vai alla cella di memoria a cui punta pb, il contenuto di quella cella di memoria viene modificato e mettendo all interno di quella cella memoria il valore da modificare 
    *pb='m';
    printf("valore di b %c, valore di pb %c\n",b,*pb);// m m
    
    printf("char %lu, int %lu\n",sizeof(b),sizeof(a)); //char 1 int 4
    printf("\npunct char %lu, punct int %lu\n ",sizeof(char*),sizeof(int*));//char* 8, int* 8

    //Esempio funzione
    //i puntatori sono fondamentali nel momento in cui si vogliano utilizzare funzioni in cui si vogliono modificare/cambiare i valori a più variabili
    //in c non possiamo far ritornare da una funzione più variabili
    //in c le funzioni formalmente sono sempre passate by value, ossia si passa alla funzione una fotocopia delle variabili/parametri e la funzione fa quello che vuole,
    //quindi con i puntatori possiamo passare per valore l'indirizzo della variabile a cui punta e all'interno della funzione modifcare i conntenuti negli indirizzi in cui il puntatore punta e quindi "modificare anche tali valori all'interno del main"
    int x=42;
    int y=69;
    printf("prima dello swap, valore di x %d, valore di y %d\n",x,y); //42 69
    swap(&x,&y);
    printf("dopo lo swap, valore di x %d, valore di y %d\n",x,y); //69 42

    //ARITMETRICA DEI PUNTATORI
    //assegnamento
    //uando un puntatore viene dichiarato non punta a nulla!  Per poterlo utilizzare deve puntare a qualcosa! E' infatti un errore comune non assegnare un indirizzo di memoria a un  puntatore prima di usarlo.
    int c=5;
    int *pc=&c;
    int *pc_second;
    //assegno al puntatore Pc_second l'indirizzo contenuto all'interno del puntatore pc
    //puntatore come riferimento?
    pc_second=pc; 
    printf("indirizzo di pc %p, indirizzo di pc_second %p \n",pc_second,pc); //stesso
    //modifico valore contenuto della variabile a cui punta pc_second
    *pc_second=666;
    printf("valore pc_second %d , valore pc %d, valore c %d\n",*pc_second,*pc,c); //666 666 666 

    //confronto
    int q=1;
    int w=1;
    int *pq=&q;
    int *pw=&w;
    //confronto indirizzi di memoria
    if(pq==pw){
        printf("gli indirizzi a cui puntano i puntatori sono gli stessi\n");
    }else{
        printf("puntatori hanno diversi indirizzi a cui puntano\n");//PRINT THIS
    }
    //confronto contenuto degli indirizzi a cui puntano i puntatori
    if(*pq==*pw){
        printf("i contenuti degli indirizzi a cui puntano i puntantori hanno lo stesso valore\n");//PRINT THIS
    }else{
        printf("i contenuti degli indirizzi a cui puntano i puntaotri NON assumono lo stesso valore\n");
    }

    //dualità puntatore vettore
    int k[100];
    int i;
    for(i=0;i<100;i++) k[i]=i; //riempo il vettore
    //for(i=0;i<100;i++) scanf("%d ",&k[i]); //inserisco valori array 

    //modalità di accesso tramite puntatore
    int *pk=k; //come scrivere int *pk=&k[0];
    for(i=0;i<100;i++) printf("%d",*(pk+i)); //0,1,2,3,4,...,99
    printf("1 \n\n\n");
    for(i=0;i<100;i++) *(pk+i)=*(pk+i)*2; //raddoppio tutti i valori del vettore
    printf("2 \n\n\n");
    for(i=0;i<100;i++) printf("%d ",*(pk+i)); //0,2,4,6,8,...,198
    printf("3 \n\n\n");
    for(i=0;i<100;i++,pk++) printf("%p ",pk);//stampo indirizzo della cella a cui punta il puntatore, incremento il valore del puntatore (ossia shifto di sizeof cassele) nel for
    printf("4 \n\n\n");
    //for(i=0;i<100;i++;k++) printf("%p ",k); non posso utilizzare la variabile che identifica il vettore in quando il nome della variabile è una costante puntatore e non posso modificare il suo valore
    printf("\n %p\n",pk+2);//stampo indirizzo cella di memoria della terza casella dell'array
    //modalità mista
    //for(i=0;i<100;i++) scanf("%d ",&pk[i]);//espressione equivalente alla riga 86 , inserisco valori array
    //for(i=0;i<100;i++) scanf("%d ",k+i);//!! espressione equivalente alla riga 95 e 86, inserisco valori array
    printf("5 \n\n\n");
    for(i=0;i<100;i++) printf("%d ",*(k+i));//vett[i] equivale a *(vett+i)
    printf("6 \n\n\n");
    int l=42;
    int r=69;
    int *punt_subarray=&k[l];//assegno al puntatore l'indirizzo di memoria della cella "l" dell'array
    int n=r-l+1; //quante volte devo iterare
    for(i=0;i<n;i++) printf("%d ",*(punt_subarray+i)); //stampo i valori del subarray con scrittura equivalente della riga 94

    //puntatori e stringhe
    char str[]="ciaociaociaociao";
    char *pstr=&str[0];
    for(i=0;i<strlen(str);i++){
        printf("%c ",*(pstr+i));
    }

    //puntatori e struct
    struct person *personPtr, person1;
    personPtr = &person1;   

    printf("Enter age: ");
    scanf("%d", &personPtr->age);

    printf("Enter weight: ");
    scanf("%f", &personPtr->weight);

    printf("Displaying:\n");
    printf("Age: %d\n", personPtr->age);
    printf("weight: %f", personPtr->weight);

    return 0;
}

void swap(int *x,int *y){
    int tmp;
    tmp=*x;
    *x=*y;
    *y=tmp;
}
