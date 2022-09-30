#include <stdio.h>
//calcolare n-esimo numero nella serie di fibonacci
int fibonacci_ricorsivo(int n);

int main(){
    int n=4,res;
    res=fibonacci_ricorsivo(n);
    printf("%d\n",res);
    return 0;
}

//due condizzioni di terminazione
//due chiamate ricorsive
//nel main viene eseguito fib(4)
//primo step: controllo se n==0 o n==1
//            altrimenti la funzione ritorna fib(n-1)+fib(n-2)
//            fib(3)+fib(2)
//partiranno sempre due freccie tranne nel caso base

//chiamo prima fib(3), non è una caso base
//ritorna fib(2)+fib(1)
//calcoliamo fib(2), non è un caso base, ritorna fib(1)+fib(0)
//fib(1) caso base, ritorna 1, MA CI MANCA + fib(0) e ritorna 0
// a fib(2) ritorna 1+0 = 1
//fib(3) ritorna fib(2)+fib(1), fib(2) è 1 e manca fib(1), che è un caso base, a fib(3) rtirona 1+1=2
//fib(4) ha calcolato quante vale fib(3), gli manca capire quanto vale fib(2),
//fib(2) chiama fib(1)-fib(0) entrambi casi base e ritorna 1 a fib(2)
//fib(4) ha finito, perchè aveva chiamato fib(3) 2 e fib(2) 1
//al main ritorna 3
int fibonacci_ricorsivo(int n){
    if(n==0) return 0;
    if(n==1) return 1;
    return fibonacci_ricorsivo(n-1)+fibonacci_ricorsivo(n-2);
}

