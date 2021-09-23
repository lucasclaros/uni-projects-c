#include "commands.h"
#include "queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Messages
{
    char *phrase, *target, *subs;
    bool isEOF;
    queue_t *queue;
} messages_t;

int main(){
    messages_t *m = malloc(sizeof(messages_t));
    m->isEOF = FALSE;
    m->queue = queueCreate();
    while (!m->isEOF)
    {
        char *aux = NULL;
        m->phrase = read_line(&m->isEOF);
        m->target = read_line(&m->isEOF);
        m->subs = read_line(&m->isEOF);
        aux = strstr(m->phrase, m->target);
        while (aux != NULL)
        {
            strncpy(aux, m->subs, strlen(m->target));
            aux = strstr(m->phrase, m->target);
        }
        queueInsert(m->queue, m->phrase);
    }
    while (!queueisEmpty(m->queue))
    {
        char *x = (char *)queueRemove(m->queue);
        printf("%s\n", x);
    }
    
    queueDestroy(m->queue);
    free(m);
    return 0;
}