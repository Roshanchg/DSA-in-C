#include<stdio.h>
#include<stdlib.h>

struct Node{ // make node for list
    int val;
    struct Node* next;
};

struct LinkedList{ // make list
    struct Node* head;
    struct Node* tail;
};

struct LinkedList* init_ll(){ // get a memory allocated list
    struct LinkedList* linkedlist=(struct LinkedList* )malloc(sizeof(struct LinkedList));
    if(!linkedlist){
        printf("\nMalloc failed at LinkedList ");
        exit(1);
    }
    linkedlist->head=NULL;
    linkedlist->tail=NULL;
    return linkedlist;
}

struct Node* Create_Node(int val){ // get a memory allocated Node
    struct Node* newnode=(struct Node*)malloc(sizeof(struct Node));
    if(!newnode){
        printf("\nMalloc Failed at value %d",val);
        exit(1);
    }
    newnode->val=val;
    newnode->next=NULL;
    return newnode;
}

void insert_at_end(struct LinkedList* linkedlist,int val){ // insert at the tail 
    struct Node* newnode=Create_Node(val);
    if(linkedlist->head==NULL){
        linkedlist->head=newnode;
        linkedlist->tail=newnode;
        return;
    }
    linkedlist->tail->next=newnode; // set the previous tail's next as newnode and the new node as list's new tail
    linkedlist->tail=newnode;
}

void print_ll(struct LinkedList* linkedlist){
    if(linkedlist->head==NULL){
        printf("\nNULL");
        return;
    }
    struct Node* head=linkedlist->head;
    printf("\n");
    while(head!=NULL){// iterate whole list
        printf("%d -> ",head->val);
        head=head->next;
    }
    printf("NULL\n");

}

void free_memory(struct LinkedList* linkedlist){
    if(linkedlist==NULL){ // if list is NULL just return
        return;
    }
    if(linkedlist->head==NULL){ // if head is NULL , list is empty so free memory of list and return 
        free(linkedlist);
        linkedlist=NULL;
        return;
    }
    struct Node* head=linkedlist->head;
    struct Node* temp;
    while(head!=NULL){// else iterate through the whole list and free every node
        temp=head;
        head=head->next;
        free(temp);
    }
    free(linkedlist);
}

int main(){
    struct LinkedList* linkedlist=init_ll();
    insert_at_end(linkedlist,1);
    insert_at_end(linkedlist,2);
    insert_at_end(linkedlist,3);
    print_ll(linkedlist);
    free_memory(linkedlist);
    return 0;
}