typedef int type;
typedef struct Node node_t;
typedef struct Tree {
    node_t *root;
} bstree_t;


node_t *createNode(type data);
bstree_t *bstreeCreate();
int bstreeEmpty(bstree_t *t);
void bstreeDestroy(node_t *root);
void bstreePrint(node_t *root);
int bstreeHeight(node_t *root);
node_t *bstreeSearch(node_t *root, type x);
int bstreeInsert(node_t **root, type x);
int bstreeRemove(bstree_t *t);
void bstreePrintPreorder(node_t *root);
void bstreePrintInorder(node_t *root);
void bstreePrintPostorder(node_t *root);
