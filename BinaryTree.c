#include<stdio.h>
#include<stdlib.h>

struct TreeNode{
    int val;
    struct TreeNode* left;
    struct TreeNode* right;
};

struct TreeNode* Create_Node(int val){
    struct TreeNode* newNode=(struct TreeNode*) malloc(sizeof(struct TreeNode));
    if(!newNode){
        printf("\nMalloc Failed");
        exit(1);
    }
    newNode->val=val;
    newNode->left=NULL;
    newNode->right=NULL;
    return newNode;
}

void Insert_Node(struct TreeNode** root,int val){
    struct TreeNode* newNode=Create_Node(val);
    if(*root==NULL){
        *root=newNode;
        return;
    }
    struct TreeNode* temp=*root;
    while(temp!=NULL){
        if(temp->val==val){
            printf("\n%d already Exists in the Tree!!",val);
            return;
        }
        if(temp->val<val ){
            if(temp->right==NULL){
                temp->right=newNode;
                break;
            }
            temp=temp->right;
            continue;
        }
        else{
            if(temp->left==NULL){
                temp->left=newNode;
                break;
            }
            temp=temp->left;
            continue;
        }
    }
}


void InOrder_Traversal(struct TreeNode* root){
    if(root==NULL) return;
    InOrder_Traversal(root->left);
    printf("%d\t",root->val);
    InOrder_Traversal(root->right);
    return;
}

void free_memory(struct TreeNode* root){
    if(root==NULL) return;
    free_memory(root->left);
    free_memory(root->right);
    free(root);
}

int Get_Height(struct TreeNode* root){
    if (root==NULL) return 0;
    int left=Get_Height(root->left);
    int right=Get_Height(root->right);
    return (1+((left>right)?left:right));
}

int main(){
    struct TreeNode* root=NULL;
    Insert_Node(&root,11);
    Insert_Node(&root,9);
    Insert_Node(&root,10);
    Insert_Node(&root,7);
    Insert_Node(&root,8);
    Insert_Node(&root,6);
    Insert_Node(&root,14);
    Insert_Node(&root,16);
    Insert_Node(&root,12);
    InOrder_Traversal(root);
    printf("\n");
    printf("%d",Get_Height(root));
    free_memory(root);
    root=NULL;
    return 0;
}