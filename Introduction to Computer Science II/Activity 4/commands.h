typedef enum bool {FALSE, TRUE} bool;
typedef struct List list_t;

void readWords(char *filename, list_t *l);
char *readLine();
char *readLineFile();
int checkInsertPrio(char *w1, char *w2);