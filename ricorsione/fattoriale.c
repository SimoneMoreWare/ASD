#include <stdio.h>

//int fattoriale_iterativo(int n);
int fattoriale_ricorsivo(int n);
int main(){
    int n=4,res;
    //res=fattoriale_iterativo(n);
    
    //il programma chiama la funzione fattoriale_ricorsivo
    //la funzione sarà eseguita
    //e il valore di ritorno verrà assegnato alla variabile res
    res=fattoriale_ricorsivo(n);
    
    printf("%d ",res);
    return 0;
}

/*int fattoriale_iterativo(int n){
    int i, res=1;
    for(i=n;i>=1;i--) res=res*i;
    return res;
}*/


//es n=4
//controllo inanzitutto se n==1
//risposta no, 4 diverso da 1
//la funzione ritorna n*fattoriale_ricorsivo(n-1) -> 
//4*fact(3)
//non posso moltiplicare 4*funzione, dobbiamo eseguire la funzione, vedere cosa ci ritorna, e a quel punto moltiplicarla per 4 e da qui ritorniamo al main il fattoriale di 4
//calcoliamo fact(3)
//controlo n==1
//risposta no, ritorna n*fact(n-1) -> 3*fact(2) -> non posso moltplicare un numero per una funzione, devo prima vedere fact(2)
//fact(2)
//2!=1
//ritorno 2*fact(1), non posso moltiplicare un numero per un funzione-> controllo quanto vale fact(1)
//1==1 return 1 alla funzione fact(1)
//non dimentichiamoci perchè stiamo calcolando il fattoriale di 1, lo stiamo calcolando ci era stato richiesto il fattoriale di 2  
//fact(2) deve ritornare a fact(3) 2*fact(1) ossia 2
//fatt(3) deve ritornare a fact(4) 3*fact(2) ossia 6 
//fact(4) deve ritornare a main 4*fact(3)
//
//1==1 return 1 alla funzione fact(1), poi returno 2*1 a fact(2) -> return 3*2 a fact(3) -> return 4*6 a fact(4)

int fattoriale_ricorsivo(int n){
    if(n==1) return 1;
    return n*fattoriale_ricorsivo(n-1);
}
