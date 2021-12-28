#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "treap.h"
#define MAX(x, y) (((x) > (y)) ? (x) : (y))

struct Node
{
    type data;
    int prio;
    node_t *left, *right;
};

node_t *createNode(type data, int prio){
    node_t *newNode = malloc(sizeof(node_t));
    newNode->data = data;
    newNode->prio = prio;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

treap_t *treapCreate(){
    treap_t *t = malloc(sizeof(treap_t));
    t->root = NULL;
    return t;
}

int treapEmpty(treap_t *t){
    assert(t != NULL);
    if (t->root == NULL)
        return 1;
    return 0;
}

void treapDestroy(node_t *root){
    if (root != NULL)
    {
        treapDestroy(root->left);
        treapDestroy(root->right);
        free(root);
    }
}

void treapPrint(node_t *root){
    if (root != NULL)
    {
        printf("%d(", root->data);
        treapPrint(root->left);
        printf(",");
        treapPrint(root->right);
        printf(")");
    }else printf("NULL");
}

int treapHeight(node_t *root){
    if (root == NULL)
        return 0;
    int h_left = 1 + treapHeight(root->left);
    int h_right = 1 + treapHeight(root->right);
    return MAX(h_left, h_right);
}

node_t *treapSearch(node_t *root, type x){
    if (root == NULL) 
        return NULL; 
    else if (root->data == x) 
        return root; 
    else if (x < root->data) 
        return treapSearch(root->left, x);
    else 
        return treapSearch(root->right, x);
}

int treapInsert(node_t **root, type x, int prio){
    if ((*root) == NULL)
    {
        (*root) = createNode(x, prio);
        return 1;
    }else if ((*root)->data == x) 
    {
        printf("Elemento ja existente\n");
        return 0; 
    }
    else if (x < (*root)->data) 
    {
        int result = treapInsert(&(*root)->left, x, prio);
        if ((*root)->left->prio > (*root)->prio)
            (*root) = treapRightRotate((*root));
        return result;

    }else 
    {
        int result = treapInsert(&(*root)->right, x, prio);
        if ((*root)->right->prio > (*root)->prio)
            (*root) = treapLeftRotate((*root));
        return result;
    }
}

int treapRemove(node_t **root, type x){
    if ((*root) == NULL)
        return 0;
    
    if (x < (*root)->data)
        return treapRemove(&(*root)->left, x);
    else if (x > (*root)->data)
        return treapRemove(&(*root)->right, x);
    else if ((*root)->left == NULL)
    {
        node_t *aux = (*root)->right;
        free((*root));
        *root = aux;
    }else if ((*root)->right == NULL)
    {
        node_t *aux = (*root)->left;
        free((*root));
        *root = aux;
    }else if ((*root)->left->prio < (*root)->right->prio)
    {
        (*root) = treapLeftRotate((*root));
        return treapRemove(&(*root)->left, x);
    }else
    {
        (*root) = treapLeftRotate((*root));
        return treapRemove(&(*root)->right, x);
    }
}

void treapPrintPreorder(node_t *root){
    if (root != NULL)
    {
        printf("(%d, %d) ", root->data, root->prio);
        treapPrintPreorder(root->left);
        treapPrintPreorder(root->right);
    }
}

void treapPrintInorder(node_t *root){
    if (root != NULL)
    {
        treapPrintInorder(root->left);
        printf("(%d, %d) ", root->data, root->prio);
        treapPrintInorder(root->right);
    }
}

void treapPrintPostorder(node_t *root){
    if (root != NULL)
    {
        treapPrintPostorder(root->left);
        treapPrintPostorder(root->right);
        printf("(%d, %d) ", root->data, root->prio);
    }
}

node_t *treapLeftRotate(node_t *n){
    node_t *aux = n->right;
    n->right = aux->left;
    aux->left = n;
    return aux;
}

node_t *treapRightRotate(node_t *n){
    node_t *aux = n->left;
    n->left = aux->right;
    aux->right = n;
    return aux;
}

void printLevelOrder(node_t* root)
{
    int h = treapHeight(root);
    int i;
    for (i = 1; i <= h; i++)
        printCurrentLevel(root, i);
}
 
/* Print nodes at a current level */
void printCurrentLevel(node_t* root, int level)
{
    if (root == NULL)
        return;
    if (level == 1)
        printf("(%d, %d) ", root->data, root->prio);
    else if (level > 1) {
        printCurrentLevel(root->left, level - 1);
        printCurrentLevel(root->right, level - 1);
    }
}