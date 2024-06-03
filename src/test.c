#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "./eval.h"

int
main(int argc, char *argv[])
{
    int process_n = atoi(argv[1]);

    /* test 1: Check if initialization of pcb array is functioning */
    pcb_t* parray = (pcb_t*)malloc(sizeof(pcb_t) * process_n);
    initrandparray(parray, process_n);
    displayparray(parray, process_n);

    /* test 2: Check if push into and find on linked list is functioning */
    ll_t* waitq = createll();
    for (int i = 0; i < process_n; i++) {
        insertpcb(waitq, parray, i+1);
    }
    displayll(waitq);

    /* test 3: check for move node*/
    ll_t* test1 = createll();
    for (int i = 0; i < process_n; i++) {
        insertpcb(test1, parray, i+1);
    }
    ll_t* test2 = createll();
    printf("test1 ll:\n");
    displayll(test1);
    printf("test2 ll:\n");
    displayll(test2);

    movenode(test1, test2, 3);
    movenode(test1, test2, 5);

    printf("test1 ll:\n");
    displayll(test1);
    printf("test2 ll:\n");
    displayll(test2);

    /* test 4: Check for run function */
    printf("TEST 4:\n");
    cpu_t* cpu_test = (cpu_t*) malloc (sizeof(cpu_t));
    run(cpu_test, 1, 3, parray, process_n);
    displayll(test1);
    for(int i=0; i < 10; i++) {
        printf("%d ", cpu_test->time[i]);
    }
    printf("\n");



    // /* test 5: Now check for FCFS logic  */
    // printf("TEST 5:\n");
    // int t = 0;
    // cpu_t* cpu_fcfs = (cpu_t*) malloc (sizeof(cpu_t));
    // ll_t* readyq = createll();
    // while (!allcomplete(parray, process_n)) {
    //     for (int i = 0; i < process_n; i++) {
    //         if (parray[i].arrival == t) {
    //             movenode(waitq, readyq, parray[i].pid);
    //         }
    //     }
    //
    //     int pid = findminarrival(readyq);
    //     run(cpu_fcfs, pid, t, parray, process_n);
    //
    //     if (iscomplete(parray, pid, t)) {
    //         node_t* del = deletenode(readyq, pid);
    //         free(del);
    //     }
    //
    //     printf("waitq ll:\n");
    //     displayll(waitq);
    //     printf("readyq ll:\n");
    //     displayll(readyq);
    //     printf("time: %d\n", t);
    //     t++;
    // }
    //
    // /* test 6: Check actual fcfs function, along with gantt chart*/
    // printf("TEST 6: FCFS \n");
    // resetp(parray, process_n);
    //
    // cpu_t* cpu_fcfsf = (cpu_t*) malloc (sizeof(cpu_t));
    // simulate(cpu_fcfsf, FCFS, parray, process_n);
    //
    // gantt_t* gantt_fcfs = creategantt(cpu_fcfsf);
    // displaygantt(gantt_fcfs);
    // displayparray(parray, process_n);
    //
    // /* test 7: display gantt chart */
    // printf("TEST 7:\n");
    // int i = 0;
    // while (gantt_fcfs->pid[i] != -1) {
    //     printf("%d ", gantt_fcfs->ratio[i]);
    //     i++;
    // }
    // printf("\n");
    // displayganttchart(gantt_fcfs);
    // printf("\n");
    //
    // /* test 8: npsjf*/
    // printf("TEST 8: NPSJF\n");
    // resetp(parray, process_n);
    // cpu_t* cpu_npsjf = (cpu_t*) malloc (sizeof(cpu_t));
    // simulate(cpu_npsjf, NPSJF, parray, process_n);
    //
    // gantt_t* gantt_npsjf = creategantt(cpu_npsjf);
    // displaygantt(gantt_npsjf);
    // displayganttchart(gantt_npsjf);
    // printf("\n");
    // eval(parray, process_n);
    //
    // /* test 9: psjf */
    // printf("TEST 9: PSJF");
    // resetp(parray, process_n);
    // cpu_t* cpu_psjf = (cpu_t*) malloc (sizeof(cpu_t));
    // simulate(cpu_psjf, PSJF, parray, process_n);
    //
    // gantt_t* gantt_psjf = creategantt(cpu_psjf);
    // displaygantt(gantt_psjf);
    // displayganttchart(gantt_psjf);
    // printf("\n");
    // eval(parray, process_n);
    //
    //
    // /* test 10: npps */
    // printf("TEST 10: NPPS\n");
    // resetp(parray, process_n);
    // cpu_t* cpu_npps = (cpu_t*) malloc (sizeof(cpu_t));
    // simulate(cpu_npps, NPPS, parray, process_n);
    //
    // gantt_t* gantt_npps = creategantt(cpu_npps);
    // displaygantt(gantt_npps);
    // displayganttchart(gantt_npps);
    // printf("\n");
    // eval(parray, process_n);
    //
    // /* test 11 */
    // printf("TEST 11: PPS");
    // resetp(parray, process_n);
    // cpu_t* cpu_pps = (cpu_t*) malloc (sizeof(cpu_t));
    // simulate(cpu_pps, PPS, parray, process_n);
    //
    // gantt_t* gantt_pps = creategantt(cpu_pps);
    // displaygantt(gantt_pps);
    // displayganttchart(gantt_pps);
    // printf("\n");
    // eval(parray, process_n);

    printf("TEST 12: RR\n");
    ll_t* waitque = createll();
    ll_t* readyque = createll();
    cpu_t* cpu_rr = (cpu_t*) malloc (sizeof(cpu_t));

    for (int i = 0; i < process_n; i++) {
        insertpcb(waitque, parray, i+1);
    }

    displayll(waitque);

    int pid = 0;
    int runtime = 0;
    int t = 0;
    node_t* current = NULL;

    while (!allcomplete(parray, process_n)) {
        //  t check for arrival
        for (int i = 0; i < process_n; i++) {
            if (parray[i].arrival == t) {
                movenodetail(waitque, readyque, parray[i].pid);
            }
        }
        // if (t % 5 == 0) {
        //     printf("%d\n", t);
        //     displayll(readyque);
        // }

        if (isempty(readyque)) {  // if ready q empty
            run(cpu_rr, 0, t, parray, process_n);
        } else {
            if (pid == 0 || runtime == 0) {  // If done or first
                if  (current!= NULL && current->pcb->cpu_remaining > 0) {
                    insertnodetail(readyque, current);
                }

                current = deletenodehead(readyque);
                pid = current->pcb->pid;
                runtime = (current->pcb->cpu_remaining < QUANTUM) ? current->pcb->cpu_remaining : QUANTUM;
            }

            run(cpu_rr, pid, t, parray, process_n);
            runtime -= 1;

            if (current->pcb->cpu_remaining == 0) {
                current->pcb->completion = 1;
                 pid = 0;
            }
        }

        t++;
    }




    // resetp(parray, process_n);
    // cpu_t* cpu_rr = (cpu_t*) malloc (sizeof(cpu_t));
    // simulate(cpu_rr, RR, parray, process_n);
    //
    for(int i = 0; i < 500; i++) {
        printf("%d", cpu_rr->time[i]);
    }
    gantt_t* gantt_rr = creategantt(cpu_rr);
    displaygantt(gantt_rr);
    displayganttchart(gantt_rr);
    printf("\n");
    eval(parray, process_n);


    return 0;
}
