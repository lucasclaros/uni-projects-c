/**
 *   Author: Lucas da Silva Claros
 *   nUSP: 12682592
 *   Create Time: 09/10/2021 23:08
 *   Modified time: 10/10/2021 03:17
 *   Description: List Rotation
 */

#include "commands.h"
#include "list.h"
#include <stdio.h>
#include <stdlib.h>

int main(){
    int nInputs;
    scanf("%d", &nInputs);
    getchar();
    for (int i = 0; i < nInputs; i++)
    {
        list_t *l = listCreate();
        int nRotations = readInputs(l);
        for (int j = 0; j < nRotations; j++)
            listRotate(l);
        listPrint(l);
        listDestroy(l);
    }
    
    return 0;
}