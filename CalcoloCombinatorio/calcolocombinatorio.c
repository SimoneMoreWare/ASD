#include <stdio.h>
#include <stdlib.h>

typedef struct { int *scelte; int num_scelte; } Livello;

int princ_molt(int pos, Livello *val, int *sol, int k, int count);
int disp_sempl(int pos, int *val, int *sol, int *mark, int n, int k, int count);
int disp_ripet(int pos, int *val, int *sol, int n, int k, int count);
int perm_sempl(int pos, int *val, int *sol, int *mark, int n,  int count);
int perm_ripet(int pos, int *dist_val, int *sol, int *mark, int n,  int n_dist, int count);
int comb_sempl(int pos, int *val, int *sol, int n, int k, int start, int count);
int comb_ripet(int pos, int *val, int *sol, int n, int k, int start, int count);
void Merge(int *val, int l, int q, int r);
void MergeSort(int *val, int l, int r);

int main(void){
    int i, j, n, n_dist, k, total, *val, *dist_val, *sol, *mark;
    Livello *valor;

    printf("\n");
    printf("\n Calcolo Combinatorio su interi\n");
    printf("===============\n");
    printf("1. Principio di moltiplicazione\n");
    printf("2. Disposizioni semplici\n");
    printf("3. Disposizioni ripetute\n");
    printf("4. Permutazioni semplici\n");
    printf("5. Permutazioni ripetute\n");
    printf("6. Combinazioni semplici\n");
    printf("7. Combinazioni ripetute\n");
    printf("8. Exit\n");
    printf("Selezionare : ");
    if(scanf("%d",&i)<=0) {
        printf("Solo interi!\n");
        exit(0);
    }
    else {
        switch(i) {
            case 1:     printf("Inserisci il numero di decisioni n: ");
                scanf("%d", &k);
                valor = malloc(k * sizeof(Livello));
                for(i = 0; i < k; i++) {
                    printf("Inserisci il numero di scelte per il passo %d: ", i);
                    scanf("%d", &valor[i].num_scelte);
                    valor[i].scelte = malloc(valor[i].num_scelte * sizeof(int));
                }
                for (i = 0; i < k; i++)
                    for (j = 0; j < valor[i].num_scelte; j++) {
                        printf("inserisci scelta %d-esima a livello %d: ", j, i);
                        scanf("%d", &valor[i].scelte[j]);
                    }
                sol = malloc(k * sizeof(int));

                printf("L'applicazione del principio di moltiplicazione da' le seguenti soluzioni: \n");
                total = princ_molt(0, valor, sol, k, 0);
                printf("e in totale sono %d \n", total);
                free(sol);
                for (i = 0; i < k; i++)
                    free(valor[i].scelte);
                free(valor);
                break;
            case 2:     printf("Inserisci n: ");
                scanf("%d", &n);
                printf("Inserisci k: ");
                scanf("%d", &k);
                val = malloc(n * sizeof(int));
                sol = malloc(k * sizeof(int));
                mark = calloc(n, sizeof(int));
                for (i=0; i < k; i++)
                    sol[i]= -1;
                for (i=0; i<n; i++) {
                    printf("Inserisci elemento %d: ", i);
                    scanf("%d", &val[i]);
                }
                printf("Le disposizioni semplici di %d interi  ", n);
                for (i=0; i <n; i++)
                    printf("%d ", val[i]);
                printf(" a %d a %d sono:\n", k, k);
                total = disp_sempl(0, val, sol, mark, n, k, 0);
                printf("e in totale sono %d \n", total);
                free(sol);
                free(val);
                free(mark);
                break;
            case 3:     printf("Inserisci n: ");
                scanf("%d", &n);
                printf("Inserisci k: ");
                scanf("%d", &k);
                val = malloc(n * sizeof(int));
                sol = malloc(k * sizeof(int));
                for (i=0; i < k; i++)
                    sol[i]= -1;
                for (i=0; i<n; i++) {
                    printf("Inserisci elemento %d: ", i);
                    scanf("%d", &val[i]);
                }
                printf("Le disposizioni ripetute di %d interi  ", n);
                for (i=0; i <n; i++)
                    printf("%d ", val[i]);
                printf("a %d a %d sono:\n", k, k);
                total = disp_ripet(0, val, sol, n, k, 0);
                printf("e in totale sono %d \n", total);
                free(sol);
                free(val);
                break;
            case 4:     printf("Inserisci n: ");
                scanf("%d", &n);
                val = malloc(n * sizeof(int));
                sol = malloc(n * sizeof(int));
                mark = calloc(n, sizeof(int));
                for (i=0; i < n; i++)
                    sol[i]= -1;
                for (i=0; i<n; i++) {
                    printf("Inserisci elemento %d: ", i);
                    scanf("%d", &val[i]);
                }
                printf("Le permutazioni semplici di %d interi  ", n);
                for (i=0; i <n; i++)
                    printf("%d ", val[i]);
                printf("sono:\n");
                total = perm_sempl(0, val, sol, mark, n, 0);
                printf("e in totale sono %d \n", total);
                free(sol);
                free(val);
                free(mark);
                break;
            case 5:     printf("Inserisci n: ");
                scanf("%d", &n);
                val = malloc(n * sizeof(int));
                dist_val = malloc(n * sizeof(int));
                sol = malloc(n * sizeof(int));
                for (i=0; i<n; i++) {
                    printf("Inserisci elemento %d: ", i);
                    scanf("%d", &val[i]);
                }
                printf("Le permutazioni distinte di %d interi con ripetizione ", n);
                for (i=0; i <n; i++)
                    printf("%d ", val[i]);
                printf("sono:\n");
                MergeSort(val, 0, n-1);
                n_dist =1;
                for (i=1; i<n; i++)
                    if(val[i-1] != val[i])
                        n_dist++;
                mark = calloc(n_dist,sizeof(int));
                j = 0;
                dist_val[j++] = val[0];
                for (i=1; i<n; i++)
                    if(val[i-1] != val[i])
                        dist_val[j++]= val[i];
                i = 1;
                j = 0;
                mark[j] = 1;
                while(i < n) {
                    while (val[i-1] == val[i]) {
                        i++;
                        mark[j]++;
                    }
                    j++;
                    mark[j]++;
                    i++;
                }
                for (i=0; i < n; i++)
                    sol[i]= -1;
                total = perm_ripet(0, dist_val, sol, mark, n, n_dist, 0);
                printf("e in totale sono %d \n", total);
                free(sol);
                free(val);
                free(dist_val);
                free(mark);
                break;
            case 6:     printf("Inserisci n: ");
                scanf("%d", &n);
                printf("Inserisci k: ");
                scanf("%d", &k);
                val = malloc(n * sizeof(int));
                sol = malloc(k * sizeof(int));
                for (i=0; i < k; i++)
                    sol[i]= -1;
                for (i=0; i<n; i++) {
                    printf("Inserisci elemento %d: ", i);
                    scanf("%d", &val[i]);
                }
                printf("Le combinazioni  semplici  di %d interi  ", n);
                for (i=0; i <n; i++)
                    printf("%d ", val[i]);
                printf(" a %d a %d sono:\n", k, k);
                total = comb_sempl(0, val, sol, n, k, 0, 0);
                printf("e in totale sono %d \n", total);
                free(sol);
                free(val);
                break;
            case 7:     printf("Inserisci n: ");
                scanf("%d", &n);
                printf("Inserisci k: ");
                scanf("%d", &k);
                val = malloc(n * sizeof(int));
                sol = malloc(k * sizeof(int));
                for (i=0; i < k; i++)
                    sol[i]= -1;
                for (i=0; i<n; i++) {
                    printf("Inserisci elemento %d: ", i);
                    scanf("%d", &val[i]);
                }
                printf("Le combinazioni  ripetute  di %d interi  ", n);
                for (i=0; i <n; i++)
                    printf("%d ", val[i]);
                printf(" a %d a %d sono:\n", k, k);
                total = comb_ripet(0, val, sol, n, k, 0, 0);
                printf("e in totale sono %d \n", total);
                free(sol);
                free(val);
                break;
            case 8:     break;
            default:    printf("Opzione non valida\n");
        }
    }
    return 0;
}

