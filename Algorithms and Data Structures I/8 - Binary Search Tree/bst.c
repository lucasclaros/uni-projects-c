#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "bst.h"
#define MAX(x, y) (((x) > (y)) ? (x) : (y))

struct Node
{
    type data;
    node_t *left, *right;
};

node_t *createNode(type data){
    node_t *newNode = malloc(sizeof(node_t));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

bstree_t *bstreeCreate(){
    bstree_t *t = malloc(sizeof(bstree_t));
    t->root = NULL;
    return t;
}

int bstreeEmpty(bstree_t *t){
    assert(t != NULL);
    if (t->root == NULL)
        return 1;
    return 0;
}

void bstreeDestroy(node_t *root){
    if (root != NULL)
    {
        bstreeDestroy(root->left);
        bstreeDestroy(root->right);
        free(root);
    }
}

void bstreePrint(node_t *root){
    if (root != NULL)
    {
        printf("%d(", root->data);
        bstreePrint(root->left);
        printf(",");
        bstreePrint(root->right);
        printf(")");
    }else printf("NULL");
}

int bstreeHeight(node_t *root){
    if (root == NULL)
        return 0;
    int h_left = 1 + bstreeHeight(root->left);
    int h_right = 1 + bstreeHeight(root->right);
    return MAX(h_left, h_right);
}

node_t *bstreeSearch(node_t *root, type x){
    if (root == NULL) 
        return NULL; 
    else if (root->data == x) 
        return root; 
    else if (x < root->data) 
        return bstreeSearch(root->left, x);
    else 
        return bstreeSearch(root->right, x);
}

int bstreeInsert(node_t **root, type x){
    if ((*root) == NULL)
    {
        (*root) = createNode(x);
        return 1;
    }else if ((*root)->data == x) 
        return 0; 
    else if (x < (*root)->data) 
        return bstreeInsert(&(*root)->left, x);
    else 
        return bstreeInsert(&(*root)->right, x);
}



int bstreeRemove(bstree_t *t){
    return 0;
}
void bstreePrintPreorder(node_t *root){
    if (root != NULL)
    {
        printf("%d ", root->data);
        bstreePrintPreorder(root->left);
        bstreePrintPreorder(root->right);
    }
}

void bstreePrintInorder(node_t *root){
    if (root != NULL)
    {
        bstreePrintInorder(root->left);
        printf("%d ", root->data);
        bstreePrintInorder(root->right);
    }
}

void bstreePrintPostorder(node_t *root){
    if (root != NULL)
    {
        bstreePrintPostorder(root->left);
        bstreePrintPostorder(root->right);
        printf("%d ", root->data);
    }
}

