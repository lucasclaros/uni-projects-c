/**
 *   Author: Lucas da Silva Claros
 *   nUSP: 12682592
 *   Course: SCC0201
 *   Create Time: 12/10/2021 10:16
 *   Modified time: 18/10/2021 17:35
 *   Description: WAV Compression
 */

#include "commands.h"
#include <stdio.h>

int main(){

    char *filename = read_line();
    int nCoef;
    scanf("%d", &nCoef);
    getchar();
    
    audio_t *audio = createAudio(filename, nCoef);
    read_audio(audio);
    DFT(audio);
    sortByMagnitude(audio);
    printAudio(audio);
    //createNewAudio(audio);
    destroyAudio(audio);
    return 0;
}