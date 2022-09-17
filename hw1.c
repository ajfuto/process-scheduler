#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "algorithms.h"
#include "queue.h"

#define MAX_LEN 512

int main(int argc, char **argv)
{
    FILE *ifp, *ofp;
    srand(time(NULL));
    int num = 0;

    if (argc != 2)
    {
        printf("please run with the following syntax:\n");
        printf("\t./a.out processes_file_name.in\n");
        return -1;
    }

    // opens input file
    ifp = fopen(argv[1], "r");

    // making sure we can open out input file
    if (ifp == NULL)
    {
        printf("error opening <processes.in> file\n");
        return -1;
    }

    // generates output file name
    char *output_name = malloc(MAX_LEN * sizeof(char));
    int i = 0;
    while (*argv[1] != '.')
        output_name[i++] = *argv[1]++;
    output_name = strcat(output_name, ".out");

    // opens output file
    ofp = fopen(output_name, "w");

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

    fprintf(ofp, "%d processes\n", pc);
    fprintf(ofp, "Using %s\n", ALGO_STRINGS[algorithm - ALGO_START]);
    if (algorithm == ROUND_ROBIN)
        fprintf(ofp, "Quantum %d\n", quantum);
    fprintf(ofp, "\n");

    switch (algorithm)
    {
        case FIRST_COME_FIRST_SERVE:
            fcfs(pc, runfor, q, ofp);
            break;
        case SHORTEST_JOB_FIRST:
            sjf(pc, runfor, q, ofp);
            break;
        case ROUND_ROBIN:
            rr(pc, runfor, quantum, q, ofp);
            break;
    }
    
    fclose(ifp);
    fclose(ofp);
    return 0;
}

