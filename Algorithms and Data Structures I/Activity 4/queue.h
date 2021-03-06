/**
 *   Author: Lucas da Silva Claros
 *   nUSP: 12682592
 *   Create Time: 19/09/2021 22:30
 *   Modified time: 26/09/2021 18:33
 *   Description: Queue Header
 */

#define SIZE_QUEUE 100

typedef struct Queue { 
    int ini, end, total;
    void **queue;
} queue_t;

/**
 *  Initializes a queue, all variables setted
 */
queue_t *queueCreate();

/**
 *  Deallocates queue pointer 
 * 
 * @param queue: queue pointer 
 */
void queueDestroy (queue_t *queue);

/**
 *  Get next item in queue
 * 
 * @param queue: queue pointer
 * @return: void * item address
 */
void *queueRemove (queue_t *queue);

/**
 *  Checks if the queue is full
 * 
 * @param queue: queue pointer
 * @return: 1 - full
 *          0 - not full
 */
int  queueisFull  (queue_t *queue);

/**
 *  Checks if the queue is empty
 * 
 * @param queue: queue pointer
 * @return: 1 - empty
 *          0 - not empty
 */
int  queueisEmpty (queue_t *queue);

/**
 *  Inserts an item in queue
 * 
 * @param queue: queue pointer
 * @param item: item address
 * @return: 1 - all good
 *         -1 - queue full
 */
int  queueInsert  (queue_t *queue, void *item);