typedef struct Entry entry_t;
typedef struct skipList sl_t;

typedef enum bool { FALSE, TRUE } bool;

char *readLine(bool *isEOF);
entry_t *createEntry(char *word, int id);
void entryDestroy(entry_t *e);
int checkContent(entry_t *e1, entry_t *e2);
bool operationDecider(sl_t *sl);
void entryInsert(sl_t *sl, char *infos);
void entryRemove(sl_t *sl, char *infos);
void entryPrintOne(entry_t *e);