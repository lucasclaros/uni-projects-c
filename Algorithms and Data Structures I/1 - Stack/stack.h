#define SIZE_STACK 100

typedef int elem;
typedef struct stack stack_t;

stack_t *create();
void destroy(stack_t *);
int isFull(stack_t *);
int isEmpty(stack_t *);
int push(stack_t *, elem);
int pop(stack_t *, elem *);
int top(stack_t *, elem *);
void printStack(stack_t *);