typedef int type;
typedef struct Node node_t;
typedef struct Tree {
    node_t *root;
} btree_t;


node_t *createNode(type data);
btree_t *btreeCreate();
int btreeEmpty(btree_t *t);
void btreeDestroy(node_t *t);
void btreePrint(node_t *root);
int btreeHeight(node_t *root);
node_t *btreeSearch(node_t *root, type x);
node_t *btreeSearchParent(node_t *root, type x);
int btreeInsertLeft(btree_t *t, type x, type parent);
int btreeInsertRight(btree_t *t, type x, type parent);
int btreeRemove(btree_t *t);
int btreeSumNodes(node_t *root);

