#include "./process.h"

#include <stdlib.h>
#include <stdio.h>

int
main(int argc, char *argv[])
{
    int p_n = atoi(argv[1]);  // process number

    pcb_t* pcb = (pcb_t*)malloc(sizeof(pcb_t) * p_n);
    initrandparray(parray, p_n);
    displayparray(parray, p_n);

    /* FCFS */
    // init
    resetp(parray, p_n);
    cpu_t* cpu_fcfsf = (cpu_t*) malloc (sizeof(cpu_t));

    simulate(cpu_fcfsf, NPSJF, parray, p_n);  // run

    gantt_t* gantt_fcfs = creategantt(cpu_fcfsf);  //eval
    displaygantt(gantt_fcfs);
    displayganttchart(gantt_fcfs);
    eval(parray, p_n)

    /* NPSJF */
    resetp(parray, p_n);
    cpu_t* cpu_npsjf = (cpu_t*) malloc (sizeof(cpu_t));

    simulate(cpu_npsjf, NPSJF, parray, p_n);

    gantt_t* gantt_npsjf = creategantt(cpu_npsjf);
    displaygantt(gantt_npsjf);
    displayganttchart(gantt_npsjf);
    eval(parray, p_n);

    /* PSJF */
    resetp(parray, p_n);
    cpu_t* cpu_psjf = (cpu_t*) malloc (sizeof(cpu_t));

    simulate(cpu_psjf, PSJF, parray, p_n);

    gantt_t* gantt_psjf = creategantt(cpu_psjf);
    displaygantt(gantt_psjf);
    displayganttchart(gantt_psjf);
    eval(parray, p_n);

    /* NPPS */
    printf(" NPPS \n");
    resetp(parray, process_n);
    cpu_t* cpu_npps = (cpu_t*) malloc (sizeof(cpu_t));

    simulate(cpu_npps, NPPS, parray, process_n);

    gantt_t* gantt_npps = creategantt(cpu_npps);
    displaygantt(gantt_npps);
    displayganttchart(gantt_npps);
    printf("\n");
    eval(parray, process_n);

    /* PPS */
    printf(" PPS \n");
    resetp(parray, process_n);
    cpu_t* cpu_pps = (cpu_t*) malloc (sizeof(cpu_t));

    simulate(cpu_pps, PPS, parray, process_n);

    gantt_t* gantt_pps = creategantt(cpu_pps);
    displaygantt(gantt_pps);
    displayganttchart(gantt_pps);
    printf("\n");
    eval(parray, process_n);


    // TODO: memory cleanup
    free(gantt_fcfs);
    free(gantt_npsjf);
    free(gantt_psjf);
    free(gantt_npps);
    free(gantt_pps);
    return 0;
}
