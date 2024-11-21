#include<stdio.h>
#include<stdlib.h>

struct LinkedList{
    int val;
    struct LinkedList* next;
};

struct LinkedList* Create_Node(int val){
    struct LinkedList* newNode=(struct LinkedList* )malloc(sizeof(struct LinkedList));
    if(!newNode){
        printf("\nMalloc Failed");
        exit(1);
    }
    newNode->val=val;
    newNode->next=NULL;
    return newNode;
}

void add(int val, struct LinkedList** head){
    struct LinkedList* newNode=Create_Node(val);
    if(*head==NULL){
        *head=newNode;
        return;
    }
    struct LinkedList* temp= *head;
    while(temp->next!=NULL){
        temp=temp->next;
    }
    temp->next=newNode;
}

void remove_queue(struct LinkedList** head){
    if(*head==NULL){
        printf("\nEmpty Node!");
        return;
    }
    struct LinkedList* temp=*head;
    *head=temp->next;
    free(temp);
}

void preety_print(struct LinkedList* head){
    if(head==NULL) return;
    while(head!=NULL){
        printf("%d ->\t",head->val);
        head=head->next;
    }
    printf("NULL\n");
}

void free_memory(struct LinkedList** head){
    if(*head==NULL) return;
    struct LinkedList* temp=*head;
    struct LinkedList* ttemp;
    while(temp!=NULL){
        ttemp=temp;
        temp=temp->next;
        free(ttemp);
    }
    free(head);
}

int main(){
    struct LinkedList* head=NULL;
    add(1,&head);
    add(2,&head);
    add(3,&head);
    add(4,&head);
    add(5,&head);
    add(6,&head);
    preety_print(head);
    remove_queue(&head);
    preety_print(head);
    free_memory(&head);

    return 0;
}