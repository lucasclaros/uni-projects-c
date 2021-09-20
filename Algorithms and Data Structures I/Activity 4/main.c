/**
 *   Author: Lucas da Silva Claros
 *   nUSP: 12682592
 *   Create Time: 19/09/2021 22:30
 *   Modified time: 20/09/2021 19:42
 *   Description: Priority Queues
 */

#include "commands.h"
#include "queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
    commands_t *commands = malloc(sizeof(commands_t));
    for (int i = 0; i < QUEUES; i++)
        commands->main_queue[i] = queueCreate();
    
    scanf("%d", &commands->nLines);
    getchar();
    commands->linesInput = malloc(commands->nLines * sizeof(char *));

    for (int i = 0; i < commands->nLines; i++)
        commands->linesInput[i] = read_line();

    commandsDecider(commands);

    for (int i = 0; i < QUEUES; i++)
        queueDestroy(commands->main_queue[i]);

    for (int i = 0; i < commands->nLines; i++)
        free(commands->linesInput[i]);

    free(commands->linesInput);
    free(commands);
    return 0;
}

