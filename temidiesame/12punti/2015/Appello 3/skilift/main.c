#include <stdio.h>
#include <stdlib.h>

#include "skilift.h"
#include "ST.h" 
#include "skier.h"
#include "BST.h"

#define MAXNINIT 100
#define MAX 21

void readSkiliftData(char *fname, ST skilifts) {
  FILE *fin = fopen(fname, "r");
  char id[MAX];
  int time;
  if (fin == NULL) {
    printf("Cannot open file %s\n", fname);
    exit(-1);
  }
  while(fscanf(fin, "%s %d", id, &time) == 2)
    STsearchOrInsert(skilifts, id, time);
  fclose(fin);
}

int authorize (int cardId, char *skiliftId, int time, ST skilifts,
	       BST skiers) {
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
  if ((last_time == -1) ||
      (time - last_time) > SKILIFTinterval(this_skilift)) {
    SKIERsetTime(s, time, skiliftIndex);
    return 1;
  }
  else
    return 0;
}

int authorize_debug(int cardId, char *skiliftId, int time, ST skilifts,
		    BST skiers) {
  int res;
  printf("Requested authorization for skilift %s by skier %d at %d\n", skiliftId, cardId, time);
  printf("Skilifts:\n");
  STdisplay(skilifts, stdout);
  printf("Skiers:\n");
  BSTprint(skiers, stdout);
  res = authorize(cardId, skiliftId, time, skilifts, skiers);
  if (res)
    printf("Request result: OK\n");
  else
    printf("Request result: DENY\n");
  printf("Updated skiers:\n");
  BSTprint(skiers, stdout);
  printf("\n");
}
  

int main() {
  ST skilifts = STinit(MAXNINIT);
  BST skiers = BSTinit();
  readSkiliftData("skiliftdata.txt", skilifts);
  authorize_debug(100, "0003", 0, skilifts, skiers);
  authorize_debug(100, "0002", 5, skilifts, skiers);
  authorize_debug(103, "0004", 7, skilifts, skiers);
  authorize_debug(101, "0003", 10, skilifts, skiers);
  authorize_debug(100, "0004", 7, skilifts, skiers);
  authorize_debug(101, "0003", 12, skilifts, skiers);  
  authorize_debug(100, "0002", 5, skilifts, skiers);
  authorize_debug(102, "0003", 10, skilifts, skiers);
  authorize_debug(100, "0003", 12, skilifts, skiers);  
  authorize_debug(100, "0004", 0, skilifts, skiers);
  authorize_debug(100, "0009", 0, skilifts, skiers); /* No skilift 0009 */
  BSTdestroy(skiers);
  STdestroy(skilifts);
}

