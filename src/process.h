/*
** PROCESS NUMBER(Technically belongs to accounting, but put put it separately
** because it is important)
** SCHEDULING INFORMATION(Priority,Pointers to scheduling queues)
** ACCOUNTING INFORMATION(CPU Burst time, real time, IO time etc)
*/

#include <stdio.h>

#ifndef __PROCESS
#define __PROCESS

typedef struct pcb_t  // process control block
{
	int pid;
	int priority;

	// accounting information
	int arrival;
	int cpu_burst;
	int cpu_remaining;

	int completion;
} pcb_t;

void
initrandparray(pcb_t pcb[], int len);

int
allcomplete(pcb_t* parray, int process_n);

void
printparray(pcb_t pcb[], int len);

#endif

