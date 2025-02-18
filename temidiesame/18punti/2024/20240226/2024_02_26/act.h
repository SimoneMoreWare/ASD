#ifndef ACT_H
#define ACT_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 20
#define MAX_VINC 2

typedef struct activities *ACT;

ACT activityRead(FILE *file);
int checkSelection(ACT a, char **selected, int nsel);

#endif