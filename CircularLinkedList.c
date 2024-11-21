#include <stdio.h>
#include <stdlib.h>

struct CircularLinkedList {
    struct Node *head;
    struct Node *tail;
};

struct Node {
    int val;
    struct Node *next;
};

struct Node *Create_Node(int val) {
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    if (!newNode) {
        printf("\nMalloc Failed to create Node of Val: %d", val);
        exit(1);
    }
    newNode->val = val;
    newNode->next = NULL;
    return newNode;
}

struct CircularLinkedList *Init_LL() {
    struct CircularLinkedList *linkedList = (struct CircularLinkedList *)malloc(sizeof(struct CircularLinkedList));
    if (!linkedList) {
        printf("\nMalloc Failed to Init LL");
        exit(1);
    }
    linkedList->head = NULL;
    linkedList->tail = NULL;
    return linkedList;
}

void Insert_At_End(struct CircularLinkedList *linkedList, int val) {
    struct Node *newNode = Create_Node(val);
    if (linkedList->head == NULL) {
        linkedList->head = newNode;
        linkedList->tail = newNode;
        newNode->next = newNode; // Point to itself
        return;
    }
    linkedList->tail->next = newNode;
    linkedList->tail = newNode;
    newNode->next = linkedList->head; // Maintain circular structure
}

void Print_LinkedList(struct CircularLinkedList *linkedList) {
    if (linkedList->head == NULL) {
        printf("\nList is empty.\n");
        return;
    }
    struct Node *current = linkedList->head;
    printf("\n");
    do {
        printf("%d -> ", current->val);
        current = current->next;
    } while (current != linkedList->head); // Stop when we reach the head again
    printf("(back to head)\n");
}

void free_memory(struct CircularLinkedList *linkedList) {
    if (linkedList->head == NULL) {
        free(linkedList);
        return;
    }
    struct Node *current = linkedList->head;
    struct Node *temp;
    do {
        temp = current;
        current = current->next;
        free(temp);
    } while (current != linkedList->head);
    free(linkedList);
    linkedList = NULL;
}

int main() {
    struct CircularLinkedList *linkedList = Init_LL();
    Insert_At_End(linkedList, 1);
    Insert_At_End(linkedList, 2);
    Insert_At_End(linkedList, 3);
    Print_LinkedList(linkedList);
    free_memory(linkedList);
    return 0;
}
