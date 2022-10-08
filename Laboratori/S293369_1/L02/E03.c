#include <stdio.h>
#include <stdlib.h>

struct prova{
    int x;
    int y;
    char ch;
};

int main(){
    struct prova *prova_ptr,**prova_adt;
    int dim=9;
    prova_ptr=(struct prova *) malloc(dim*sizeof (struct prova));
    prova_adt=(struct prova **) malloc(5*sizeof(struct prova*));//NUMERO RIGHE
    for(int i=0;i<dim;i++){
        prova_ptr[i].x=i;
        prova_ptr[i].y=i;
        prova_ptr[i].ch='a';
    }
    for(int i=0;i<5;i++){
        prova_adt[i]=(struct prova *) malloc(dim*sizeof (struct prova));
    }
    for(int i=0;i<dim;i++){
        prova_adt[0][i]=prova_adt[1][i]=prova_adt[2][i]=prova_adt[3][i]=prova_adt[4][i]=prova_ptr[i];
    }
    for(int i=0;i<dim;i++){
        printf("%d ",prova_adt[0][i].x  );
    }

}
