#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "avl.h"
#define MAX(x, y) (((x) > (y)) ? (x) : (y))

node_t *avlInsert(node_t *root, type x, int *flag);
node_t *avlRemove(node_t *root, type x, int *flag);
node_t *removeSearch(node_t *root, node_t *key, int *height);

struct Node
{
    type data;
    node_t *left, *right;
    int bf;
};

node_t *createNode(type data){
    node_t *newNode = malloc(sizeof(node_t));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->bf = 0;
    return newNode;
}

avltree_t *avltreeCreate(){
    avltree_t *t = malloc(sizeof(avltree_t));
    t->root = NULL;
    return t;
}

int avltreeEmpty(avltree_t *t){
    assert(t != NULL);
    if (t->root == NULL)
        return 1;
    return 0;
}

void avltreeDestroy(node_t *root){
    if (root != NULL)
    {
        avltreeDestroy(root->left);
        avltreeDestroy(root->right);
        free(root);
    }
}

void avltreePrint(node_t *root){
    if (root != NULL)
    {
        printf("%d(", root->data);
        avltreePrint(root->left);
        printf(",");
        avltreePrint(root->right);
        printf(")");
    }else printf("NULL");
}

int avltreeHeight(node_t *root){
    if (root == NULL)
        return 0;
    int h_left = 1 + avltreeHeight(root->left);
    int h_right = 1 + avltreeHeight(root->right);
    return MAX(h_left, h_right);
}

node_t *avltreeSearch(node_t *root, type x){
    if (root == NULL) 
        return NULL; 
    else if (root->data == x) 
        return root; 
    else if (x < root->data) 
        return avltreeSearch(root->left, x);
    else 
        return avltreeSearch(root->right, x);
}

void avltreeInsert(avltree_t *t, type x){
    int flag = 0;
    t->root = avlInsert(t->root, x, &flag);
}

node_t *avlInsert(node_t *root, type x, int *flag){
    if (root != NULL)
    {
        if (x < root->data)
        {
            root->left = avlInsert(root->left, x, flag);
            if (*flag == 1)
            {
                switch (root->bf)
                {
                    case -1:
                        root->bf = 0;
                        *flag = 0;
                        break;
                    case 0:
                        root->bf = 1;
                        *flag = 1;
                        break;
                    case 1:
                        if (root->left->bf == 1)
                        {
                            root = avltreeRightRotate(root);
                            root->right->bf = 0;
                            root->bf = 0;
                        }else 
                        {
                            root = avltreeLRRotate(root);
                            if(root->bf == -1)
                            {
                                root->left->bf = 1;
                                root->right->bf = 0;
                                root->bf = 0;
                            }
                            else if (root->bf == 0)
                            {
                                root->left->bf = 0;
                                root->right->bf = 0;
                                root->bf = 0;
                            }else
                            {
                                root->left->bf = 0;
                                root->right->bf = -1;
                                root->bf = 0;
                            }
                        }
                        *flag = 0;
                        break;
                    
                    default:
                        break;
                }
            }
        }else if (x > root->data)
        {
            root->right = avlInsert(root->right, x, flag);
            if (*flag == 1)
            {
                switch (root->bf)
                {
                    case 1:
                        root->bf = 0;
                        *flag = 0;
                        break;
                    case 0:
                        root->bf = -1;
                        *flag = 1;
                        break;
                    case -1:
                        if (root->right->bf == -1)
                        {
                            root = avltreeLeftRotate(root);
                            root->left->bf = 0;
                            root->bf = 0;
                        }else 
                        {
                            root = avltreeRLRotate(root);
                            if(root->bf == -1)
                            {
                                root->left->bf = 1;
                                root->right->bf = 0;
                                root->bf = 0;
                            }
                            else if (root->bf == 0)
                            {
                                root->left->bf = 0;
                                root->right->bf = 0;
                                root->bf = 0;
                            }else
                            {
                                root->left->bf = 0;
                                root->right->bf = -1;
                                root->bf = 0;
                            }
                        }
                        *flag = 0;
                        break;
                    
                    default:
                        break;
                }
            }
        }else printf("Elemento ja existente!\n");
        
    }else 
    {
        root = createNode(x);
        *flag = 1;
    }
    
    return root;
}


void avltreeRemove(avltree_t *t, type x){
    int flag = 0;
    t->root = avlRemove(t->root, x, &flag);
}

