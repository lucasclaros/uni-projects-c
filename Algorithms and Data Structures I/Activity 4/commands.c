#include "queue.h"
#include "commands.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


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
            person_t *person;
            person = (person_t *)queueRemove(commands->main_queue[i]);
            printf("%s %d %d\n", person->name, person->age, person->prio);
            free(person);
            return 1;
        }
    }
    printf("FILA VAZIA\n");
    return -1;
}

int queueAppend(commands_t *commands, int index){
    person_t *p = malloc(sizeof(person_t));
    if (p == NULL)
        return -1;
    
    char *aux = NULL;
    aux = strtok(commands->linesInput[index], " \r\n");

    aux = strtok(NULL, " \r\n");
    p->name = aux;

    aux = strtok(NULL, " \r\n");
    if (aux != NULL) p->age = atoi(aux);

    aux = strtok(NULL, " \r\n");
    if (aux != NULL) p->prio = atoi(aux);

    if (p->age >= 60)
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
        if (strcmp("SAI", commands->linesInput[i]) == 0)
            queueNext(commands);
        else 
            queueAppend(commands, i);
    }
}