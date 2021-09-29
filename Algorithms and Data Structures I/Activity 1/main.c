/**
 *   Author: Lucas da Silva Claros
 *   nUSP: 12682592
 *   Create Time: 27/09/2021 00:32
 *   Modified time: 29/09/2021 06:14
 *   Description: Frequent Words
 */

#include "commands.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){

    bool isEOF = FALSE;
    while (!isEOF)
    {
        input_t *t = inputCreate();
        isEOF = inputRead(t);
        freq_words_t *f = wordCounter(t);
        freqWordsPrint(t, f);
        if (!isEOF) printf("\n");
        freqWordsDestroy(f);
        inputDestroy(t);
    }

    return 0;
}