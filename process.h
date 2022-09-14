#ifndef PROCESS_H
#define PROCESS_H

#include <stdlib.h>
#include <string.h>

typedef struct Process
{
    char* name;
    int arrival;
    int burst;
    int priority;
} Process;

Process *create_process(char* name, int arrival, int burst, int priority)
{
    Process* p = (Process*) malloc(sizeof(Process));
    p->name = (char*) malloc(strlen(name) * sizeof(char));
    strcpy(p->name, name);
    p->arrival = arrival;
    p->burst = burst;
    p->priority = priority;

    return p;

}


#endif
