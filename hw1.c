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
    int num = 0;
    ifp = fopen("./asn1-sampleio/set3_process.in", "r");

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
            // printf("FOUND PC: %d\n", pc);
        }

        // argparse runfor
        if (strncmp(line, "runfor", 6) == 0)
        {
            sscanf(line, "%*s %d%*[^\n]\n", &runfor);
            // printf("FOUND RUNFOR: %d\n", runfor);
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
            // printf("FOUND ALGO: %d %s\n", algorithm, algo);
            
        }

        // argparse quantum
        if (strncmp(line, "quantum", 7) == 0)
        {
            sscanf(line, "%*s %d%*[^\n]\n", &quantum);
            // printf("FOUND QUANTUM: %d\n", quantum);
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
            Process* curr = create_process(name, arrival, burst, pri, num++);
            // printf("NEW PROCESS: %s, arrival %d, burst %d num %d\n", curr->name, curr->arrival, curr->burst, curr->num);
            a_enqueue(q, curr);
        }

    }

    printf("%d processes\n", pc);
    printf("Using %s\n\n", ALGO_STRINGS[algorithm - ALGO_START]);

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
    
    return 0;
}

