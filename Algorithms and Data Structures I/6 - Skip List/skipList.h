/**
 *   Author: Lucas da Silva Claros
 *   nUSP: 12682592
 *   Create Time: 06/11/2021 03:19
 *   Modified time: 10/11/2021 06:59
 *   Description:  Skip List Header
 */

#define MAX_LEVELS 2556489789786
#define FIRST -1
#define LAST   1
#define MIDDLE 0

typedef enum bool { FALSE, TRUE } bool;
typedef struct skipList sl_t;
typedef struct Node node_t;
typedef int type;

/**
 *  Initializes a list, all variables setted
 */
sl_t *slCreate();

/**
 *  Deallocates list pointer 
 * 
 * @param list: list pointer 
 */
void slDestroy (sl_t *list);

/**
 *  Checks if the list is full
 * 
 * @param list: list pointer
 * @return: 1 - full
 *          0 - not full
 */
int  slisFull  (sl_t *list);

/**
 *  Checks if the list is empty
 * 
 * @param list: list pointer
 * @return: 1 - empty
 *          0 - not empty
 */
int  slisEmpty (sl_t *list);

node_t *slCreateNode(type data, int level);
int slRemove(sl_t *l, type data);
int slInsert(sl_t *l, type data);
type slSearch(sl_t *l, type data);
int generateLevel(int maxValue);
void slPrint(sl_t *sl);