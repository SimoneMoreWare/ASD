#include <stdio.h>
#include <stdlib.h>

typedef enum {
    z,
    r,
    t,
    s
} type;

int max(int a, int b) {
    return a>b ? a:b;
}

int ****malloc4d(int max_z, int max_r, int max_t, int max_s) {
    int ****m;
    int z, r, t, s;

    m = (int****) malloc((max_z+1)*sizeof(int***));
    for(z = 0; z <= max_z; z++) {
        m[z] = (int***) malloc((max_r+1)*sizeof(int**));
        for(r = 0; r <= max_r; r++) {
            m[z][r] = (int**) malloc((max_t+1)*sizeof(int*));
            for(t = 0; t <= max_t; t++) {
                m[z][r][t] = (int*) malloc((max_s+1)*sizeof(int));
            }
        }
    }

    for(z = 0; z <= max_z; z++) 
        for(r = 0; r <= max_r; r++) 
            for(t = 0; t <= max_t; t++) 
                for(s = 0; s <= max_s; s++) 
                    m[z][r][t][s] = -1;
    
    return m;
}

int fr(int ****mz, int ****mr, int ****mt, int ****ms,  int *gemme);
int ft(int ****mz, int ****mr, int ****mt, int ****ms,  int *gemme);
int fr(int ****mz, int ****mr, int ****mt, int ****ms,  int *gemme);
int fs(int ****mz, int ****mr, int ****mt, int ****ms,  int *gemme);

int fz(int ****mz, int ****mr, int ****mt, int ****ms, int *gemme) {
    int max_z, max_r, resz;

    if(gemme[z] == 0) 
        return 0;
    
    if(mz[gemme[z]][gemme[r]][gemme[t]][gemme[s]] != -1)
        return mz[gemme[z]][gemme[r]][gemme[t]][gemme[s]];
    
    gemme[z]--;
    max_z = fz(mz, mr, mt, ms, gemme);
    max_r = fr(mz, mr, mt, ms, gemme);
    gemme[z]++;

    resz = max(max_z, max_r) + 1;
    mz[gemme[z]][gemme[r]][gemme[t]][gemme[s]] = resz;

    return resz;
}

int ft(int ****mz, int ****mr, int ****mt, int ****ms,  int *gemme) {
    int max_z, max_r;
    int rest;

    if(gemme[t] == 0)  
        return 0;
    
    if(mt[gemme[z]][gemme[r]][gemme[t]][gemme[s]] != -1)
        return mt[gemme[z]][gemme[r]][gemme[t]][gemme[s]];
    
    gemme[t]--;
    max_z = fz(mz, mr, mt, ms, gemme);
    max_r = fr(mz, mr, mt, ms, gemme);
    gemme[t]++;

    rest = max(max_z, max_r) + 1;
    mt[gemme[z]][gemme[r]][gemme[t]][gemme[s]] = rest;

    return rest;
}

int fr(int ****mz, int ****mr, int ****mt, int ****ms,  int *gemme) {
    int max_s, max_t;
    int resr;

    if(gemme[r] == 0) 
        return 0;
    
    if(mr[gemme[z]][gemme[r]][gemme[t]][gemme[s]] != -1) 
        return mr[gemme[z]][gemme[r]][gemme[t]][gemme[s]];
    
    gemme[r]--;
    max_s = fs(mz, mr, mt, ms, gemme);
    max_t = ft(mz, mr, mt, ms, gemme);
    gemme[r]++;
    
    resr = max(max_s, max_t) + 1;
    mr[gemme[z]][gemme[r]][gemme[t]][gemme[s]] = resr;
    
    return resr;
}

int fs(int ****mz, int ****mr, int ****mt, int ****ms,  int *gemme) {
    int max_s, max_t;
    int ress;
    
    if(gemme[s] == 0) 
        return 0;
    if(ms[gemme[z]][gemme[r]][gemme[t]][gemme[s]] != -1) 
        return ms[gemme[z]][gemme[r]][gemme[t]][gemme[s]];
    
    gemme[s]--;
    max_s = fs(mz, mr, mt, ms, gemme);
    max_t = ft(mz, mr, mt, ms, gemme);
    gemme[s]++;
    
    ress = max(max_s, max_t) + 1;
    ms[gemme[z]][gemme[r]][gemme[t]][gemme[s]] = ress;
    
    return ress;
}

void dealloca(int ****memoizationZ, int ****memoizationR, int ****memoizationT, int ****memoizationS, int max_z, int max_r, int max_t) {
    int i, j, k;
    for(i = 0; i <= max_z; i++) {
        for(j = 0; j <= max_r; j++) {
            for(k = 0; k <= max_t; k++) {
                free(memoizationZ[i][j][k]);
                free(memoizationR[i][j][k]);
                free(memoizationT[i][j][k]);
                free(memoizationS[i][j][k]);
            }
            free(memoizationZ[i][j]);
            free(memoizationR[i][j]);
            free(memoizationT[i][j]);
            free(memoizationS[i][j]);
        }
        free(memoizationZ[i]);
        free(memoizationR[i]);
        free(memoizationT[i]);
        free(memoizationS[i]);
    }
    free(memoizationZ);
    free(memoizationR);
    free(memoizationT);
    free(memoizationS);
}

int SolveM(int *gemme) {
    int ****mem_z, ****mem_r, ****mem_t, ****mem_s, max_len, tmp;
    int max_z = gemme[z], max_r = gemme[r], max_t = gemme[t], max_s = gemme[s];

    mem_z = malloc4d(max_z, max_r, max_t, max_s);
    mem_r = malloc4d(max_z, max_r, max_t, max_s);
    mem_t = malloc4d(max_z, max_r, max_t, max_s);
    mem_s = malloc4d(max_z, max_r, max_t, max_s);

    max_len = fz(mem_z, mem_r, mem_t, mem_s, gemme);
    tmp = fr(mem_z, mem_r, mem_t, mem_s, gemme);
    max_len = max(max_len, tmp);
    tmp = ft(mem_z, mem_r, mem_t, mem_s, gemme);
    max_len = max(max_len, tmp);
    tmp = fs(mem_z, mem_r, mem_t, mem_s, gemme);
    max_len = max(max_len, tmp);
    
    dealloca(mem_z, mem_r, mem_t, mem_s, max_z, max_r, max_t);
    
    return max_len;
}

int main() {
    FILE *file;
    int max_len, n, i, gemme[4];
    char nome_file[50];
    printf("Inserisci il nome del file: ");
    scanf("%s", nome_file);

    if((file = fopen(nome_file, "r")) == NULL) {
        printf("Non è stato possibile aprire il file.");
        return 1;
    }
    fscanf(file, "%d", &n);
    
    for(i = 0; i < n; i++) {
        fscanf(file, "%d %d %d %d", &gemme[z], &gemme[r], &gemme[t], &gemme[s]);
        max_len = SolveM(gemme);
        printf( "TEST #%d\n"
                "Lunghezza massima della collana: %d\n", i+1, max_len);
        printf("\n");
    }
    
    return 0;
}

