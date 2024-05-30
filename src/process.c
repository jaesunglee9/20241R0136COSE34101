#include <stdlib.h>
#include <stdio.h>

#include "./process.h"





void
initrandparray(pcb_t pcb[], int len)
{
    int i;
    for (i = 0; i < len; i++){

        pcb[i].pid = i+1;  /* 0 is reserved for end of computation in cpu log. This should change if cpu can be idle during computation.*/
        pcb[i].priority = rand()%MAXPRIORITY;

        pcb[i].arrival = rand()%MAXARRIVAL;
        pcb[i].cpu_burst = rand()%MAXBURST;
        pcb[i].cpu_remaining = pcb->cpu_burst;

        pcb->completion = 0;
    }
}

// TODO initialize according to some determined table()

int
allcomplete(pcb_t* parray, int p_n)
{
    int allcomplete = 1;
    for (int i = 0; i < p_n; i++) {
        allcomplete = allcomplete && parray[i].completion;
    }
    return allcomplete;
}





int*
arrivedp(pcb_t parray[], int p_n, int i)
{
    int arrivedpid[MAXPROCESS];
    int i;
    for (i = 0; i < p_n; i++) {
        if (parray[i].arrival == t) {
            arrivedpid[i] = parray[i].pid;
        }
    }
    i++;
    arrivedpid[i] = -1;  // cap arrivedpid

    return arrivedpid;
}

void
printparray(pcb_t parray[], int p_n)
{
    int i;
    for (i=0;i<p_n;i++) {
        printf("pid:%d\npriority:%d\n", parray[i].pid, parray[i].priority);
    }
}


// void run_process(pcb_t* pcb,unsigned int runtime){
//     pcb->cpu_remaining -= runtime;
//     return;
// }

// I am not sure we require io burst in cpu simulation.

// void del_process (pcb_t* process) {
//     free(process);
// }
//