int princ_molt(int pos, Livello *val, int *sol, int k, int count) {
    int i;
    if (pos >= k) {
        for (i = 0; i < k; i++)
            printf("%d ", sol[i]);
        printf("\n");
        return count+1;
    }
    for (i = 0; i < val[pos].num_scelte; i++) {
        sol[pos] = val[pos].scelte[i];
        count = princ_molt(pos+1, val, sol, k, count);
    }
    return count;
}

int disp_sempl(int pos, int *val, int *sol, int *mark, int n, int k, int count) {
    int i;
    if (pos >= k) {
        for (i=0; i<k; i++)
            printf("%d ", sol[i]);
        printf("\n");
        return count+1;
    }
    for (i=0; i<n; i++) {
        if (mark[i] == 0) {
            mark[i] = 1;
            sol[pos] = val[i];
            count = disp_sempl(pos+1, val, sol, mark, n, k, count);
            mark[i] = 0;
        }
    }
    return count;
}

int disp_ripet(int pos, int *val, int *sol, int n, int k, int count) {
    int i;
    if (pos >= k) {
        for (i=0; i<k; i++)
            printf("%d ", sol[i]);
        printf("\n");
        return count+1;
    }
    for (i = 0; i < n; i++) {
        sol[pos] = val[i];
        count = disp_ripet(pos+1, val, sol, n, k, count);
    }
    return count;
}

