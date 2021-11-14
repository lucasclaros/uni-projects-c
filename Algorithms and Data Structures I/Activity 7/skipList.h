/**
 *   Author: Lucas da Silva Claros
 *   nUSP: 12682592
 *   Create Time: 06/11/2021 03:19
 *   Modified time: 14/11/2021 16:10
 *   Description:  Skip List Header
 */

#define MAX_LEVELS 25
#define FRACTIONS 0.25
#define FIRST -1
#define LAST   1
#define MIDDLE 0

typedef struct Entry entry_t;
typedef struct skipList sl_t;
typedef struct Node node_t;
typedef entry_t* type;

/**
 *  Initializes a skip list, all variables setted
 * 
 * @return : sl_t * - all good
 *           NULL   - unable to allocate memory 
 */
sl_t *slCreate();

/**
 *  Deallocates skip list struct
 * 
 * @param sl: sl_t* to be destroyed
 */
void slDestroy (sl_t *sl);

/**
 *  Create a new skip list node, all variables setted and allocated 
 * 
 * @param data : data to be stored in node
 * @param level: node level in skip list
 * @return     : node_t* - all good
 *               NULL    - unable to allocate memory 
 */
node_t *slCreateNode(type data, int level);

/**
 *  Removes an element in a skip list
 * 
 * @param sl  : sl_t* to remove element
 * @param data: element to be removed
 * @return    : 1 - all good
 *              0 - element not found
 */
int slRemove(sl_t *sl, type data);

/**
 *  Inserts an element in a skip list (repetitions not allowed)
 * 
 * @param sl  : sl_t* to insert element
 * @param data: element to be inserted
 * @return    : 1 - all good
 *              0 - element already added
 */
int slInsert(sl_t *sl, type data);

/**
 *  Search an element in a skip list
 * 
 * @param sl  : sl_t* to search element
 * @param data: element to be searched
 * @return    : node_t* - all good
 *              NULL    - sl null or element not found
 */
node_t *slSearch(sl_t *sl, type data);

/**
 *  Prints a skip list (if it's null, prints "VAZIA")
 * 
 * @param sl: sl_t* to be printed
 */
void slPrint(sl_t *sl);

/**
 *  Flipcoin function for skip list 
 * 
 * @return: int - number in range of 0-MAX_LEVELS
 */
int generateLevel();