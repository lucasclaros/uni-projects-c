#define SIZE_STACK 100

typedef char elem;
typedef struct stack stack_t;

stack_t *create  ();
void printStack  (stack_t *);
void destroy     (stack_t *);
int  isFull      (stack_t *);
int  isEmpty     (stack_t *);
elem pop         (stack_t *);
int  push        (stack_t *, elem);
int  top         (stack_t *, elem *);