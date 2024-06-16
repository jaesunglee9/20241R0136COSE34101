#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "./process.h"





void
initrandparray(pcb_t pcb[], int len)
{
    srand(time(NULL));

    int i;
    for (i = 0; i < len; i++){

        pcb[i].pid = i+1;  /* 0 is reserved for end of computation in cpu log. This should change if cpu can be idle during computation.*/
        pcb[i].priority = rand()%MAXPRIORITY;

        pcb[i].arrival = rand()%MAXARRIVAL;
        pcb[i].cpu_burst = rand()%MAXBURST;
        pcb[i].cpu_remaining = pcb[i].cpu_burst;

        pcb->completion = 0;
    }
}

// TODO initialize according to some determined table()

int
iscomplete(pcb_t* parray, int pid, int t)
{
    int i = pid - 1;  // index and pid differ by 1
    if (parray[i].cpu_remaining == 0) {
        parray[i].completion = 1;
        parray[i].completion_time = t + 1;
        return parray[i].completion;
    }
    return parray[i].completion;
}

int
allcomplete(pcb_t* parray, int p_n)
{
    int allcomplete = 1;
    for (int i = 0; i < p_n; i++) {
        allcomplete = allcomplete && parray[i].completion;
    }
    return allcomplete;
}

void
resetp(pcb_t* parray, int p_n)
{
    for (int i = 0; i < p_n; i++) {
        parray[i].cpu_remaining = parray[i].cpu_burst;
        parray[i].completion_time = 0;
        parray[i].turnaround_time = 0;
        parray[i].waiting_time = 0;
        parray[i].completion = 0;
    }
}

void
displayparray(pcb_t parray[], int p_n)
{
    int i;
    for (i=0;i<p_n;i++) {
        printf("pid:%d, priority:%d, arrival: %d, burst:%d, remaining: %d, completion_time: %d, completion:%d\n",
               parray[i].pid,
               parray[i].priority,
               parray[i].arrival,
               parray[i].cpu_burst,
               parray[i].cpu_remaining,
               parray[i].completion_time,
               parray[i].completion);
    }
}

// I am not sure we require io burst in cpu simulation.


