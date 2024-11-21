#include <stdio.h>
#include <stdlib.h>

// Node Structure 
struct Node{
    int val;
    struct Node *next;
    struct Node *previous;
};

// Function to allocate memory and make a new Node
struct Node *Create_Node(int val){
    struct Node *newNode = NULL;
    newNode = (struct Node *)malloc(sizeof(struct Node));
    if (!newNode) // If allocation failed
    {
        printf("\nMemory Allocation failed for %d", val);
        exit(1);
    }
    newNode->previous = NULL;
    newNode->next = NULL;
    newNode->val = val;
    return newNode; // get the Node Pointer
}

// fucntion to insert value at the end, must pass address of the Node pointer 
void insert_end(int val, struct Node **head)
{
    struct Node *newNode = Create_Node(val);
    if (*head == NULL) // if the list is empty , just need to set newNode as Head
    {
        *head = newNode; 
        return;
    }
    struct Node *temp = *head;
    while (temp->next != NULL) // traverse the list to find the final Node
    {
        temp = temp->next;
    }
    temp->next = newNode;
    newNode->previous = temp; // setting the "next" as a newly made node as setting its "previous" as the current node 
}

// Function to traverse The list
void print_ll(struct Node *head) 
{
    struct Node *temp = head;
    while (temp != NULL) // if list is not empty
    {
        if (temp->previous != NULL && temp->next!=NULL) // for Node that is between Beginning and END
            printf("\nval: %d, prev: %d, next:%d", temp->val, temp->previous->val,temp->next->val);

        else if(temp->previous==NULL && temp->next!=NULL){ // for Node that is at First But Not the End
            printf("\nval: %d, prev: NULL, next: %d", temp->val,temp->next->val);
        }
        else if(temp->previous==NULL && temp->next==NULL){  // if list has only one element ie. both start and end
            printf("\nval:%d, prev: NULL, next: NULL",temp->val);
        }
        else{ // If the Node is at the End
            printf("\nval: %d, prev: %d, next: NULL",temp->val,temp->previous->val);
        }
        temp = temp->next; // to traverse
    }
    printf("\n");
}

// function to free the memory of malloced pointers and setting to NULL
void freeMemory(struct Node **head)
{
    struct Node *temp = *head;
    struct Node *ttemp;
    while (temp != NULL)
    {
        ttemp = temp; // temporary to temp to hold the value of previous node
        temp = temp->next; 
        free(ttemp); // freeing the memory of previous node and set temp to next Node 
    }
    *head = NULL; 
}

// function to insert integer at the Begining of a list 
void insert_first(struct Node **head, int val){
    struct Node *temp = *head;
    struct Node *newNode = Create_Node(val); // calling the Create_node function to get a memory allocated Node pointer 
    if (*head == NULL){
        *head = newNode; // if its empty just set the new Pointer as head 
        return;
    }

    // setting New Node's next as current Node i.e. current Head as next for new Node
    // setting current Node's previous as New Node 
    // setting the head pointer to point at newNode 
    newNode->next = temp; 
    temp->previous = newNode;
    *head=newNode;
    temp=NULL; // Nullifying the unused pointer (probably unnecessary in this line)
}


// function to remove a Node from the linked List 
void remove_node(int val, struct Node** head){
    if(*head==NULL){ // If the List is empty
        printf("\nEmpty List");
        return;
    }
    struct Node * temp=*head;
    struct Node* del= NULL; // A new Pointer to Store the previous pointer before traversal (currently initialized as NULL )
    del=temp;
    if(temp->val==val){ // if the head is the Node to remove
        *head=temp->next; // Make the head pointer point to its "next" making that new Head
        if(temp->next!=NULL){
            temp->next->previous=NULL; // if its not the last Node set its "next's previous" Node as NULL (i.e. Making the next Node as head)
        }// else the list is empty anyway so there is no "next"
        free(temp); // freeing the memory of the removed Node
        return;
    }
    while(temp!=NULL){ // if the list is not empty
        if(temp->val==val){
            break; // if the value to remove is found 
        }
        del=temp; // set del to current and set current to "next" i.e. making del "previous" for next iteration 
        temp=temp->next;
    }
    if(temp==NULL){
        printf("\n%d not Found\n",val); // if the value does not exist in the List
        return;
    }
    if(temp->previous!=NULL && temp->val==val){ // if its not "head " Node and value is found 
        del->next=temp->next; // setting the "previous " Node's "next" as current Node's "next"
        if(temp->next!=NULL){
            del->next->previous=temp->previous; // if next Node exists set its previous to previous Node (!not current!)
        }
        free(temp); // freeing the removed Node
        return;
    }
}

// function to search for index of a value in the List
int search_index(int val,struct Node* head){
    unsigned int ind_count=0; // initial counter to return 
    if(head==NULL){
        return -1; // EMPTY List
    }
    struct Node* temp=head;
    while(temp!=NULL){ // iterate until the list is Empty
        if(temp->val==val){
            return ind_count; 
        }
        ind_count++; // increment the Counter every iteration 
        temp=temp->next;
    }
    return -404; // Not Found
}

// function to Get the length of the List
int get_size(struct Node* head){
    unsigned int count=0; // counter 
    if(head==NULL){
        return count ; // Empty List
    }
    struct Node* temp= head;
    while(temp!=NULL){ // if not empty loop until it is empty
        count++; // increment counter every iteration
        temp=temp->next;
    }
    return  count;
}

// function to search the value in certain index in the Linked List
int search_value(int index, struct Node* head){
    if(head==NULL){
        printf("\nEmpty List!!");
        exit(1);
    }
    int listSize=get_size(head); // NUll is checked on If condition above this 
    if(listSize<index || index < 0){ // if index is negative or larger than the size of the list
        printf("\nIndex Out of Bounds");
        exit(1); 
    }
    struct Node* temp=head;
    int counter=0;
    while(temp!=NULL && counter<index){ // iterate the list until counter is equal to index
        temp=temp->next;
        counter++;
    }
    return temp->val;
}

void print_tail(struct Node*);

int main()
{
    struct Node *head = NULL;
    insert_end(1, &head);
    insert_end(2, &head);
    insert_end(3, &head);
    insert_end(4, &head);
    insert_end(6, &head);
    insert_first(&head, 7);
    insert_end(1, &head);
    insert_end(2, &head);
    insert_end(8, &head);
    insert_end(10, &head);
    insert_end(5, &head);

    print_ll(head);

    remove_node(7,&head);
    remove_node(4,&head);
    remove_node(5,&head);
    remove_node(69,&head);
    remove_node(2,&head);

    print_ll(head);
    
    int ListSize=get_size(head);
    if(ListSize==0){
        printf("\nEmpty LinekdList!!");
    }
    else{
        printf("\nThe Size of Linked List is %d",ListSize);
    }

    int Searchindex =search_index(2,head);
    switch(Searchindex){
        case -1:
            printf("\nEmpty List");
            break;
        case -404:
            printf("\nValue Not Found in List ");
            break;
        default:
            printf("\nIndex of 2 is %d",Searchindex);
    }
    
    int SearchValue = search_value(3,head);
    printf("\nValue at Index no. 3 is %d\t",SearchValue);

    freeMemory(&head);
    return 0;
}