#include <stdlib.h>
#include <stdio.h>

#include "./eval.h"

gantt_t*
creategantt(cpu_t* cpu)
{
    gantt_t* gantt = (gantt_t*) malloc (sizeof(gantt_t));

    gantt->pid[0] = cpu->time[0];
    gantt->start_time[0] = 0;

    int i = 1;  // index for gantt
    int t = 1;  // index for cpu
    while (cpu->time[t] != -1 || t < MAXRUN) {
        if (cpu->time[t-1] != cpu->time[t]) {
            gantt->pid[i] = cpu->time[t];
            gantt->start_time[i] = t;
            i++;
        }
        t++;
    }

    gantt->pid[i] = cpu->time[t];
    gantt->start_time[i] = t;

    return gantt;
}

void
displaygantt (gantt_t* gantt)
{

    printf("\nPID: \t");
    int i = 0;
    while (gantt->pid[i] != -1) {
        printf("%4d ", gantt->pid[i]);
        i++;
    }

    printf("\nSTART: \t");
    i = 0;
    while (gantt->pid[i] != -1) {
        printf("%4d ", gantt->start_time[i]);
        i++;
    }

    printf("\nEND: \t");
    i = 0;
    while (gantt->pid[i] != -1) {
        printf("%4d ", gantt->start_time[i+1]);
        i++;
    }

    printf("\nDUR: \t");
    i = 0;
    while (gantt->pid[i] != -1) {
        printf("%4d ", gantt->start_time[i+1] - gantt->start_time[i]);
        i++;
    }
    printf("\n");
}
