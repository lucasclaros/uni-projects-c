#define SIZE_QUEUE 100

typedef int elem;

typedef struct queue { 
    int ini, end, total;
    elem queue[SIZE_QUEUE];
} queue_t;

queue_t *createQueue();
void destroy(queue_t *);
int isFull(queue_t *);
int isEmpty(queue_t *);
int insert(queue_t *, elem);
elem remove_elem(queue_t *);
void printQueue(queue_t *);