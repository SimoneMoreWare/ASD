#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "skilift.h"

struct ski_lift {
  char *id;
  int index;
  int time;
};

skilift SKILIFTnew(char *str, int time, int index) {
  skilift tmp = (skilift) malloc (sizeof(struct ski_lift));
  if (tmp == NULL) {
    printf("Errore di allocazione di memoria\n");
    exit(1);
  }
  if (tmp != NULL) {
    tmp->id = strdup(str);
    tmp->time = time;
    tmp->index = index;
  }
  return tmp;
}

void SKILIFTfree(skilift s) {
  if (s == NULL)
    return;
  free(s->id);
  free(s);
}

char *SKILIFTid(skilift s) {
  return s->id;
}

int SKILIFTinterval(skilift s) {
  return s->time;
}

int SKILIFTindex(skilift s) {
  return s->index;
}
