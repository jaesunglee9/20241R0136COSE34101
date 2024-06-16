#include <stdlib.h>
#include <stdio.h>

#include "./process.h"
#include "./queue.h"

pn_t*
newprocess(int pid, int arrival, int cpu_burst)
{
    pn_t* temp = (pn_t*) calloc (1, sizeof(pn_t));
    temp->pid = pid;
    temp->arrival = arrival;
    temp->cpu_burst = cpu_burst;
    temp->cpu_remaining = cpu_burst;
    temp->next = NULL;
    return temp;
}

pq_t*
createq()
{
    pq_t* q = (pq_t*) calloc (1, sizeof(pq_t));
    q->front = q->rear = NULL;
    return q;
}

void
enqueue(pq_t* q, pn_t* p) {
    if (q->rear == NULL) {
        q->front = q->rear = p;
        return;
    }

    q->rear->next = p;
    q->rear = p;
}

pn_t*
dequeue(pq_t* q)
{
    if (q->front == NULL) {
        return NULL;
    }
    pn_t* temp = q->front;
    q->front = q->front->next;
    if (q->front == NULL) {
        q->rear = NULL;
    }
    return temp;
}

int
isqempty(pq_t* q)
{
    return q->front == NULL;
}


