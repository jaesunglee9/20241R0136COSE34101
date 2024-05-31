#include "./linkedlist.h"

#ifndef __CPU
#define __CPU

#define FCFS 1  // first come first serve
#define NPSJF 2  // non preemptive shortest job first
#define PSJF 3  // preemptive shortest job first
#define NPPS 4  // non preemptive priority scheduling
#define PPS 5  // preemptive priority scheduling
#define RR 6  // round robin

#define MAXRUN 99999

typedef struct cpu_t
{
    int quantum[MAXRUN];
} cpu_t;

void
simulate(cpu_t* cpu, int algo, pcb_t* pcb, int p_n);

void
run(cpu_t* cpu, int pid, int t, pcb_t* pcb,int p_n);

void
fcfs(cpu_t* cpu,pcb_t* parray, int p_n);

#endif
