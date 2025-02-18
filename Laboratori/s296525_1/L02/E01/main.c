#include <stdio.h>

typedef enum {
    false,
    true
} bool;

/*
 * Calcolo del MCD di a e b
 * 
 * a = numero intero
 * b = numero intero
 * 
 * Ritorna il MCD di a e b
 */
int gcd(int a, int b);

/*
 * Scambia la posizione in memoria di a e b
 * 
 * a = puntatore a numero intero
 * b = puntatore a numero intero
 */
void swap (int* a, int* b);

int main() {
    int a, b;
    do {
        printf("Inserisci due numeri interi positivi di cui calcolare il MCD: ");
        scanf("%d %d", &a, &b);
        if(a < 0 || b < 0) {
            printf("Inserisci dei valori validi!\n");
        }
    } while(a < 0 || b < 0);
    printf("MCD: %d", gcd(a,b));
    return 0;
}

int gcd(int a, int b) {
    // condizione calcolo MCD
    if (a < b) {
        swap(&a,&b);
    }
    
    // condizioni di terminazione
    if (a == 0 || a == 1)
        return b;
    if (b == 0)
        return a;

    // calcolo MCD
    bool a_is_odd = a%2, b_is_odd = b%2;
    if (!a_is_odd && !b_is_odd) {
        return 2*gcd(a/2, b/2);
    } else if (a_is_odd && !b_is_odd) {
        return gcd(a, b/2);
    } else if (!a_is_odd && b_is_odd) {
        return gcd(a/2, b);
    } else {
        return gcd((a-b)/2, b);
    }
}

void swap(int* a, int* b) {
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}