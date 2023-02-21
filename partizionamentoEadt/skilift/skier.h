#ifndef SKIER
#define SKIER

typedef struct user *skier;

skier SKIERnew(int id, int n_skilift);
void SKIERfree(skier s);
void SKIERprint(FILE *fp, skier s);
int SKIERid(skier s);
void SKIERsetTime(skier s, int time, int indice_skilift);
int SKIERgetTime(skier s, int indice_skilift);
void SKIERlistSkilifts(skier s, ST st_skilift);
skier SKIERNULL();
#endif
