/**
 *   Author: Lucas da Silva Claros
 *   nUSP: 12682592
 *   Create Time: 29/09/2021 22:30
 *   Modified time: 05/11/2021 04:23
 *   Description:  List Header
 */

#define MAX_SIZE_LIST 100
#define FIRST -1
#define LAST   1
#define MIDDLE 0

typedef enum bool { FALSE, TRUE } bool;
typedef struct List list_t;
typedef struct Node node_t;
typedef int type;

/**
 *  Initializes a list, all variables setted
 */
list_t *listCreate();

/**
 *  Deallocates list pointer 
 * 
 * @param list: list pointer 
 */
void listDestroy (list_t *list);

/**
 *  Get next item in list
 * 
 * @param list: list pointer
 * @return: void * item address
 */
int listRemove (list_t *list, type x);

/**
 *  Checks if the list is full
 * 
 * @param list: list pointer
 * @return: 1 - full
 *          0 - not full
 */
int  listisFull  (list_t *list);

/**
 *  Checks if the list is empty
 * 
 * @param list: list pointer
 * @return: 1 - empty
 *          0 - not empty
 */
int  listisEmpty (list_t *list);

/**
 *  Inserts an item in list
 * 
 * @param list: list pointer
 * @param item: item address
 * @return: 1 - all good
 *         -1 - list full
 */
int  listInsert  (list_t *list, type item);

void  listPrint  (list_t *l);
node_t  *listSearchElement  (list_t *list, type x);
int listElementPosition  (node_t *);
void listRemoveMultiples(list_t *);
void listSumNodes(list_t *src, list_t *dest);
void listCopy(list_t *src, list_t *dest);