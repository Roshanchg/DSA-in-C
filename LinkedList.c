#include<stdio.h>
#include<stdlib.h>

struct Node{
    int val;
    struct Node* next;
};

struct Node* Create_Node(int val){
    struct Node* newNode=(struct Node*)malloc(sizeof(struct Node));
    if(newNode){
        newNode->val=val;
        newNode->next=NULL;
        return newNode;
    }
    else{
        exit(1);
    }
}

void insert_at_end(int val,struct Node** head){
    struct Node* newNode=Create_Node(val);
    struct Node* temp=*head;
    if(*head==NULL){
        *head=newNode;
        return;
    }
    while(temp->next!=NULL){
        temp=temp->next;
    }
    temp->next=newNode;
}

void insert_at_first(int val,struct Node** head){
    struct Node* newNode=Create_Node(val);
    newNode->next=*head;
    *head=newNode;
}

void remove_node(int val,struct Node** head){
    struct Node* temp=*head;
    struct Node* previous=NULL;
    if(*head==NULL){
        printf("\nNo head");
        return;
    }
    if(temp->val==val){
        *head=temp->next;
        free(temp);
        return;
    }
    previous=temp;
    while(temp!=NULL && temp->val!=val){
        previous=temp;
        temp=temp->next;
    }
    if(temp==NULL){
        printf("\n%d Not Found!!",val);
        return;
    }
    previous->next=temp->next;
    free(temp);
}

void print_ll(struct Node* head){
    struct Node* temp=head;
    printf("\n");
    while(temp!=NULL){
        printf("%d\t",temp->val);
        temp=temp->next;
    }
    printf("NULL");
}

void free_memory_ll(struct Node** head){
    struct Node* temp=*head;
    struct Node* temp2;
    while(temp!=NULL){
        temp2=temp->next;
        free(temp);
        temp=temp2;
    }
    *head=NULL;
    printf("\nMemory Freed! Printing LL NOW: ");
    print_ll(*head);
}

int main(){
    struct Node* head=NULL;
    insert_at_end(2,&head);
    insert_at_end(7,&head);
    insert_at_end(5,&head);
    insert_at_end(6,&head);
    insert_at_end(9,&head);
    insert_at_end(15,&head);
    insert_at_end(21,&head);
    print_ll(head);
    insert_at_first(1,&head);
    print_ll(head);
    remove_node(5,&head);
    print_ll(head);
    free_memory_ll(&head);
    return 0;
}