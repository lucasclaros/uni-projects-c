#define SIZE_STACK 100

typedef int elem;
typedef struct stack stack_t;

stack_t *create  ();
void printStack  (stack_t *);
void destroy     (stack_t *);
int  isFull      (stack_t *);
int  isEmpty     (stack_t *);
void  *pop         (stack_t *);
int  push        (stack_t *, void *);
int  top         (stack_t *, void **);