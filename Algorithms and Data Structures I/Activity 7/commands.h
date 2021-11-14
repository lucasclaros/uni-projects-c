typedef struct Entry entry_t;
typedef struct skipList sl_t;

typedef enum bool { FALSE, TRUE } bool;


/**
 * Dynamically allocates a line read from stdin
 *
 * @return: char * address allocated
 */
char *readLine(bool *isEOF);


/**
 *  Initializes a entry_t* structure, all variables setted
 *  @return: entry_t* - all good
 *           NULL - unable to allocate memory
 */
entry_t *createEntry(char *word, int id);

/**
 *  Deallocates a entry_t structure 
 * 
 * @param p: poly_t to be destroyed 
 */
void entryDestroy(entry_t *e);

/**
 *  Compares 2 entries id 
 * 
 * @param e1: entry_t* to compare 
 * @param e2: entry_t* to compare
 * @return  : 1 - e1 id < e2 id
 *            0 - e1 id > e2 id
 *           -1 - e1 id = e2 id
 */
int checkContent(entry_t *e1, entry_t *e2);

/**
 *  Reads the operation from stdin
 * 
 * @param sl: sl_t* to work with
 * @return true  -  EOF found
 *         false -  not EOF found, still data to read
 */
bool operationDecider(sl_t *sl);

/**
 *  Reads a new entry from a string formatted like "id name" and 
 * insert into a skip list creating a new entry_t*
 * 
 * @param sl   : sl_t* to insert entry_t*
 * @param infos: string containing the data
 */
void entryInsert(sl_t *sl, char *infos);

/**
 *  Reads a new entry from a string formatted like "name" and 
 * remove from a skip list creating a new entry_t*
 * 
 * @param sl   : sl_t* to insert entry_t*
 * @param infos: string containing the data
 */
void entryRemove(sl_t *sl, char *infos);

/**
 *  Prints a entry_t* formatted like "id, name; "
 * 
 * @param e: entry_t* to be printed 
 */
void entryPrintOne(entry_t *e);