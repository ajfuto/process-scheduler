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
    int turnaround;
    int num;
} Process;

// creates a process
Process *create_process(char* name, int arrival, int burst, int num)
{
    Process* p = (Process*) malloc(sizeof(Process));
    p->name = (char*) malloc(strlen(name) * sizeof(char));
    strcpy(p->name, name);
    p->arrival = arrival;
    p->burst = burst;
    p->tleft = burst;
    p->turnaround = 0;
    p->num = num;

    return p;

}


#endif
