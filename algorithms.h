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
    for (int t = 0; t < runfor+1; t++)
    {
        if (peek(processes)->arrival == t)
        {
            Process* curr = dequeue(processes);
            printf("Time %d: %s arrived", t, curr->name);
        }

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