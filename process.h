#ifndef PROCESS_H
#define PROCESS_H

#include <stdlib.h>
#include <string.h>

typedef struct Process
{
    char* name;
    int arrival;
    int burst;
    int tleft;
    int priority;
    int turnaround;
} Process;

Process *create_process(char* name, int arrival, int burst, int priority)
{
    Process* p = (Process*) malloc(sizeof(Process));
    p->name = (char*) malloc(strlen(name) * sizeof(char));
    strcpy(p->name, name);
    p->arrival = arrival;
    p->burst = burst;
    p->tleft = burst;
    p->priority = priority;
    p->turnaround = 0;

    return p;

}


#endif
