#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "skilift.h"

struct ski_lift {
  char *id;
  int index;
  int time;
};

skilift SKILIFTnew(char *str, int time, int index) {
  skilift tmp = (skilift) malloc (sizeof(struct ski_lift));
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

void SKILIFTprint(skilift s, FILE *fp) {
  if (s != NULL)
    fprintf(fp, "Skilift %s - %d - %d", s->id, s->index, s->time);
}

skilift SKILIFTNULL() {
  return NULL;
}
