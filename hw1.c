#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "algorithms.h"
#include "queue.h"


int main(void)
{
    FILE *ifp;
    srand(time(NULL));
    ifp = fopen("./processes.in", "r");

    // making sure we can open out input file
    if (ifp == NULL)
    {
        printf("error opening <processes.in> file");
        return -1;
    }

    char *line = malloc(1024 * sizeof(char));

    // read process count
    int pc = 0;
    fscanf(ifp, "%s %d%[^\n]", line, &pc, line);
    printf("processcount: %d\n", pc);

    // read runfor
    int runfor = 0;
    fscanf(ifp, "%s %d%[^\n]", line, &runfor, line);
    printf("runfor: %d\n", runfor);

    // read algorithm
    char *algo = malloc(512 * sizeof(char));
    fscanf(ifp, "%s %s%[^\n]", line, algo, line);
    printf("algo: %s\n", algo);

    // read quantum, if necessary
    int quantum = 0;
    if (strcmp(algo, "rr") == 0)
    {
        fscanf(ifp, "%s %d%[^\n]", line, &quantum, line);
        printf("quantum: %d\n", quantum);
    }

    // an array of our processes
    Queue *q = create_queue();

    // iterate through our processes
    for (int i = 0; i < pc; i++)
    {
        char *name = malloc(512 * sizeof(char));
        int arrival = 0, burst = 0;

        // read the necessary information
        fscanf(ifp, "%*s %*s %s %*s %d %*s %d", name, &arrival, &burst);

        // create a new process to append to our processes array
        int pri = rand() % 100 + 1;
        printf("%d\n", pri);
        Process* curr_process = create_process(name, arrival, burst, pri);
        enqueue(q, curr_process);
        // curr_process.name = malloc(strlen(name) * sizeof(char));
        // strcpy(curr_process.name, name);
        // curr_process.arrival = arrival;
        // curr_process.burst = burst;
        // curr_process.next = NULL;
        // curr_process.priority = 0;

        // appends process to our array
        // processes[i] = curr_process;
        // printf("name: [%-5s] arrival: [%-3d] burst: [%-3d]\n", processes[i].name, processes[i].arrival, processes[i].burst);
    }

    printf("\n");
    while (!isEmpty(q)) {
        Process *p = dequeue(q);
        printf("%s %d\n", p->name, p->priority);

    }
    
    return 0;
}

