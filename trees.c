#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definition for linked list to hold children
struct LinkedList {
    struct TreeNode* node;
    struct LinkedList* next;
}; 

// Definition for tree node
struct TreeNode {
    struct TreeNode* parent;
    struct LinkedList* children;
    int val;
};

void Free_Tree(struct TreeNode* root);

// Function to create a new tree node
struct TreeNode* Create_Tree(int val) {
    struct TreeNode* newNode = (struct TreeNode*) malloc(sizeof(struct TreeNode));
    if (!newNode) {
        printf("\nMalloc Failed!!");
        exit(1);
    }
    newNode->parent = NULL;
    newNode->children = NULL;
    newNode->val = val;
    return newNode;
}

// Helper function to find a node with a given value in the tree
struct TreeNode* Find_Node(struct TreeNode* root, int parentVal) {
    if (root == NULL) return NULL;
    if (root->val == parentVal) return root;
    
    struct LinkedList* childList = root->children;
    while (childList != NULL) {
        struct TreeNode* found = Find_Node(childList->node, parentVal); // DFS
        if (found) return found;
        childList = childList->next;
    }
    return NULL;
}

// Function to insert a child node with value `val` under a parent with value `parentVal`
void Insert_Children(int val, struct TreeNode** root, int parentVal) {
    struct TreeNode* newNode = Create_Tree(val);
    
    // If the tree is empty, set the new node as the root
    if (*root == NULL) {
        *root = newNode;
        return;
    }
    
    // Find the parent node
    struct TreeNode* parentNode = Find_Node(*root, parentVal);
    if (!parentNode) {
        printf("Parent with value %d not found!\n", parentVal);
        free(newNode); // Free the new node if parent is not found
        return;
    }
    
    // Add the new node to the parent's list of children
    newNode->parent = parentNode;
    struct LinkedList* childNode = (struct LinkedList*) malloc(sizeof(struct LinkedList));
    if (!childNode) {
        printf("\nMalloc Failed!!");
        exit(1);
    }
    childNode->node = newNode;
    childNode->next = parentNode->children;
    parentNode->children = childNode;
}

void Print_Tree(struct TreeNode* root, int level) {
    if (root == NULL) return;

    // Print the current node with indentation to represent tree level
    for (int i = 0; i < level; i++) printf("    ");
    printf("Node: %d\n", root->val);

    // Recursively print children
    struct LinkedList* child = root->children;
    while (child != NULL) {
        Print_Tree(child->node, level + 1);
        child = child->next;
    }
}
void Free_Children(struct LinkedList* children) {
    struct LinkedList* temp;
    while (children != NULL) {
        temp = children;
        children = children->next;
        Free_Tree(temp->node);  // Recursively free the child node
        free(temp);  // Free the linked list node
    }
}

// Function to free a tree node and all its descendants
void Free_Tree(struct TreeNode* root) {
    if (root == NULL) return;

    // Free the list of children recursively
    Free_Children(root->children);

    // Free the node itself
    free(root);
}

int main() {
    struct TreeNode* root = NULL;
    
    // Insert nodes into the tree
    Insert_Children(1, &root, -1);  // Root node
    Insert_Children(2, &root, 1);   // Child of root
    Insert_Children(3, &root, 1);   // Another child of root
    Insert_Children(4, &root, 2);   // Child of node with value 2
    Insert_Children(5, &root, 2);   // Another child of node with value 2
    Insert_Children(5, &root, 5); 
    Insert_Children(5, &root, 2); 
    Insert_Children(5, &root, 3); 
    // Print the tree structure
    printf("Tree Structure:\n");
    Print_Tree(root, 0);
    Free_Tree(root);
    return 0;
}
