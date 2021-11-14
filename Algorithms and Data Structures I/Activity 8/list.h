/**
 *   Author: Lucas da Silva Claros
 *   nUSP: 12682592
 *   Create Time: 29/09/2021 22:30
 *   Modified time: 14/11/2021 15:35
 *   Description:  List Header
 */

#define MAX_SIZE_LIST 100
#define FIRST -1
#define MIDDLE 0
#define LAST   1

typedef enum bool { FALSE, TRUE } bool;
typedef struct List list_t;
typedef struct Node node_t;
typedef int type;

/**
 *  Initializes a list, all variables setted
 *  @return: list_t* - all good
 *           NULL    - unable to allocate memory
 */
list_t *listCreate();

/**
 *  Deallocates list pointer 
 * 
 * @param list: list pointer 
 */
void listDestroy (list_t *list);

/**
 *  Removes an element in list
 * 
 * @param list   : list pointer
 * @param element: element to remove
 * @return       : 1 - all good
 *                 0 - list null or list empty
 *                -1 - list doesnt contain element
 */
int listRemove (list_t *list, type element);

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
 *  Inserts an item at the end of a list
 * 
 * @param list: list pointer
 * @param item: item address
 * @return: 1 - all good
 *         -1 - list full
 */
int  listInsert  (list_t *list, type item);

/**
 *  Makes a copy list from a given list
 * 
 * @param src : list to be copied
 * @param dest: destination list where src content will be copied
 * @return: 1 - all good
 *          0 - src is null
 */
int listCopy(list_t *src, list_t *dest);

/**
 *  Prints a entire list
 * 
 * @param l: list to be print
 */
void  listPrint  (list_t *l);

/**
 *  Search the element in a list
 * 
 * @param list   : search list
 * @param element: element to searh
 * @return       : node_t* - element found
 *                 NULL - element not found
 */
node_t  *listSearchElement  (list_t *list, type element);

/**
 *  Check a node position
 * 
 * @param node: node_t * to check its position in your list
 * @return    : -1 - node is the first element 
 *               0 - node is at a middle position
 *               1 - node is the last element
 */
int listElementPosition  (node_t *node);


/**
 *  Sums the dest content nodes with src content nodes
 * 
 * @param src : list where nodes to be copied 
 * @param dest: destination list where src content will be added
 */
void listSumNodes(list_t *src, list_t *dest);