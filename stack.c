#include<stdio.h>
#include<stdlib.h>

struct LinkedList{
    int val;
    struct LinkedList* next;
};

struct LinkedList* Create_Node(int val){
    struct LinkedList* newNode=(struct LinkedList*) malloc(sizeof(struct LinkedList));
    if(!newNode){
        printf("\nMalloc Failed");
        exit(1);
    }
    newNode->val=val;
    newNode->next=NULL;
    return newNode;
}

void Push(int val, struct LinkedList** head){
    struct LinkedList* newNode=Create_Node(val);
    if(*head==NULL){
        *head=newNode;
        return;
    }
    struct LinkedList* temp=*head;
    newNode->next=temp;
    *head=newNode;   
}

void Pop(struct LinkedList** head){
    if(*head==NULL){
        printf("\nEmpty List!!");
        return;
    }
    struct LinkedList* temp=*head;
    *head=temp->next;
    free(temp);
}

void free_memory(struct LinkedList* head){
    if(head==NULL){
        return;
    }
    free_memory(head->next);
    free(head);    
}

void Preety_Print(struct LinkedList* head){
    while(head!=NULL){
        printf("\t%d ->",head->val);
        head=head->next;
    }
    printf("\tNULL");
}
int main(){
    struct LinkedList* head=NULL;
    Push(1,&head);
    Push(2,&head);
    Push(3,&head);
    Push(4,&head);
    Push(5,&head);
    Push(6,&head);
    Preety_Print(head);
    Pop(&head);
    Preety_Print(head);
    head=NULL;
}