typedef struct Process process_t;
typedef struct Thread thread_t;
typedef struct List list_t;
typedef struct Node node_t;

typedef enum bool { FALSE, TRUE } bool;


/**
 * Dynamically allocates a line read from stdin
 *
 * @return: char * address allocated
 */
char *readLine(bool *isEOF);


/**
 *  Initializes a process_t* structure, all variables setted
 *  @return: process_t* - all good
 *           NULL - unable to allocate memory
 */
process_t *createProcess();

/**
 *  Deallocates a process_t structure 
 * 
 * @param p: poly_t to be destroyed 
 */
void processDestroy(process_t *e);

/**
 *  Compares 2 entries id 
 * 
 * @param p1: process_t* to compare 
 * @param p2: process_t* to compare
 * @return  : 1 - p1 id < p2 id
 *            0 - p1 id > p2 id
 *           -1 - p1 id = p2 id
 */
int checkInsertPriority(process_t *p1, process_t *p2);

int checkPriority(process_t *p1, process_t *p2);
void readProcesses(thread_t *t);
int decreaseQuantum(process_t *p);
int compareTime(process_t *p, int time);
void getProcessbyTime(thread_t *t, int time);

thread_t *threadCreate();
void threadDestroy(thread_t *t);
int threadisEmpty(thread_t *t);

list_t *getMainProcesses(thread_t *t);
node_t *getCurrProcess(thread_t *t);
void updateCurrProcess(thread_t *t);
void processKilled(thread_t *t);