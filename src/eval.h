#include "./cpu.h"

#ifndef __EVAL
#define __EVAL

#define MAXGANTT 999999
#define CHARTLEN 60

typedef struct gantt_t
{
    int pid[MAXGANTT+1];
    int start[MAXGANTT+1];
    int end[MAXGANTT+1];
    int dur[MAXGANTT+1];
    int ratio[MAXGANTT+1];
} gantt_t;


gantt_t*
creategantt(cpu_t* cpu);

void
eval(pcb_t* parray, int p_n, float* avgwait, float* avgturn);


void
displaygantt (gantt_t* gantt);


#endif
