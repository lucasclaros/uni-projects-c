/**
 *   Author: Lucas da Silva Claros
 *   nUSP: 12682592
 *   Create Time: 03/10/2021 13:56
 *   Modified time: 09/10/2021 19:08
 */

#define SIZE_STACK 400

typedef char elem;
typedef struct stack stack_t;

stack_t *create  ();
void destroy     (stack_t *);
int  isFull      (stack_t *);
int  isEmpty     (stack_t *);
elem pop         (stack_t *);
elem top         (stack_t *);
int  push        (stack_t *, elem);