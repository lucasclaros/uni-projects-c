#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "bt.h"
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

btree_t *btreeCreate(){
    btree_t *t = malloc(sizeof(btree_t));
    t->root = NULL;
    return t;
}

int btreeEmpty(btree_t *t){
    assert(t != NULL);
    if (t->root == NULL)
        return 1;
    return 0;
}

void btreeDestroy(node_t *root){
    if (root != NULL)
    {
        btreeDestroy(root->left);
        btreeDestroy(root->right);
        free(root);
    }
}

void btreePrint(node_t *root){
    if (root != NULL)
    {
        printf("%d(", root->data);
        btreePrint(root->left);
        printf(",");
        btreePrint(root->right);
        printf(")");
    }else printf("NULL");
}

int btreeHeight(node_t *root){
    if (root == NULL)
        return 0;
    int h_left = 1 + btreeHeight(root->left);
    int h_right = 1 + btreeHeight(root->right);
    return MAX(h_left, h_right);
}

node_t *btreeSearch(node_t *root, type x){
    if (root == NULL)
        return NULL;
    
    if (root->data == x)
        return root;
    
    node_t *p = btreeSearch(root->left, x);
    if (p == NULL)
        p = btreeSearch(root->right, x);

    return p;
}

node_t *btreeSearchParent(node_t *root, type x){
    if (root == NULL)
        return NULL;

    if (root->left != NULL && root->left->data == x)
        return root;

    if (root->right != NULL && root->right->data == x)
        return root;

    node_t *p = btreeSearchParent(root->left, x);
    if (p == NULL)
        p = btreeSearchParent(root->right, x);
    
    return p;
}

int btreeInsertLeft(btree_t *t, type x, type parent){
    node_t *p = createNode(x);
    
    if (parent == -1)
    {
        if (t->root == NULL)
            t->root = p;
        else
        {
            free(p);
            return 0;
        }
    }else
    {
        node_t *aux = btreeSearch(t->root, parent);
        if (aux != NULL && aux->left == NULL && aux->data != x) 
            aux->left = p;
        else
        {
            free(p);
            return 0;
        }
    }

    return 1;
}


int btreeInsertRight(btree_t *t, type x, type parent){
    node_t *p = createNode(x);
    
    if (parent == -1)
    {
        if (t->root == NULL)
            t->root = p;
        else
        {
            free(p);
            return 0;
        }
    }else
    {
        node_t *aux = btreeSearch(t->root, parent);
        if (aux != NULL && aux->right == NULL && aux->data != x) 
            aux->right = p;
        else
        {
            free(p);
            return 0;
        }
    }

    return 1;
}

int btreeSumNodes(node_t *root){
    assert(root != NULL);
    int left, right;

    if (root->left == NULL || root->right == NULL)
        return root->data;
        
    left = btreeSumNodes(root->left);
    right = btreeSumNodes(root->right);

    if (root->data == (left+right))
        return root->data;
    else
        return 0;

}

