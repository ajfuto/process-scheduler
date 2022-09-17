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

        // looks to see if a new process has arrived
        if (!isEmpty(processes) && peek(processes)->arrival == t)
        {
            Process* curr = dequeue(processes);
            enqueue(tbp, curr);
            printf("Time %d: %s arrived\n", t, curr->name);
        }

        // looks at processes that are to be processed
        if (!isEmpty(tbp))
        {
            Process* curr = peek(tbp);

            // check if previous process finished
            if (curr->tleft == 0)
            {
                printf("Time %d: %s finished\n", t, curr->name);
                strcpy(prevname, curr->name);
                Process* dq = dequeue(tbp);
                enqueue(finished, dq);
            }   
        }

        // decrement our processes
        if (!isEmpty(tbp))
        {
            Process* curr = peek(tbp);
            
            // checks if a new process has been selected
            if(strcmp(prevname, curr->name) != 0)
            {
                printf("Time %d: %s selected (burst %d)\n", t, curr->name, curr->burst);
                strcpy(prevname, curr->name);
            }

            curr = decrement(tbp);

        }
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