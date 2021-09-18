#define SIZE_QUEUE 100

typedef struct queue queue_t;

queue_t *createQueue();
void destroy(queue_t *);
int isFull(queue_t *);
int isEmpty(queue_t *);
int insert(queue_t *, void *);
void *remove_elem(queue_t *);
void printQueue(queue_t *);