node_t *avlRemove(node_t *root, type x, int *height){
    node_t *aux;
    if (root == NULL)
    {
        printf("Chave nao foi encontrada!\n");
        *height = 0;
    } else if (x < root->data)
    {
        root->left = avlRemove(root->left, x, height);
        if (*height == 1)
        {
            root = avltreeLeftBalance(root, height);
        }
    }else if (x > root->data)
    {
        root->right = avlRemove(root->right, x, height);
        if (*height == 1)
        {
            root = avltreeRightBalance(root, height);
        }
    }else
    {
        if (root->right == NULL)
        {
            aux = root;
            root = root->left;
            free(aux);
            *height = 1;
        }else if (root->left == NULL)
        {
            aux = root;
            root = root->right;
            free(aux);
            *height = 1;
        }else
        {
            root->left = removeSearch(root->left, root, height);
            if (*height == 1)
                root = avltreeLeftBalance(root, height);
        }
    }
    return root;
}

node_t *removeSearch(node_t *root, node_t *key, int *height){
    node_t *aux;

    if (root->right != NULL) 
    {
        root->right = removeSearch(root->right, key, height);
        if(*height == 1)
            root = avltreeRightBalance(root, height);  
    }
    else
    {
        key->data = root->data;
        aux = root;
        root = root->left;
        free(aux);
        *height = 1;
    }
    return root;
}

node_t *avltreeLeftBalance(node_t *root, int *height){
    switch (root->bf)
    {
        case 1:
            root->bf = 0;
            break;
        case 0:
            root->bf = -1;
            *height = 0;
            break;
        case -1:
            if (root->right->bf <= 0)
            {
                root = avltreeLeftRotate(root);
                if (root->bf == 0)
                {
                    root->left->bf = -1;
                    root->bf = 1;
                    *height = 0;
                }else{
                    root->left->bf = 0;
                    root->bf = 0;
                }
            }else 
            {
                root = avltreeRLRotate(root);
                if (root->bf == 1)
                {   
                    root->left->bf = 0;
                    root->right->bf = -1;
                }else if (root->bf == -1)
                {
                    root->left->bf = 1;
                    root->right->bf = 0;
                }else 
                {
                    root->left->bf = 0;
                    root->right->bf = 0;
                }
                root->bf = 0;
            }
            break;
        default:
            break;
    }
    return root;
}

node_t *avltreeRightBalance(node_t *root, int *height){
    switch (root->bf)
    {
        case -1:
            root->bf = 0;
            break;
        case 0:
            root->bf = 1;
            *height = 0;
            break;
        case 1:
            if (root->left->bf >= 0)
            {
                root = avltreeRightRotate(root);
                if (root->bf == 0)
                {
                    root->right->bf = 1;
                    root->bf = -1;
                    *height = 0;
                }else{
                    root->right->bf = 0;
                    root->bf = 0;
                }
            }else 
            {
                root = avltreeLRRotate(root);
                if (root->bf == 1)
                {   
                    root->left->bf = 0;
                    root->right->bf = -1;
                }else if (root->bf == -1)
                {
                    root->left->bf = 1;
                    root->right->bf = 0;
                }else 
                {
                    root->left->bf = 0;
                    root->right->bf = 0;
                }
                root->bf = 0;
            }
            break;
        default:
            break;
    }
    return root;
}

void avltreePrintPreorder(node_t *root){
    if (root != NULL)
    {
        printf("%d ", root->data);
        avltreePrintPreorder(root->left);
        avltreePrintPreorder(root->right);
    }
}

void avltreePrintInorder(node_t *root){
    if (root != NULL)
    {
        avltreePrintInorder(root->left);
        printf("%d ", root->data);
        avltreePrintInorder(root->right);
    }
}

void avltreePrintPostorder(node_t *root){
    if (root != NULL)
    {
        avltreePrintPostorder(root->left);
        avltreePrintPostorder(root->right);
        printf("%d ", root->data);
    }
}

node_t *avltreeLeftRotate(node_t *n){
    node_t *aux = n->right;
    n->right = aux->left;
    aux->left = n;
    return aux;
}

node_t *avltreeRightRotate(node_t *n){
    node_t *aux = n->left;
    n->left = aux->right;
    aux->right = n;
    return aux;
}

node_t *avltreeLRRotate(node_t *n){
    n->left = avltreeLeftRotate(n->left);
    return avltreeRightRotate(n);
}

node_t *avltreeRLRotate(node_t *n){
    n->right = avltreeRightRotate(n->right);
    return avltreeLeftRotate(n);
}
