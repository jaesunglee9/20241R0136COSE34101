#include <stdlib.h>
#include <stdio.h>

#include "./cpu.h"

void
simulate(cpu_t* cpu, int algo, pcb_t* pcb, int p_n)
{
    switch (algo) {
        case FCFS:
            fcfs(cpu, pcb, p_n);
            break;
    }
}

void
run(cpu_t* cpu, int pid, int t, pcb_t* pcb, int p_n)
{
    cpu->quantum[t] = pid;
    for (int i = 0;i < p_n; i++) {
        if (pcb[i].pid == pid) {
            pcb[i].cpu_remaining -= 1;
        }
    }
}


/* PSEUDOCODE: FCFS
 *
 * push process into queue
 * sort queue by arrival
 *
 * Init timestep = 0
 * while queue is not empty
 *     while top(queue) is not done
 *         run(top(queue))
 *         t += 1
 *     dequeue(queue)
 */
void
fcfs(cpu_t* cpu, pcb_t* parray, int p_n)
{
    ll_t* waitq = createll();
    ll_t* readyq = createll();

    for (int i = 0; i < p_n; i++) {
        insertpcb(waitq, parray, i+1);
    }

    int t = 0;
    while (!allcomplete(parray, p_n)) {
        for (int i = 0; i < p_n; i++) {
            if (parray[i].arrival == t) {
                movenode(waitq, readyq, parray[i].pid);
            }
        }


        // run
        int pid = findminarrival(readyq);
        run(cpu, pid, t, parray, p_n);


        // check if process is done
        if (iscomplete(parray, pid)) {
            node_t* del = deletenode(readyq, pid);
            free(del);
        }


        t++;
    }
    run(cpu, -1, t, parray, p_n);  // cap cpu

    free(waitq);
    free(readyq);
}


