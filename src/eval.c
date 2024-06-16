#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "./eval.h"



gantt_t*
creategantt(cpu_t* cpu)
{
    gantt_t* gantt = (gantt_t*) malloc (sizeof(gantt_t));

    gantt->pid[0] = cpu->time[0];
    gantt->start[0] = 0;

    int i = 1;  // index for gantt
    int t = 1;  // index for cpu
    while (cpu->time[t] != -1 && t < MAXRUN) {
        if (cpu->time[t-1] != cpu->time[t]) {
            gantt->pid[i] = cpu->time[t];
            gantt->start[i] = t;
            i++;
        }
        t++;
    }

    // cap gantt
    gantt->pid[i] = cpu->time[t];
    gantt->start[i] = t;

    // secondary info
    i = 0;
    while (gantt->pid[i] != -1) {
        gantt->end[i] = gantt->start[i+1];
        gantt->dur[i] = gantt->end[i] - gantt->start[i];
        i++;
    }

    float total_dur = (float) gantt->end[i-1];
    i = 0;
    while (gantt->pid[i] != -1) {
        int ratio = ceil(gantt->dur[i] / total_dur * CHARTLEN);
        if (ratio < 3) {
            ratio = 3;
        }
        gantt->ratio[i] = ratio;
        i++;
    }



    return gantt;
}

void
eval(pcb_t* parray, int p_n, float* avgwait, float* avgturn)
{
    // waiting needs to be defined after turnaround, hence two loops
    for (int i = 0; i < p_n; i++) {
        parray[i].turnaround_time = parray[i].completion_time - parray[i].arrival;
    }
    for (int i = 0; i < p_n; i++) {
        parray[i].waiting_time = parray[i].turnaround_time - parray[i].cpu_burst;
    }


    puts("\t+-----+------------+--------------+----------+--------------+-----------------+");
    puts("\t| PID | Burst Time | Arrival Time | Priority | Waiting Time | Turnaround Time |");
    puts("\t+-----+------------+--------------+----------+--------------+-----------------+");


	for (int i = 0; i < p_n; i++)
	{
		printf("\t| %3d |     %3d    |      %3d     |    %3d   |      %3d     |        %3d      |\n",
			parray[i].pid, parray[i].cpu_burst, parray[i].arrival, parray[i].priority, parray[i].waiting_time, parray[i].turnaround_time);

		puts("\t+-----+------------+--------------+----------+--------------+-----------------+");
	}

	puts("\n");



    int total_wait = 0;
    int total_turnaround = 0;
    for (int i = 0; i < p_n; i++) {
        total_wait += parray[i].waiting_time;
        total_turnaround += parray[i].turnaround_time;
    }

    float avg_wait = (float) total_wait / p_n;
    float avg_turnaround = (float) total_turnaround / p_n;



    *avgwait = avg_wait;
    *avgturn = avg_turnaround;

    printf("Average waiting: %f, average turnaround: %f\n\n", avg_wait, avg_turnaround);

}

void
displaygantt (gantt_t* gantt)
{

    printf("\nPID: \t");
    int i = 0;
    while (gantt->pid[i] != -1) {
        printf("%4d ", gantt->pid[i]);
        i++;
    }

    printf("\nSTART: \t");
    i = 0;
    while (gantt->pid[i] != -1) {
        printf("%4d ", gantt->start[i]);
        i++;
    }

    printf("\nEND: \t");
    i = 0;
    while (gantt->pid[i] != -1) {
        printf("%4d ", gantt->end[i]);
        i++;
    }

    printf("\nDUR: \t");
    i = 0;
    while (gantt->pid[i] != -1) {
        printf("%4d ", gantt->dur[i]);
        i++;
    }
    printf("\n");

    /* DISPLAY GANTT CHART */

    // set total dur
    i = 0;
    while (gantt->pid[i] != -1) {
        i++;
    }
    float total_dur = (float) gantt->end[i-1];

    // print top part of chart
    printf(" ");
    i = 0;
    while (gantt->pid[i] != -1) {
        for(int j = 0; j < gantt->ratio[i]; j++) {
            printf("-");
        }
        printf(" ");
        i++;
    }

    printf("\n");

    // print process name
    printf("|");
    i = 0;
    while (gantt->pid[i] != -1) {
        if (gantt->pid[i] == 0) {
            for (int j = 0; j < gantt->ratio[i]; j++) {
                printf(" ");
            }
        } else {
            printf("P%-*d", gantt->ratio[i]-1, gantt->pid[i]);  // (2 * gantt->ratio[i])-1

        }
        printf("|");
        i++;
    }

    printf("\n");

    // print bottom bar

    printf(" ");
    i = 0;
    while (gantt->pid[i] != -1) {
        for(int j = 0; j < gantt->ratio[i]; j++) {
            printf("-");
        }
        printf(" ");
        i++;
    }

    printf("\n");

    // print endtime
    printf(" ");
    i = 0;
    while (gantt->pid[i] != -1) {
        printf("%*d", gantt->ratio[i], gantt->end[i]);  // 2*gantt->ratio[i] + 1
        printf(" ");
        i++;
    }
    printf("\n\n");
}



