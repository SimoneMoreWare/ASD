#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include "ST.h"
#include "BST.h"
#include "skilift.h"
#include "skier.h"

#define MAX 11

int authorize (int cardId, char *skiliftId, int time, ST skilifts, BST skiers);
void readSkiliftData(char *fname, ST skilifts);

int main(int argc, char **argv) {
  int i, id, time;
  char sk[MAX];
  FILE *fin = fopen(argv[2], "r");
  ST skilifts;
  BST skiers;

  skilifts = STinit(1);
  skiers = BSTinit();

  readSkiliftData(argv[1], skilifts);

  while(fscanf(fin, "%s %d %d",  sk, &id, &time) == 3)
    printf("skier %d %s on %s at %d \n", id, authorize(id, sk, time, skilifts, skiers) ? "ALLOWED" : "NOT ALLOWED ", sk, time);
  printf("\n");

  for (i=0; i <= BSTcount(skiers); i++)
    SKIERlistSkilifts(BSTsearch(skiers, i), skilifts);

  BSTfree(skiers);
  STfree(skilifts);
  fclose(fin);
  return 0;
}

void readSkiliftData(char *fname, ST skilifts) {
  FILE *fin = fopen(fname, "r");
  char id[MAX];
  int time;

  while(fscanf(fin, "%s %d", id, &time) == 2)
    STsearchOrInsert(skilifts, id, time);

  fclose(fin);
}

int authorize (int cardId, char *skiliftId, int time, ST skilifts, BST skiers) {
  int n_skilifts = STcount(skilifts), skiliftIndex, last_time;
  skilift this_skilift;
  skier s;

  this_skilift = STsearch(skilifts, skiliftId);
  if (this_skilift == NULL)
    return 0;

  skiliftIndex = SKILIFTindex(this_skilift);

  s = BSTsearch(skiers, cardId);
  if (s == NULL) {
    s = SKIERnew(cardId, n_skilifts);
    BSTinsert(skiers, s);
    SKIERsetTime(s, time, skiliftIndex);
    return 1;
  }

  last_time = SKIERgetTime(s, skiliftIndex);
  if ((last_time == -1) || (time - last_time) > SKILIFTinterval(this_skilift)) {
    SKIERsetTime(s, time, skiliftIndex);
    return 1;
  } else
    return 0;
}



