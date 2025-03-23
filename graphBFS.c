#include<stdio.h>
#include<stdlib.h>


struct Node {
    int val;
    struct Node** conn;
    int connSize;
};

struct Graphs {
    struct Node* head;
    struct Graphs* next;
};

struct linkedlist{
    struct Node* node;
    struct linkedlist* next;
};

struct Node* create_node(int val) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (!newNode) {
        perror("NODE Malloc Failed");
        exit(-1);
    }
    newNode->val = val;
    newNode->conn = NULL;
    newNode->connSize = 0;
    return newNode;
}

struct Graphs* Graph(int val) {
    struct Graphs* newGraph = (struct Graphs*)malloc(sizeof(struct Graphs));
    if (!newGraph) {
        perror("GRAPH Malloc Failed");
        exit(-1);
    }
    newGraph->head = create_node(val);
    newGraph->next = NULL;
    return newGraph;
}

// Helper to find a node in the graph
struct Node* find_node(struct Graphs* graph, int val) {
    while (graph) {
        if (graph->head->val == val) {
            return graph->head;
        }
        graph = graph->next;
    }
    return NULL;
}

// Helper to add a node to the graph
void add_node(struct Graphs** graph, int val) {
    struct Graphs* newGraph = Graph(val);
    newGraph->next = *graph;
    *graph = newGraph;
}

void add_conn(struct Graphs** graph, int parentVal, int connVal) {
    if (*graph == NULL) {
        add_node(graph, parentVal);
    }

    struct Node* parentNode = find_node(*graph, parentVal);
    if (parentNode == NULL) {
        add_node(graph, parentVal);
        parentNode = find_node(*graph, parentVal);
    }

    struct Node* connNode = find_node(*graph, connVal);
    if (connNode == NULL) {
        add_node(graph, connVal);
        connNode = find_node(*graph, connVal);
    }

    // Resize and add the connection
    parentNode->conn = (struct Node**)realloc(parentNode->conn, (parentNode->connSize + 1) * sizeof(struct Node*));
    if (!parentNode->conn) {
        perror("Realloc Failed");
        exit(-1);
    }
    parentNode->conn[parentNode->connSize++] = connNode;
}

// Print the graph connections
void print_graph(struct Graphs* graph) {
    while (graph) {
        printf("Node %d: ", graph->head->val);
        for (int i = 0; i < graph->head->connSize; i++) {
            printf("%d ", graph->head->conn[i]->val);
        }
        printf("\n");
        graph = graph->next;
    }
}

struct linkedlist* make_queue(struct Node* node){
    struct linkedlist* newqueue=(struct linkedlist* )malloc(sizeof(struct linkedlist));
    if(!newqueue){
        perror("MALLOC FAILED AT queue ");
        exit(-1);
    }
    newqueue->node=node;
    newqueue->next=NULL;
    return newqueue;
}

void preety_print(struct linkedlist* queue){
    if(queue->next!=NULL){
        printf("%d->\t",queue->node->val);
        queue=queue->next;
    }
    printf("NULL\n");
}

void enqueue(struct linkedlist** head,struct Node* node){
    struct linkedlist* newNode=make_queue(node);
    if(*head==NULL){
        *head=newNode;
        return;
    }
    struct linkedlist* temp=*head;
    while(temp->next!=NULL){
        temp=temp->next;
    }
    temp->next=newNode;
}

void dequeue(struct linkedlist** head){
    if(*head==NULL){
        return;
    }
    struct linkedlist* temp=*head;
    *head=(*head)->next;
    free(temp);
    temp=NULL;
}

struct Node* getFirst(struct linkedlist* queue){
    if(queue==NULL){printf("NULL queue");return NULL;}
    return queue->node;
}

void free_queue(struct linkedlist** queue){
    if(*queue==NULL){
        return;
    }
    struct linkedlist* head=*queue;
    struct linkedlist* temp=head;
    while(head->next!=NULL){
        temp=head;
        head=head->next;
        free(temp);
    }
    free(head);
    head=NULL;
    temp=NULL;
    free(queue);
    queue=NULL;
}


int isEmpty(struct linkedlist** queue){return (queue==NULL || *queue==NULL);}

int getTotalNodes(struct Graphs* graph){
    int i=0;
    if(graph==NULL){return i;}
    while(graph!=NULL){
        i++;
        graph=graph->next;
    }
    return i;
}



void bfs(struct Graphs* graph,int search){
    struct linkedlist* queue=NULL;
    if(graph==NULL){
        perror("EMPTY GRAPH");
        return;
    }

    struct Node* head=graph->head;
    if(head==NULL){
        perror("NO HEAD OF GRAPH");
        return ;
    }

    struct Node* temp=head;
    int i=0;
    int graphSize=getTotalNodes(graph);
    enqueue(&queue,temp);
    while(1){
        temp=getFirst(queue);
        dequeue(&queue);
        if(temp->val==search){
            printf("\nValue Found");
            free_queue(&queue);
            return;
        }
        for(int j=0;j<temp->connSize;j++){
            enqueue(&queue,temp->conn[j]);
        }
        preety_print(queue);
        if(isEmpty(&queue)){
            break;
        }
        if(i>graphSize){
            break;
        }
        i++;
    }
    printf("\nNOT FOUND ");
    free_queue(&queue);
}

int main() {
    struct Graphs* graph = NULL;

    add_conn(&graph, 1, 2);
    add_conn(&graph, 1, 3);
    add_conn(&graph, 2, 4);
    add_conn(&graph, 3, 5);
    add_conn(&graph, 4, 1);
    add_conn(&graph, 5, 2);
    print_graph(graph);
    bfs(graph,7);
    return 0;
}