int perm_sempl(int pos, int *val, int *sol, int *mark, int n,  int count) {
    int i;
    if (pos >= n) {
        for (i=0; i<n; i++)
            printf("%d ", sol[i]);
        printf("\n");
        return count+1;
    }

    for (i=0; i<n; i++)
        if (mark[i] == 0) {
            mark[i] = 1;
            sol[pos] = val[i];
            count = perm_sempl(pos+1, val, sol, mark, n,  count);
            mark[i] = 0;
        }
    return count;
}

int perm_ripet(int pos, int *dist_val, int *sol, int *mark, int n, int n_dist, int count) {
    int i;
    if (pos >= n) {
        for (i=0; i<n; i++)
            printf("%d ", sol[i]);
        printf("\n");
        return count+1;
    }
    for (i=0; i<n_dist; i++) {
        if (mark[i] > 0) {
            mark[i]--;
            sol[pos] = dist_val[i];
            count = perm_ripet(pos+1, dist_val, sol, mark, n, n_dist, count);
            mark[i]++;
        }
    }
    return count;
}


int comb_sempl(int pos, int *val, int *sol, int n, int k, int start,  int count) {
    int i;
    if (pos >= k) {
        for (i=0; i<k; i++)
            printf("%d ", sol[i]);
        printf("\n");
        return count+1;
    }
    for (i=start; i<n; i++) {
        sol[pos] = val[i];
        count = comb_sempl(pos+1, val, sol, n, k, i+1, count);
    }
    return count;
}

int comb_ripet(int pos, int *val, int *sol, int n, int k, int start,  int count) {
    int i;
    if (pos >= k) {
        for (i=0; i<k; i++)
            printf("%d ", sol[i]);
        printf("\n");
        return count+1;
    }
    for (i=start; i<n; i++) {
        sol[pos] = val[i];
        count = comb_ripet(pos+1, val, sol, n, k, start, count);
        start++;
    }
    return count;
}

void Merge(int *val, int l, int q, int r) {
    int i, j, k, *B;
    int len;
    len = r - l +1;
    B = malloc (len *sizeof(int));
    i = l;
    j = q+1;
    for(k = l; k <= r; k++)
        if (i > q)
            B[k] = val[j++];
        else if (j > r)
            B[k] = val[i++];
        else if (( val[i] < val[j]) || (val[i] == val[j])  )
            B[k] = val[i++];
        else
            B[k] = val[j++];
    for ( k = l; k <= r; k++ )
        val[k] = B[k];
    return;
}

void MergeSort(int *val, int l, int r) {
    int q;
    if (r <= l)
        return;
    q = (l + r)/2;
    MergeSort(val, l, q);
    MergeSort(val, q+1, r);
    Merge(val, l, q, r);
}

