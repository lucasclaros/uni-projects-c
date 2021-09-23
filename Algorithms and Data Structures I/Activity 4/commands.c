#include "queue.h"
#include "commands.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

person_t *personCreate(){
    person_t *p = (person_t *)malloc(sizeof(person_t));
    assert(p != NULL);
    p->name = NULL;
    p->prio = 0;
    p->age = 0;
    return p; 
}

void personDestroy(person_t *p){
    assert(p != NULL);
    free(p->name);
    free(p);
}

char *read_line(){
    int c,k=0;
    char *linha = NULL;
    while((c=getchar()) != '\n' && c != EOF)
    {
        if (c == '\r') continue;
        
        linha = realloc(linha, (k+1) * sizeof(char));
        linha[k++] = c;
    }
    linha = realloc(linha, (k+1) * sizeof(char));
    linha[k] = '\0';
    return linha;
}

int queueNext(commands_t *commands){
    for (int i = 0; i < QUEUES; i++)
    {
        if(!queueisEmpty(commands->main_queue[i]))
        {
            person_t *person = queueRemove(commands->main_queue[i]);
            printf("%s %d %d\n", person->name, person->age, person->prio);
            personDestroy(person);
            return 1;
        }
    }
    printf("%s\n", EMPTY_MESSAGE);
    return -1;
}

/**
 *  The function separates the input line using strtok().
 * First call is for cleaning "ENTRA" from the line and the
 * next three calls get name, age, and prio respectively. It allocates
 * memory in p->name copying name into it. strol is needed to convert
 * number in string into integer becoming available for comparisons.
 * After that, the person created will be inserted on your respective
 * queue.
 * 
 * @param commands: struct Commands pointer
 * @param index: index of the lineInput
 * 
 * @return: 1 - all good
 *         -1 - person cannot be created
 */
int queueAppend(commands_t *commands, int index){
    person_t *p = personCreate();
    if (p == NULL)
        return -1;

    char *aux = strtok(commands->linesInput[index], " ");

    if ((aux = strtok(NULL, " ")) != NULL) 
    { 
        p->name = malloc((strlen(aux)+1) * sizeof(char));
        strcpy(p->name, aux);
    }
    if ((aux = strtok(NULL, " ")) != NULL) p->age = strtol(aux, NULL, 10);
    if ((aux = strtok(NULL, " ")) != NULL) p->prio = strtol(aux, NULL, 10);

    if (p->age >= PRIO_AGE)
    {   
        if (p->prio == TRUE)
            queueInsert(commands->main_queue[ELDERLY_1], p);
        else
            queueInsert(commands->main_queue[ELDERLY_0], p);
    }else if (p->prio == TRUE)
        queueInsert(commands->main_queue[NORMAL_1], p);
    else
        queueInsert(commands->main_queue[NORMAL_0], p);
    
    return 1;
}

void commandsDecider(commands_t *commands){
    for (int i = 0; i < commands->nLines; i++)
    {
        if (strcmp(KEYWORD, commands->linesInput[i]) == 0)
            queueNext(commands);
        else 
            queueAppend(commands, i);
    }
}