#include <stdlib.h>
#include <stdio.h>

#include "./cpu.h"
#include "./queue.h"

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
    pn_t* p[p_n];
    for (int i =0; i < p_n; i++) {
        p[i] = newprocess(parray[i].pid, parray[i].arrival, parray[i].cpu_burst);
    }

    pq_t* q = createq();
    int t = 0, time = 0, completed = 0;
    int* gantt = (int*) calloc (MAXRUN, sizeof(int));
    int gantt_index = 0;

    while (completed <= p_n + 1) {
        for (int i = 0; i < p_n; i++) {
            if (p[i]->arrival <= time && p[i]->cpu_remaining > 0 && p[i]->arrival != -1) {
                enqueue(q, p[i]);
                p[i] ->arrival = -1;
            }
        }

        if (!isqempty(q)) {
            pn_t* current = dequeue(q);
            if (current->cpu_remaining > QUANTUM) {
                for (int i = 0; i < QUANTUM; i++) {
                    run(cpu, current->pid, t, parray, p_n);
                    t++;
                }
                time += QUANTUM;
                current->cpu_remaining -= QUANTUM;
                gantt[gantt_index++] = current->pid;
                // if (current->cpu_remaining <= 0) {
                //     parray[current->pid-1].completion_time = time;
                //     parray[current->pid-1].completion = 1;
                //     completed++;
                // }
                enqueue(q, current);
            } else {
                for (int i = 0; i < current->cpu_remaining; i++) {
                    run(cpu, current->pid, t, parray, p_n);
                    t++;
                }
                time += current->cpu_remaining;
                gantt[gantt_index++] = current->pid;
                current->cpu_remaining = 0;
                parray[current->pid-1].completion_time = time;
                parray[current->pid-1].completion = 1;
                completed++;
            }
        } else {
            gantt[gantt_index++] = -1;
            time++;
            run(cpu, 0, t, parray, p_n);
            t++;
        }
    }
    run(cpu, -1, t, parray, p_n);

    for (int i = 0; i < p_n; i++) {
        free(p[i]);
    }
    free(gantt);
}







