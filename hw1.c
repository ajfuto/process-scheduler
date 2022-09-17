#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "algorithms.h"
#include "queue.h"

#define MAX_LEN 512

int main(void)
{
    FILE *ifp;
    srand(time(NULL));
    ifp = fopen("./asn1-sampleio/set1_process.in", "r");

    // making sure we can open out input file
    if (ifp == NULL)
    {
        printf("error opening <processes.in> file");
        return -1;
    }

    char *line = malloc(MAX_LEN * sizeof(char));
    int pc, runfor, quantum, algorithm;
    char *algo = malloc(MAX_LEN * sizeof(char));
    Queue *q = create_queue();

    // read input file
    while (fscanf(ifp, "%[^\n]\n", line) == 1)
    {
        // takes care of spacing
        while(*line == ' ' || *line == '\n')
            line++;
        
        // takes care of comments
        if (*line == '#')
            continue;

        // printf("%s\n", line);

        // argparse processcount
        if (strncmp(line, "processcount", 12) == 0)
        {
            sscanf(line, "%*s %d%*[^\n]\n", &pc);
            printf("FOUND PC: %d\n", pc);
        }

        // argparse runfor
        if (strncmp(line, "runfor", 6) == 0)
        {
            sscanf(line, "%*s %d%*[^\n]\n", &runfor);
            printf("FOUND RUNFOR: %d\n", runfor);
        }

        // argparse use algorithm
        if (strncmp(line, "use", 3) == 0)
        {
            sscanf(line, "%*s %s%*[^\n]\n", algo);

            // store algorithm in something meaningful, not a string
            if (strcmp(algo, "fcfs") == 0)
                algorithm = FIRST_COME_FIRST_SERVE;
            else if (strcmp(algo, "sjf") == 0)
                algorithm = SHORTEST_JOB_FIRST;
            else if (strcmp(algo, "rr") == 0)
                algorithm = ROUND_ROBIN;
            printf("FOUND ALGO: %d %s\n", algorithm, algo);
            
        }

        // argparse quantum
        if (strncmp(line, "quantum", 7) == 0)
        {
            sscanf(line, "%*s %d%*[^\n]\n", &quantum);
            printf("FOUND QUANTUM: %d\n", quantum);
        }

         if (strncmp(line, "process name", 12) == 0)
         {
            char *name = malloc(MAX_LEN * sizeof(char));
            int arrival = 0, burst = 0, pri=0;

            // read the necessary information
            sscanf(line, "%*s %*s %s %*s %d %*s %d", name, &arrival, &burst);

            // schedule differently based on algorithm used
            switch(algorithm)
            {
                case FIRST_COME_FIRST_SERVE:
                    pri = arrival;
                    break;
                case SHORTEST_JOB_FIRST:
                    pri = burst;
                    break;
                case ROUND_ROBIN:
                    pri = rand() % 100 + 1;
                    break;
                default:
                    pri = rand() % 100 + 1;
                    break;
            }

            // create a new process to append to our processes array
            Process* curr = create_process(name, arrival, burst, pri);
            printf("NEW PROCESS: %s, arrival %d, burst %d\n", curr->name, curr->arrival, curr->burst);
            enqueue(q, curr);
         }

    }

    printf("%d processes\n", pc);
    printf("Using %s\n", ALGO_STRINGS[algorithm - ALGO_START]);

    return 1;
    switch (algorithm)
    {
        case FIRST_COME_FIRST_SERVE:
            fcfs(pc, runfor, q);
            break;
        case SHORTEST_JOB_FIRST:
            sjf(pc, runfor, q);
            break;
        case ROUND_ROBIN:
            rr(pc, runfor, quantum, q);
            break;
    }

    // read process count
    // int pc = 0;




    // fscanf("%MAX_LEN[^\n]", line);
    // while(*line == ' ' || *line == " ")
    //     line++;
    // if (line[0] != '#')
    //     fscanf(ifp, "%s %d%[^\n]", line, &pc, line);
    // printf("processcount: %d\n", pc);

    // // read runfor
    // int runfor = 0;
    // fscanf(ifp, "%s %d%[^\n]", line, &runfor, line);
    // printf("runfor: %d\n", runfor);

    // // read algorithm
    // char *algo = malloc(MAX_LEN * sizeof(char));
    // fscanf(ifp, "%s %s%[^\n]", line, algo, line);
    // printf("algo: %s\n", algo);
    // int algorithm = INVALID_ALGORITHM;

    // // establish a value we can use to check for algorithm to avoid other string comparisons
    // if (strcmp(algo, "fcfs") == 0)
    //     algorithm = FIRST_COME_FIRST_SERVE;
    // else if (strcmp(algo, "sjf") == 0)
    //     algorithm = SHORTEST_JOB_FIRST;
    // else if (strcmp(algo, "rr") == 0)
    //     algorithm = ROUND_ROBIN;

    // if (algorithm == INVALID_ALGORITHM)
    // {
    //     printf("invalid algorithm type: %s\n", algo);
    //     return -1;
    // }

    // // read quantum, if necessary
    // int quantum = 0;
    // if (algorithm == ROUND_ROBIN)
    // {
    //     fscanf(ifp, "%s %d%[^\n]", line, &quantum, line);
    //     printf("quantum: %d\n", quantum);
    // }

    // // priority queue of our processes
    // Queue *q = create_queue();

    // // iterate through our processes
    // for (int i = 0; i < pc; i++)
    // {
    //     char *name = malloc(MAX_LEN * sizeof(char));
    //     int arrival = 0, burst = 0, pri=0;

    //     // read the necessary information
    //     fscanf(ifp, "%*s %*s %s %*s %d %*s %d", name, &arrival, &burst);

    //     // schedule differently based on algorithm used
    //     switch(algorithm)
    //     {
    //         case FIRST_COME_FIRST_SERVE:
    //             pri = arrival;
    //             break;
    //         case SHORTEST_JOB_FIRST:
    //             pri = burst;
    //             break;
    //         case ROUND_ROBIN:
    //             pri = rand() % 100 + 1;
    //             break;
    //         default:
    //             pri = rand() % 100 + 1;
    //             break;
    //     }

    //     // create a new process to append to our processes array
    //     printf("%d\n", pri);
    //     Process* curr_process = create_process(name, arrival, burst, pri);
    //     enqueue(q, curr_process);
    // }

    // printf("\n");
    // while (!isEmpty(q)) {
    //     Process *p = dequeue(q);
    //     printf("%s %d\n", p->name, p->priority);

    // }
    
    return 0;
}

