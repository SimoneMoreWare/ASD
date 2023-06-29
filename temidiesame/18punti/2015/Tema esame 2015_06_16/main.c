#include <stdio.h>
#include <stdlib.h>
#include "skilifts.h"
#include "sciatori.h"

void ORAfromIntToChar(char *sTime, int numTime);
int ORAfromCharToInt(char *time);
int authorize (Skilifts sks, Sciatori scs, long cardId, char *skiliftId, int time);

int main()
{
    Skilifts sks;
    FILE *f;
    Sciatori scs;

    f=fopen("skilifts.txt", "r");
    if(f==NULL) exit(EXIT_FAILURE);

    sks=SKILIFTSread(f);
    scs=SCIATORIinit();

    printf("---PASSAGGI---\n");
    //PASSAGGI SCIATORE 1000
    authorize(sks, scs, 1000, "S001", 480);
    authorize(sks, scs, 1000, "S001", 485);
    authorize(sks, scs, 1000, "S001", 505);
    authorize(sks, scs, 1000, "S002", 530);
    authorize(sks, scs, 1000, "S003", 570);

    //PASSAGGI SCIATORE 1001
    printf("\n");
    authorize(sks, scs, 1001, "S001", 580);
    authorize(sks, scs, 1001, "S002", 605);
    authorize(sks, scs, 1001, "S002", 610);
    authorize(sks, scs, 1001, "S002", 645);
    authorize(sks, scs, 1001, "S003", 685);

    //PASSAGGI SCIATORE 1002
    printf("\n");
    authorize(sks, scs, 1002, "S001", 680);
    authorize(sks, scs, 1002, "S002", 705);
    authorize(sks, scs, 1002, "S003", 745);
    authorize(sks, scs, 1002, "S003", 750);
    authorize(sks, scs, 1002, "S003", 775);

    fprintf(fopen("output.txt", "a"), "---SKILIFT---\n");
    SKILIFTSprint(sks, fopen("output.txt", "a"));
    fprintf(fopen("output.txt", "a"), "\n");
    fprintf(fopen("output.txt", "a"), "---SCIATORI---\n");
    SCIATORIprint(scs, fopen("output.txt", "a"));
    return 0;
}



int authorize (Skilifts sks, Sciatori scs, long cardId, char *skiliftId, int time){
   Skilift *sk;
   Sciatore *sc, scP;
   char oraS[6];
   int lastTimeS;
   AutorizzazioneS *passaggioSciatore;
   AutorizzazioneSk *passaggioSkilift;

   sk=SKILIFTSsearch(sks, skiliftId);

   if(sk==NULL){
      printf("Lo skilift %s non esiste.\n", skiliftId);
      return -1;
   }

    sc=SCIATORIsearch(scs, cardId);

   if(sc==NULL){
      scP=SCIATOREcrea(cardId);
      ORAfromIntToChar(oraS, time);
      SCIATOREaddPassaggio(&scP, AUTORIZZAZIONEScrea(skiliftId, oraS));
      SCIATORIadd(scs, scP);
      SKILIFTaddPassaggio(sk, AUTORIZZAZIONESKcrea(cardId));
      printf("Lo sciatore %ld e' stato autorizzato allo skilift %s alle ore %s.\n", cardId, skiliftId, oraS);
      return VERO;
   }

   passaggioSciatore=SCIATOREcercaPassaggioSciatore(*sc, skiliftId);

   if(passaggioSciatore==NULL){
      ORAfromIntToChar(oraS, time);
      SCIATOREaddPassaggio(sc, AUTORIZZAZIONEScrea(skiliftId, oraS));
      SKILIFTaddPassaggio(sk, AUTORIZZAZIONESKcrea(cardId));
      printf("Lo sciatore %ld e' stato autorizzato allo skilift %s alle ore %s.\n", cardId, skiliftId, oraS);
      return VERO;
   }

   lastTimeS=ORAfromCharToInt(passaggioSciatore->time);
   if((time-lastTimeS)<sk->timeInterval){
      ORAfromIntToChar(oraS, time);
      printf("Lo sciatore %ld non e' stato autorizzato allo skilift %s: sono le ore %s, non sono ancora passati %d minuti.\n", cardId, skiliftId, oraS, sk->timeInterval);
      return FALSO;
   }

   passaggioSkilift=SKILIFTcercaPassaggioSciatore(*sk, cardId);
   AUTORIZZAZIONESKincrementaNumVolte(passaggioSkilift);
   ORAfromIntToChar(oraS, time);
   AUTORIZZAZIONESsetOra(passaggioSciatore, oraS);
   printf("Lo sciatore %ld e' stato autorizzato allo skilift %s alle ore %s.\n", cardId, skiliftId, oraS);
   return VERO;
}


void ORAfromIntToChar(char *sTime, int numTime){
    int h, m;
    h=numTime/60;
    m=numTime%60;
    sprintf(sTime, "%02d:%02d", h, m);
    return;
}


int ORAfromCharToInt(char *stime){
   int time, h, m;
   sscanf(stime, "%d:%d", &h, &m);
   time=(h*60)+m;
   return time;
}

