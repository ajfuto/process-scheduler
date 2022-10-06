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
void fcfs(int process_count, int runfor, Queue *processes, FILE* ofp)
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
            a_enqueue(tbp, curr);
            fprintf(ofp, "Time %d: %s arrived\n", t, curr->name);
        }

        // check if the last process finished
        if (!isEmpty(tbp) && peek(tbp)->tleft == 0)
        {
            fprintf(ofp, "Time %d: %s finished\n", t, peek(tbp)->name);
            strcpy(prevname, peek(tbp)->name);
            Process* dq = dequeue(tbp);
            a_enqueue(finished, dq);
        }

        // check if we have selected a new process
        if (!isEmpty(tbp) && (strcmp(prevname, peek(tbp)->name) != 0))
        {
            fprintf(ofp, "Time %d: %s selected (burst %d)\n", t, peek(tbp)->name, peek(tbp)->tleft);
            strcpy(prevname, peek(tbp)->name);
        }

        // handle idle
        if (isEmpty(tbp) && (t!=runfor))
        {
            fprintf(ofp, "Time %d: idle\n", t);
        }

        // finally, process our queue (decrement the first thing)
        process_q(tbp);
    }

    // after our processor runs, print that we finished
    fprintf(ofp, "Finished at time %d\n\n", runfor);

    // print stats for individual processes
    while (!isEmpty(finished))
    {
        Process *dq = dequeue(finished);
        fprintf(ofp, "%s wait %d turnaround %d\n", dq->name, (dq->turnaround - dq->burst), dq->turnaround);
    }

    // catches any processes that did not complete
    while (!isEmpty(tbp))
    {
        Process *dq = dequeue(tbp);
        fprintf(ofp, "%s wait %d did not complete\n", dq->name, (dq->turnaround - dq->burst));
    }

    // catches any processes that could not be scheduled
    while (!isEmpty(processes))
    {
        Process *dq = dequeue(processes);
        fprintf(ofp, "%s could not be scheduled\n", dq->name);
    }
}

// preemptive shortest job first algorithm (aka stcf)
void sjf(int process_count, int runfor, Queue *processes, FILE* ofp)
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
            t_enqueue(tbp, curr);
            fprintf(ofp, "Time %d: %s arrived\n", t, curr->name);
        }

        // check if the last process finished
        if (!isEmpty(tbp) && peek(tbp)->tleft == 0)
        {
            fprintf(ofp, "Time %d: %s finished\n", t, peek(tbp)->name);
            strcpy(prevname, peek(tbp)->name);
            Process* dq = dequeue(tbp);
            n_enqueue(finished, dq);
        }

        // check if we have selected a new process
        if (!isEmpty(tbp) && (strcmp(prevname, peek(tbp)->name) != 0))
        {
            fprintf(ofp, "Time %d: %s selected (burst %d)\n", t, peek(tbp)->name, peek(tbp)->tleft);
            strcpy(prevname, peek(tbp)->name);
        }

        // handle idle
        if (isEmpty(tbp) && (t!=runfor))
        {
            fprintf(ofp, "Time %d: idle\n", t);
        }

        // finally, process our queue (decrement the first thing)
        process_q(tbp);
    }

    // after our processor runs, print that we finished
    fprintf(ofp, "Finished at time %d\n\n", runfor);

    // print stats for individual processes
    while (!isEmpty(finished))
    {
        Process *dq = dequeue(finished);
        fprintf(ofp, "%s wait %d turnaround %d\n", dq->name, (dq->turnaround - dq->burst), dq->turnaround);
    }

    // catches any processes that did not complete
    while (!isEmpty(tbp))
    {
        Process *dq = dequeue(tbp);
        fprintf(ofp, "%s wait %d did not complete\n", dq->name, (dq->turnaround - dq->burst));
    }

    // catches any processes that could not be scheduled
    while (!isEmpty(processes))
    {
        Process *dq = dequeue(processes);
        fprintf(ofp, "%s could not be scheduled\n", dq->name);
    }
}

// round-robin algorithm
void rr(int process_count, int runfor, int quantum, Queue *processes, FILE* ofp)
{
    Queue *tbp = create_queue(); // to be processed
    Queue *finished = create_queue(); // processes that have finished
    int t; // current time
    int slice = 0;
    char prevname[512];

    // loops through time properly
    for (t = 0; t < runfor+1; t++)
    {
        int p_finished = 0; // has a process finished this round?
        q_increment_turnaround(tbp);

        // check if a new process has arrived
        if (!isEmpty(processes) && peek(processes)->arrival == t)
        {
            Process* curr = dequeue(processes);
            b_enqueue(tbp, curr);
            fprintf(ofp, "Time %d: %s arrived\n", t, curr->name);
        }

        // check if the last process finished
        if (!isEmpty(tbp) && peek(tbp)->tleft == 0)
        {
            fprintf(ofp, "Time %d: %s finished\n", t, peek(tbp)->name);
            strcpy(prevname, peek(tbp)->name);
            Process* dq = dequeue(tbp);
            n_enqueue(finished, dq);
            
            // reset the slice counter
            slice = 0;

            // mark that something finished this round
            p_finished = 1;
        }

        // selects new process if necessary
        if (!isEmpty(tbp) && (slice%quantum == 0))
        {            
            // only dequeue a process if we haven't finished one
            if (!p_finished)
            {
                Process* temp = dequeue(tbp);
                b_enqueue(tbp, temp);
            }
            fprintf(ofp, "Time %d: %s selected (burst %d)\n", t, peek(tbp)->name, peek(tbp)->tleft);
            strcpy(prevname, peek(tbp)->name);
            slice = 0;

        }

        // increments slice
        slice++;

        // check if we have selected a new process
        // if (!isEmpty(tbp) && (strcmp(prevname, peek(tbp)->name) != 0))
        // {
        //     fprintf(ofp, "Time %d: %s selected (burst %d)\n", t, peek(tbp)->name, peek(tbp)->tleft);
        //     strcpy(prevname, peek(tbp)->name);
        // }

        // handle idle
        if (isEmpty(tbp) && (t!=runfor))
        {
            fprintf(ofp, "Time %d: idle\n", t);
        }

        // finally, process our queue (decrement the first thing)
        process_q(tbp);

    }

    // after our processor runs, print that we finished
    fprintf(ofp, "Finished at time %d\n\n", runfor);

    // print stats for individual processes
    while (!isEmpty(finished))
    {
        Process *dq = dequeue(finished);
        fprintf(ofp, "%s wait %d turnaround %d\n", dq->name, (dq->turnaround - dq->burst), dq->turnaround);
    }

    // catches any processes that did not complete
    while (!isEmpty(tbp))
    {
        Process *dq = dequeue(tbp);
        fprintf(ofp, "%s wait %d did not complete\n", dq->name, (dq->turnaround - dq->burst));
    }

    // catches any processes that could not be scheduled
    while (!isEmpty(processes))
    {
        Process *dq = dequeue(processes);
        fprintf(ofp, "%s could not be scheduled\n", dq->name);
    }
}

#endif