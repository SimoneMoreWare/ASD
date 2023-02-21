#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int val;
    struct Node *next;
} Node;

typedef Node *link;
typedef link List;

link inserireinlista1(link head,int cnt,int val){
    link x = malloc(sizeof*x);

    x->val=val;

    link att=head->next;
    link pred=head;
    for(int i=0;i<cnt;i++){
        pred=att;
        att=att->next;
    }

    pred->next=x;
    x->next=att;

    return head;

}

link eliminavalorelista2(link head){
    link tmp = head;
    head=head->next;
    free(tmp);
    return head;
}

void splice (List L1, List *L2, int start, int num){

    link tmp1 = L1;
    //link tmp2 = L2;
    int valoredainserire;
    int cnt1=0;
    int cnteliminati=0;
    while(tmp1!=NULL){
        if(cnt1>=start && cnteliminati<num){
            valoredainserire = (*L2)->val;
            L1=inserireinlista1(L1,cnt1,valoredainserire);
            (*L2)=eliminavalorelista2(*L2);
            cnteliminati++;
        }
        cnt1++;
        tmp1=tmp1->next;
    }
}




int main() {
    List L1 = malloc(sizeof(Node));
    L1->val = 1;
    L1->next = malloc(sizeof(Node));
    L1->next->val = 3;
    L1->next->next = malloc(sizeof(Node));
    L1->next->next->val = 5;
    L1->next->next->next = malloc(sizeof(Node));
    L1->next->next->next->val = 7;
    L1->next->next->next->next = NULL;

    List L2 = malloc(sizeof(Node));
    L2->val = 7;
    L2->next = malloc(sizeof(Node));
    L2->next->val = 4;
    L2->next->next = malloc(sizeof(Node));
    L2->next->next->val = 9;
    L2->next->next->next = NULL;

    splice(L1, &L2, 1, 2);

    printf("L1 = ");
    for (link tmp = L1; tmp != NULL; tmp = tmp->next) {
        printf("%d ", tmp->val);
    }
    printf("\n");

    printf("L2 = ");
    for (link tmp = L2; tmp != NULL; tmp = tmp->next) {
        printf("%d ", tmp->val);
    }
    printf("\n");

    return 0;
}
