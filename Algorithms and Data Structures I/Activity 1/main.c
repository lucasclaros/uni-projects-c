/**
 *   Author: Lucas da Silva Claros
 *   nUSP: 12682592
 *   Create Time: 27/09/2021 00:32
 *   Modified time: 27/09/2021 23:50
 *   Description: Frequent Words
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
        input_t *t = inputCreate();
        isEOF = inputRead(t);
        freq_words_t *f = wordCount(t);
        freqWordPrint(t, f);
        if (!isEOF) printf("\n");
        freqWordDestroy(f);
        inputDestroy(t);
    }

    queueDestroy(q);
    return 0;
}