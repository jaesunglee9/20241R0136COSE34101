#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "./eval.h"
#include "./queue.h"

int
main(int argc, char *argv[])
{
    int p_n = atoi(argv[1]);  // number of processes
    char c;  // For continue button
    float* avgwait = (float*) malloc (p_n * sizeof(float));
    float* avgturn = (float*) malloc (p_n * sizeof(float));
    int i = 0;

    pcb_t* parray = (pcb_t*)malloc(sizeof(pcb_t) * p_n);
    initrandparray(parray, p_n);
    displayparray(parray, p_n);

    /* FCFS */
    // init
    resetp(parray, p_n);
    cpu_t* cpu_fcfs = (cpu_t*) malloc (sizeof(cpu_t));

    simulate(cpu_fcfs, FCFS, parray, p_n);  // run

    printf("\n\tFCFS\n");

    gantt_t* gantt_fcfs = creategantt(cpu_fcfs);  //eval
    displaygantt(gantt_fcfs);
    eval(parray, p_n, &avgwait[i], &avgturn[i]);
    i++;

    c = getc(stdin);

    /* NPSJF */
    printf("\n\tNPSJF\n");
    resetp(parray, p_n);
    cpu_t* cpu_npsjf = (cpu_t*) malloc (sizeof(cpu_t));

    simulate(cpu_npsjf, NPSJF, parray, p_n);

    gantt_t* gantt_npsjf = creategantt(cpu_npsjf);
    displaygantt(gantt_npsjf);
    eval(parray, p_n, &avgwait[i], &avgturn[i]);
    i++;

    c = getc(stdin);

    /* PSJF */
    printf("\n\tPSJF\n");
    resetp(parray, p_n);
    cpu_t* cpu_psjf = (cpu_t*) malloc (sizeof(cpu_t));

    simulate(cpu_psjf, PSJF, parray, p_n);

    gantt_t* gantt_psjf = creategantt(cpu_psjf);
    displaygantt(gantt_psjf);
    eval(parray, p_n, &avgwait[i], &avgturn[i]);
    i++;

    c = getc(stdin);

    /* NPPS */
    printf("\n\tNPPS\n");
    resetp(parray, p_n);
    cpu_t* cpu_npps = (cpu_t*) malloc (sizeof(cpu_t));

    simulate(cpu_npps, NPPS, parray, p_n);

    gantt_t* gantt_npps = creategantt(cpu_npps);
    displaygantt(gantt_npps);
    eval(parray, p_n, &avgwait[i], &avgturn[i]);
    i++;

    c = getc(stdin);

    /* PPS */
    printf("\n\tPPS \n");
    resetp(parray, p_n);
    cpu_t* cpu_pps = (cpu_t*) malloc (sizeof(cpu_t));

    simulate(cpu_pps, PPS, parray, p_n);

    gantt_t* gantt_pps = creategantt(cpu_pps);
    displaygantt(gantt_pps);
    eval(parray, p_n, &avgwait[i], &avgturn[i]);
    i++;

    c = getc(stdin);

    printf("\n\tRR \n");
    resetp(parray, p_n);
    cpu_t* cpu_rr = (cpu_t*) malloc (sizeof(cpu_t));

    simulate(cpu_rr, RR, parray, p_n);

    gantt_t* gantt_rr = creategantt(cpu_rr);
    displaygantt(gantt_rr);
    eval(parray, p_n, &avgwait[i], &avgturn[i]);

    c = getc(stdin);

    i = 0;
    /* SUMMARY */
    printf("\tSUMMARY\n");
    printf("\t+--------+--------------+-----------------+\n");
    printf("\t|  ALGO  | Waiting Time | Turnaround Time |\n");
    printf("\t+--------+--------------+-----------------+\n");
    printf("\t|  FCFS  |    %06.2f    |      %06.2f     |\n", avgwait[i], avgturn[i]); i++;
    printf("\t|  NPSJF |    %06.2f    |      %06.2f     |\n", avgwait[i], avgturn[i]); i++;
    printf("\t|  PSJF  |    %06.2f    |      %06.2f     |\n", avgwait[i], avgturn[i]); i++;
    printf("\t|  NPPS  |    %06.2f    |      %06.2f     |\n", avgwait[i], avgturn[i]); i++;
    printf("\t|  PPS   |    %06.2f    |      %06.2f     |\n", avgwait[i], avgturn[i]); i++;
    printf("\t|  RR    |    %06.2f    |      %06.2f     |\n", avgwait[i], avgturn[i]); i++;
    printf("\t+--------+--------------+-----------------+\n");


	puts("\n");


    //  memory cleanup
    free(cpu_fcfs);
    free(cpu_npsjf);
    free(cpu_psjf);
    free(cpu_npps);
    free(cpu_pps);
    free(cpu_rr);

    free(gantt_fcfs);
    free(gantt_npsjf);
    free(gantt_psjf);
    free(gantt_npps);
    free(gantt_pps);
    free(gantt_rr);
    return 0;
}
