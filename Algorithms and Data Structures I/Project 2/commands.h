typedef enum bool { FALSE, TRUE } bool;
typedef struct Tree bstree_t;

bool operationDecider(bstree_t *t);
char *readLine(bool *isEOF);
void entryInsert(bstree_t *t, char *infos);
void entryPrint(bstree_t *t, char *infos);