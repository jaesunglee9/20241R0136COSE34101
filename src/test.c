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



    /* test 5: Now check for FCFS logic  */
    printf("TEST 5:\n");
    int t = 0;
    cpu_t* cpu_fcfs = (cpu_t*) malloc (sizeof(cpu_t));
    ll_t* readyq = createll();
    while (!allcomplete(parray, process_n)) {
        for (int i = 0; i < process_n; i++) {
            if (parray[i].arrival == t) {
                movenode(waitq, readyq, parray[i].pid);
            }
        }

        int pid = findminarrival(readyq);
        run(cpu_fcfs, pid, t, parray, process_n);

        if (iscomplete(parray, pid)) {
            node_t* del = deletenode(readyq, pid);
            free(del);
        }

        printf("waitq ll:\n");
        displayll(waitq);
        printf("readyq ll:\n");
        displayll(readyq);
        printf("time: %d\n", t);
        t++;
    }

    /* test 6: Check actual fcfs function, along with gantt chart*/
    printf("TEST 6:\n");
    resetp(parray, process_n);

    cpu_t* cpu_fcfsf = (cpu_t*) malloc (sizeof(cpu_t));
    simulate(cpu_fcfsf, FCFS, parray, process_n);

    gantt_t* gantt_fcfs = creategantt(cpu_fcfsf);
    displaygantt(gantt_fcfs);
    displayparray(parray, process_n);


    return 0;
}
