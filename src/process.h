/*
** PROCESS NUMBER(Technically belongs to accounting, but put put it separately
** because it is important)
** SCHEDULING INFORMATION(Priority,Pointers to scheduling queues)
** ACCOUNTING INFORMATION(CPU Burst time, real time, IO time etc)
*/



#ifndef __PROCESS
#define __PROCESS

#define MAXBURST 100
#define MAXARRIVAL  100
#define MAXPRIORITY 100
#define MAXPROCESS 100

typedef struct pcb_t  // process control block
{
	int pid;
	int priority;

	// accounting information
	int arrival;
	int cpu_burst;
	int cpu_remaining;

	int completion_time;
	int turnaround_time;
	int waiting_time;

	int completion;
} pcb_t;

void
initrandparray(pcb_t pcb[], int len);

int
iscomplete(pcb_t* parray, int pid, int t);

int
allcomplete(pcb_t* parray, int p_n);

void
resetp(pcb_t* parray, int p_n);

void
displayparray(pcb_t pcb[], int len);

#endif

