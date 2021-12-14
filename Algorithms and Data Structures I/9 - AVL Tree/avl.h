typedef int type;
typedef struct Node node_t;
typedef struct Tree {
    node_t *root;
} avltree_t;


node_t *createNode(type data);
avltree_t *avltreeCreate();
int avltreeEmpty(avltree_t *t);
void avltreeDestroy(node_t *root);
void avltreePrint(node_t *root);
int avltreeHeight(node_t *root);
node_t *avltreeSearch(node_t *root, type x);
void avltreeInsert(avltree_t *t, type x);
void avltreeRemove(avltree_t *t, type x);
node_t *avltreeLeftBalance(node_t *root, int *height);
node_t *avltreeRightBalance(node_t *root, int *height);
void avltreePrintPreorder(node_t *root);
void avltreePrintInorder(node_t *root);
void avltreePrintPostorder(node_t *root);
node_t *avltreeLeftRotate(node_t *n);
node_t *avltreeRightRotate(node_t *n);
node_t *avltreeLRRotate(node_t *n);
node_t *avltreeRLRotate(node_t *n);
