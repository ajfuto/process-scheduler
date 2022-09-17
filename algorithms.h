#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include <stdlib.h>
// #include "linkedlist.h"
#include "queue.h"

#define INVALID_ALGORITHM -1
#define ALGO_START 100
#define FIRST_COME_FIRST_SERVE ALGO_START+0
#define SHORTEST_JOB_FIRST ALGO_START+1
#define ROUND_ROBIN ALGO_START+2

const char ALGO_STRINGS[3][25] = {"First Come First Served", "Shortest Job First (Pre)", "Round-Robin"};

// first-come-first-serve algorithm
void fcfs(int process_count, int runfor, Queue *processes)
{
    Queue *tbp = create_queue();
    Queue *finished = create_queue();
    int t;
    char prevname[512];

    // loops through time properly
    for (t = 0; t < runfor+1; t++)
    {
        q_increment_turnaround(tbp);

        // check if a new process has arrived
        if (!isEmpty(processes) && peek(processes)->arrival == t)
        {
            Process* curr = dequeue(processes);
            enqueue(tbp, curr);
            printf("Time %d: %s arrived\n", t, curr->name);
        }

        // check if the last process finished
        if (!isEmpty(tbp) && peek(tbp)->tleft == 0)
        {
            printf("Time %d: %s finished\n", t, peek(tbp)->name);
            strcpy(prevname, peek(tbp)->name);
            Process* dq = dequeue(tbp);
            enqueue(finished, dq);
        }

        // check if we have selected a new process
        if (!isEmpty(tbp) && (strcmp(prevname, peek(tbp)->name) != 0))
        {
            printf("Time %d: %s selected (burst %d)\n", t, peek(tbp)->name, peek(tbp)->burst);
            strcpy(prevname, peek(tbp)->name);
        }

        // finally, process our queue (decrement the first thing)
        process_q(tbp);
    }

    printf("Finished at time %d\n\n", runfor);

    while (!isEmpty(finished)) {
        Process *dq = dequeue(finished);
        printf("%s wait %d turnaround %d\n", dq->name, (dq->turnaround - dq->burst), dq->turnaround);
    }
}

// shortest job first algorithm
void sjf(int process_count, int runfor, Queue *processes)
{

}

// round-robin algorithm
void rr(int process_count, int runfor, int quantum, Queue *processes)
{

}

#endif