#include <stdio.h>
#include <stdlib.h>

typedef struct node *link;

struct node{
    int val;
    link next;
};

link newNode(int val,link next);
void printList(link head);

int main(){
    int val[] = {1,2,3,4,5,6,7,8,9};
    link head1=NULL;
    link head2=NULL;
    int i;
    int n=9;
    for(i=0;i<n;i++){
        if(val[i]%2==0) head1=newNode(val[i],head1);
        else head2=newNode(val[i],head2);
    }
    printList(head1);
    printList(head2);
    return 0;
}

link newNode(int val,link next){
    link new = malloc(sizeof *new);
    if(new==NULL){
        return NULL;
    }else{
        new->next=next;
        new->val=val;
    }
    return new;
}

void printList(link head){
    printf("\n");
    link tmp=head;
    while(tmp->next!=NULL){
        printf("%d->",tmp->val);
        tmp=tmp->next;
    }
    printf("%d",tmp->val);
}
