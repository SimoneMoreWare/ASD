#include "trianglePacking.h"

//V
V Vread(FILE *f){
   V v;
   int i;
   for(i=0; i<3; i++)
      fscanf(f, "%d", &v.vertici[i]);
   return v;
}

V Vcreate(int *vertici){
   int i;
   V v;
   for(i=0; i<3; i++)
      v.vertici[i]=vertici[i];
   return v;
}

Boolean VisDisgiunti(V v1, V v2){
   int i, j;
   for(i=0; i<3; i++){
      for(j=0; j<3; j++){
         if(v1.vertici[i]==v2.vertici[j])
           return FALSO;
      }
   }
   return VERO;
}

Boolean VareThereRealVertex(V v, int numVertici){
   int i;
   for(i=0; i<3; i++){
      if(v.vertici[i]<0 || v.vertici[i]>=numVertici)
        return FALSO;
   }
   return VERO;
}

Boolean VareThereRealEdges(V v, int **archi){
   int i;
   for(i=0; i<2; i++)
      if(archi[v.vertici[i]][v.vertici[i+1]]==-1)
        return FALSO;
   if(archi[v.vertici[0]][v.vertici[2]]==-1)
     return FALSO;
   return VERO;
}

Boolean VcontieneVerticiDiversi(V v){
   if(v.vertici[0]!=v.vertici[1] && v.vertici[0]!=v.vertici[2] && v.vertici[1]!=v.vertici[2])
     return VERO;
   return FALSO;
}

void Vprint(V v, FILE *f){
   int i;
   for(i=0; i<3; i++)
      fprintf(f, "%d%s", v.vertici[i], (i==2)?"":", ");
   return;
}




//TP
struct trianglePacking{
   V *insiemi;
   int k, maxD;
};



TP TPinit(int max){
   TP tp;
   tp=(TP)malloc(sizeof(struct trianglePacking));
   if(tp==NULL) exit(EXIT_FAILURE);
   tp->maxD=max;
   tp->k=0;
   tp->insiemi=(V*)malloc(max*sizeof(V));
   if(tp->insiemi==NULL) exit(EXIT_FAILURE);
   return tp;
}


void TPinsert(TP tp, V insieme){
   if(tp->k==tp->maxD){
      tp->maxD=2*tp->maxD;
      tp->insiemi=realloc(tp->insiemi, tp->maxD*sizeof(V));
      if(tp->insiemi==NULL) exit(EXIT_FAILURE);
   }
   tp->insiemi[tp->k]=insieme;
   (tp->k)++;
   return;
}


void TPelimina(TP tp){
   (tp->k)--;
   return;
}


//Il file è cosi formato:
//Sulla prima riga è presente K (numero di insiemi V che compongono il triangle Packing.
//Seguono K righe composte da: <numero_di_vertici><vertici>
TP TPread(FILE *f){
    TP tp;
    int k, i, nVertici;
    V insieme;
    fscanf(f, "%d", &k);
    tp=TPinit(k);
    for(i=0; i<k; i++){
       fscanf(f, "%d", &nVertici);
       if(nVertici!=3)
         return NULL;
       insieme=Vread(f);
       TPinsert(tp, insieme);
    }
    return tp;
}


Boolean TPisTrianglePacking(TP tp, int **archi, int nVertici){
    int i, j;
    if(tp==NULL)
       return FALSO;
    for(i=0; i<tp->k; i++){
       if(VareThereRealVertex(tp->insiemi[i], nVertici)==FALSO)
          return FALSO;
       if(VcontieneVerticiDiversi(tp->insiemi[i])==FALSO)
          return FALSO;
       if(VareThereRealEdges(tp->insiemi[i], archi)==FALSO)
         return FALSO;
    }

    for(i=0; i<(tp->k)-1; i++)
       for(j=i+1; j<tp->k; j++)
         if(VisDisgiunti(tp->insiemi[i], tp->insiemi[j])==FALSO)
           return FALSO;
    return VERO;
}


Boolean TPisDisgiunto(TP tp){
   int i, j;
   for(i=0; i<(tp->k)-1; i++)
      for(j=i+1; j<tp->k; j++)
         if(VisDisgiunti(tp->insiemi[i], tp->insiemi[j])==FALSO)
           return FALSO;
   return VERO;
}


void TPcopia (TP tp1, TP tp2){
   int i;
   tp2->k=tp1->k;
   for(i=0; i<tp1->k; i++)
      tp2->insiemi[i]=tp1->insiemi[i];
   return;
}


void TPprint(TP tp, FILE *f){
   int i;
   fprintf(f, "Cardinalita': %d\n", tp->k);
   fprintf(f, "V={\n");
   for(i=0; i<tp->k; i++){
      fprintf(f, "\tV%d ={", i+1);
      Vprint(tp->insiemi[i], f);
      fprintf(f, "}\n");
   }
   fprintf(f, "  }");
   return;
}


void TPfree(TP tp){
   if(tp!=NULL){
      if(tp->insiemi!=NULL)
        free(tp->insiemi);
      free(tp);
   }
   return;
}
