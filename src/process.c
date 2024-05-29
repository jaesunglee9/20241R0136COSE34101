#include <stdlib.h>

#include "./process.h"

#define MAXBURST 100
#define MAXARRIVAL  100
#define MAXPRIORITY 100



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


int
allcomplete(pcb_t* parray, int process_n)
{
    int allcomplete = 1;
    for (int i = 0; i < process_n; i++) {
        allcomplete = allcomplete && parray[i].completion;
    }
    return allcomplete;
}

// TODO initialize according to some determined table()

void
printparray(pcb_t pcb[], int len)
{
    int i;
    for (i=0;i<len;i++) {
        printf("pid:%d\npriority:%d\n", pcb[i].pid, pcb[i].priority);
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

