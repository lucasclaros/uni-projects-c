typedef int type;
typedef struct Node node_t;
typedef struct Tree {
    node_t *root;
} treap_t;


node_t *createNode(type data, int prio);
treap_t *treapCreate();
int treapEmpty(treap_t *t);
void treapDestroy(node_t *root);
void treapPrint(node_t *root);
int treapHeight(node_t *root);
node_t *treapSearch(node_t *root, type x);
int treapInsert(node_t **root, type x, int prio);
int treapRemove(node_t **root, type x);
void treapPrintPreorder(node_t *root);
void treapPrintInorder(node_t *root);
void treapPrintPostorder(node_t *root);
node_t *treapLeftRotate(node_t *n);
node_t *treapRightRotate(node_t *n);
