/**
 *   Author: Lucas da Silva Claros
 *   nUSP: 12682592
 *   Create Time: 21/09/2021 04:53
 *   Modified time: 26/09/2021 18:36
 *   Description: Replacing Strings
 */

#include "commands.h"
#include "queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){

    queue_t *q = queueCreate();
    bool isEOF = FALSE;
    while (!isEOF)
    {
        message_t *m = messageCreate();
        isEOF = readMessages(m);
        char *finalMessage = strsub(m->phrase, m->target, m->sub);
        queueInsert(q, finalMessage);
        messageDestroy(m);
    }

    while (!queueisEmpty(q))
    {
        char *x = queueRemove(q);
        printf("%s\n", x);
        free(x);
    }

    queueDestroy(q);
    return 0;
}