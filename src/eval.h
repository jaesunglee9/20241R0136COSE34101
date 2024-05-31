#include "./cpu.h"

#ifndef __EVAL
#define __EVAL

#define MAXGANTT 99999

typedef struct gantt_t
{
    int pid[MAXGANTT+1];
    int start_time[MAXGANTT+1];
} gantt_t;

gantt_t*
creategantt(cpu_t* cpu);

void
displaygantt (gantt_t* gantt);

#endif
