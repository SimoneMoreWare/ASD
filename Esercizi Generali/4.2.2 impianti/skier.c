#include "skier.h"

struct user {
  int id;
  int *skiersSkilifts;
};

skier SKIERnew(int id, int n_skilift) {
  skier tmp = (skier) malloc(sizeof(struct user));
  if (tmp == NULL) {
    printf("Errore di allocazione di memoria\n");
    exit(1);
  }
  int i;
  if (tmp != NULL) {
    tmp->id = id;
    tmp->skiersSkilifts = calloc(n_skilift, sizeof(int));
    if (tmp->skiersSkilifts == NULL) {
      printf("Errore di allocazione di memoria\n");
      exit(1);
    }
  }
  for (i=0; i<n_skilift; i++)
    tmp->skiersSkilifts[i] = -1;
  return tmp;
}

void SKIERfree(skier s) {
  if (s == NULL)
    return;
  free(s->skiersSkilifts);
  free(s);
}

void SKIERprint(FILE *fp, skier s) {
  if (s != NULL)
    fprintf(fp, "%d", s->id);
}

int SKIERid(skier s) {
  return s->id;
}

void SKIERsetTime(skier s, int time, int indice_skilift) {
  s->skiersSkilifts[indice_skilift] = time;
}
int SKIERgetTime(skier s, int indice_skilift) {
  return s->skiersSkilifts[indice_skilift];
}

void SKIERlistSkilifts(skier s, ST st_skilift) {
  int i;
  if (s == NULL)
    return;
  printf("Skilifts used by skier %d\n", s->id);
  for (i=0; i<STcount(st_skilift); i++) {
    if (s->skiersSkilifts[i] >= 0) {
      skilift sk = STsearchByIndex(st_skilift, i);
      if (sk == NULL) continue;
      printf("  %s (last ride at time %d)\n", SKILIFTid(sk), s->skiersSkilifts[i]);
    }
  }
}
