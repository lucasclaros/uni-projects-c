typedef struct Entry entry_t;
typedef struct skipList sl_t;
typedef int (*operation)(sl_t *sl);


char *read_line();
entry_t *createEntry(char *word, char *desc);
void entryDestroy(entry_t *e);
int checkContent(entry_t *e1, entry_t *e2);
int flipCoin();
int operationDecider(sl_t *sl);
void entryInsert(sl_t *sl);
void entryRemove(sl_t *sl);
void entryChange(sl_t *sl);
void entrySearch(sl_t *sl);
void errorMessage(int i);
void changeDesc(entry_t *e1, entry_t *e2);
int wordStartedWith(entry_t *e1, entry_t *e2);
void entryPrint(entry_t *e);
void entryPrintAll(sl_t *sl);