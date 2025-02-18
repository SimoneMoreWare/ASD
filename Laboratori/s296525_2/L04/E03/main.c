/*
 * Analisi del problema
 *
 * Consideriamo Z = zaffiro, R = rubino, T = topazio, S = smeraldo.
 * Si hanno le seguenti regole:
 * - se Z, il successivo sia Z o R;
 * - se S, il successivo sia S o T;
 * - se R, il successivo sia S o T;
 * - se T, il successivo sia Z o R.
 * 
 * Si può utilizzare una ricorsione simile a quella delle
 * disposizioni ripetute, applicando le regole di cui sopra
 * attraverso una funzione di verifica di accettabilità e di
 * ottimizzazione.
 * 
 * Si noti come la lunghezza della soluzione non è calcolabile,
 * ma può variare tra 1 e Z+R+S+T. 
 * 
 * E' possibile introdurre il pruning se la verifica di 
 * accettabilità non può essere rispettata (non è possibile 
 * assegnare la pietra preziosa successiva adatta) oppure se 
 * la lunghezza trovata è la lunghezza massima possibile.
 * 
 * Un'accortezza che diminuisce molto i tempi consiste nel notare
 * che, quando viene preso un elemento tra zaffiro (0) e smeraldo (3),
 * tutti gli elementi successivi che possono comporre la catena più lunga
 * sono anch'essi 0 e 3 rispettivamente fino al loro esaurimento.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define n_p 4

typedef enum {
    z,
    r,
    t,
    s
} type;

int check_terminate(int pos, int* val, int* sol, int max, int* flag) {
    int i;

    // se la dimensione è la massima possibile
    if(pos == max) {
        *flag = 1;
        return 1;
    }

    // la collana non è iniziata
    if(pos == 0) {
        for(i = 0; i < n_p; i++)
            if(val[i] > 0)
                return 0;
        return 1;
    }
    
    if(sol[pos-1]%2 == 0) { // se zaffiro o topazio
        if(val[z] == 0 && val[r] == 0)
            return 1;
    } else { // se rubino o smeraldo
        if(val[t] == 0 && val[s] == 0)
            return 1;
    }
    return 0;
}

void find_length(int pos, int* val, int* sol, int *max_length, int max, int* flag) {
    int i, j = 0, iS, iF;
    if(*flag || check_terminate(pos, val, sol, max, flag)) {
        if(*max_length < pos) {
            *max_length = pos;
        }
        return;
    }

    if (pos == 0) {
        iS = 0;
        iF = n_p;
    } else if(sol[pos-1]%2 == 0) {
        iS = 0;
        iF = n_p/2;
    } else {
        iS = n_p/2;
        iF = n_p;
    }
        
    for(i = iS; i < iF; i++)
        if(val[i] > 0) {
            if(i == 0 || i == 3) { // se 0 o 3, crea la catena
                for(; val[i] > 0; val[i]--, pos++, j++)
                    sol[pos] = i;
                find_length(pos, val, sol, max_length, max, flag);
                for(; j > 0; val[i]++, pos--, j--);
            } else {
                sol[pos] = i;
                val[i]--;
                find_length(pos+1, val, sol, max_length, max, flag);
                val[i]++;
            }
        }
}

int main() {
    FILE* file;
    int n, max, flag, val[n_p], *sol, max_length;
    char nome_file[50];
    printf("Inserisci il nome del file: ");
    scanf("%s", nome_file);

    if((file = fopen(nome_file, "r")) == NULL) {
        printf("Non è stato possibile aprire il file.");
        return 1;
    }
    fscanf(file, "%d", &n);
    for(int i = 0; i < n; i++) {
        max = 0;
        max_length = 0;
        flag = 0;
        for(int j = 0; j < n_p; j++) {
            fscanf(file, "%d", &val[j]);
            max = max + val[j];
        }
        sol = (int*) malloc(max*sizeof(int));

        find_length(0, val, sol, &max_length, max, &flag);

        printf( "TEST #%d\n"
                "Lunghezza massima della collana: %d\n", i+1, max_length);
        printf("\n");
        
        free(sol);
    }
    return 0;
}