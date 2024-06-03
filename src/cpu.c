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
        case NPSJF:
            npsjf(cpu, pcb, p_n);
            break;
        case PSJF:
            psjf(cpu, pcb, p_n);
            break;
        case NPPS:
            npps(cpu, pcb, p_n);
            break;
        case PPS:
            pps(cpu, pcb, p_n);
            break;
        case RR:
            rr(cpu, pcb, p_n);
            break;
    }
}

void
run(cpu_t* cpu, int pid, int t, pcb_t* pcb, int p_n)
{
    cpu->time[t] = pid;
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
        int pid = findmin(readyq, ARRIVAL);
        run(cpu, pid, t, parray, p_n);


        // check if process is done
        if (iscomplete(parray, pid, t)) {
            node_t* del = deletenode(readyq, pid);
            free(del);
        }


        t++;
    }
    run(cpu, -1, t, parray, p_n);  // cap cpu

    free(waitq);
    free(readyq);
}


void
npsjf(cpu_t* cpu, pcb_t* parray, int p_n)
{
    ll_t* waitq = createll();
    ll_t* readyq = createll();

    for (int i = 0; i < p_n; i++) {
        insertpcb(waitq, parray, i+1);
    }

    int pid = 0;
    int t = 0;
    while (!allcomplete(parray, p_n)) {
        for (int i = 0; i < p_n; i++) {
            if (parray[i].arrival == t) {
                movenode(waitq, readyq, parray[i].pid);
            }
        }

        // run
        if (pid == 0) {
            pid = findmin(readyq, REMAINING);
        }

        run(cpu, pid, t, parray, p_n);



        // check if process is done
        if (iscomplete(parray, pid, t)) {
            node_t* del = deletenode(readyq, pid);
            free(del);
            pid = 0;
        }
        t++;





    }
    run(cpu, -1, t, parray, p_n);  // cap cpu

    free(waitq);
    free(readyq);
}




void
psjf(cpu_t* cpu, pcb_t* parray, int p_n)
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
        int pid = findmin(readyq, REMAINING);
        run(cpu, pid, t, parray, p_n);


        // check if process is done
        if (iscomplete(parray, pid, t)) {
            node_t* del = deletenode(readyq, pid);
            free(del);
        }


        t++;
    }
    run(cpu, -1, t, parray, p_n);  // cap cpu

    free(waitq);
    free(readyq);
}


void
npps(cpu_t* cpu, pcb_t* parray, int p_n)
{
    ll_t* waitq = createll();
    ll_t* readyq = createll();

    for (int i = 0; i < p_n; i++) {
        insertpcb(waitq, parray, i+1);
    }

    int pid = 0;
    int t = 0;
    while (!allcomplete(parray, p_n)) {
        for (int i = 0; i < p_n; i++) {
            if (parray[i].arrival == t) {
                movenode(waitq, readyq, parray[i].pid);
            }
        }

        if (pid == 0) {
            pid = findmin(readyq, PRIORITY);
        }

        // run
        run(cpu, pid, t, parray, p_n);


        // check if process is done
        if (iscomplete(parray, pid, t)) {
            node_t* del = deletenode(readyq, pid);
            free(del);
            pid = 0;
        }
        t++;
    }
    run(cpu, -1, t, parray, p_n);  // cap cpu

    free(waitq);
    free(readyq);
}


void
pps(cpu_t* cpu, pcb_t* parray, int p_n)
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
        int pid = findmin(readyq, PRIORITY);
        run(cpu, pid, t, parray, p_n);


        // check if process is done
        if (iscomplete(parray, pid, t)) {
            node_t* del = deletenode(readyq, pid);
            free(del);
        }


        t++;
    }
    run(cpu, -1, t, parray, p_n);  // cap cpu

    free(waitq);
    free(readyq);
}


void
rr(cpu_t* cpu, pcb_t* parray, int p_n)
{

    ll_t* waitq = createll();
    ll_t* readyq = createll();

    for (int i = 0; i < p_n; i++) {
        insertpcb(waitq, parray, i+1);
    }

    int pid = 0;
    int runtime = 0;
    int t = 0;
    node_t* current = NULL;

    while (!allcomplete(parray, p_n)) {
        //  t check for arrival
        for (int i = 0; i < p_n; i++) {
            if (parray[i].arrival == t) {
                movenodetail(waitq, readyq, parray[i].pid);
            }
        }

        if (isempty(readyq)) {  // if ready q empty
            run(cpu, 0, t, parray, p_n);
        } else {
            if (pid == 0 || runtime == 0) {  // If done or first
                current = deletenodehead(readyq);
                pid = current->pcb->pid;
                runtime = (current->pcb->cpu_remaining < QUANTUM) ? current->pcb->cpu_remaining : QUANTUM;
            }

            run(cpu, pid, t, parray, p_n);
            runtime -= 1;

            if (runtime == 0) {
                if (!iscomplete(parray, pid, t)) {
                    insertnodetail(readyq, current);
                }
                pid = 0;
            }
        }
        t++;
    }
}







