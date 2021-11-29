#include "commands.h"
#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct Process
{
    int id, time, quantum, prio;
};

struct Thread
{
    int nProcesses;
    list_t *processes, *main;
    node_t *currProcess;
};

thread_t *threadCreate(){
    thread_t *t = malloc(sizeof(thread_t));
    if(t == NULL) return NULL;
    t->processes = listCreate(); 
    t->main = listCreate();
    t->currProcess = NULL;
    t->nProcesses = 0;
    readProcesses(t);
    return t;

}

void threadDestroy(thread_t *t){
    listDestroy(t->processes);
    listDestroy(t->main);
    free(t);
}

int threadisEmpty(thread_t *t){
    if (t->nProcesses == 0)
        return 1; 
    return 0;
}

process_t *createProcess(int id, int time, int quantum, int prio){
    process_t *p = malloc(sizeof(process_t));
    if (p == NULL) return NULL; 

    p->id = id;
    p->time = time;
    p->quantum = quantum;
    p->prio = prio;
    return p;
}

void processDestroy(process_t *p){
    free(p);
}

int checkInsertPriority(process_t *p1, process_t *p2){
    if(p1->id == p2->id) p2->id++;
    if (p1->time < p2->time)
        return 1;
    else if(p1->time > p2->time)
        return 0;
    else
        if(p1->prio > p2->prio)
            return 1;
        else if(p1->prio < p2->prio)
            return 0;
        else
            if(p1->id >= p2->id)
                return 1;
            else
                return 0;
}
int checkPriority(process_t *p1, process_t *p2){
    if(p1->prio > p2->prio)
        return 1;
    else
        return 0;
}

int decreaseQuantum(process_t *p){
    p->quantum--;
    if(p->quantum == 0)
    {
        printf("%d ", p->id);
        return 1;
    }
    return 0;
}

void readProcesses(thread_t *t){
    int id, time, quantum, prio;
    while(scanf("%d %d %d %d", &id, &time, &quantum, &prio) != EOF)
    {
        process_t *p = createProcess(id, time, quantum, prio);
        listSortInsert(t->processes, p);
        t->nProcesses++;
    }
}

int compareTime(process_t *p, int time){
    if(p != NULL && p->time == time)
        return 1;
    else
        return 0;
}

void processKilled(thread_t *t){
    t->nProcesses--;
}

void getProcessbyTime(thread_t *t, int time){
    while (compareTime(top(t->processes), time) > 0)
    {
        process_t *p1 = pop(t->processes);
        process_t *p2 = top(t->main);
        listInsertbyPrio(t->main, p1);
        if(p1 != NULL && p2 != NULL && p1->prio > p2->prio)
            t->currProcess = listSearchElement(t->main, p1);
    }
}

node_t *getCurrProcess(thread_t *t){
    if (t->currProcess == NULL)
        updateCurrProcess(t);
    
    return t->currProcess;
}

void updateCurrProcess(thread_t *t){
    if (t->currProcess == NULL)
        t->currProcess = listSearchElement(t->main, top(t->main));
    else
    {
        t->currProcess = listNextItem(t->currProcess);
        if(t->currProcess == NULL) updateCurrProcess(t);
    }
}

list_t *getMainProcesses(thread_t *t){
    return t->main;
}