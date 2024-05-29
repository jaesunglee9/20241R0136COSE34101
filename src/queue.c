#include <stdlib.h>
#include <stdio.h>

#include "./process.h"
#include "./queue.h"



pq_t*
createpq()
{
    pq_t* pq = (pq_t*)malloc(sizeof(pq_t));
    pq->head = 0;
    pq->tail = -1;
    pq->size = 0;
    pq->p_array = (pcb_t*)malloc(MAXQUEUESIZE * sizeof(pcb_t));

    return pq;
}

void
deletepq(pq_t* pq)
{
    free(pq->p_array);
    free(pq);
}

int
isfull(pq_t* pq)
{
    return (pq->size == MAXQUEUESIZE);
}

int
isempty(pq_t* pq)
{
    return (pq->size == 0);
}

int
enqueue(pq_t* pq, pcb_t* pcb)
{
    if (isfull(pq)) {
        return -1;
    }
    pq->tail = (pq->tail+1)%MAXQUEUESIZE;
    pq->p_array[pq->tail] = *pcb;
    pq->size++;
    return 0;
}

pcb_t
dequeue(pq_t* pq)
{
    pcb_t pcb = pq->p_array[pq->head];
    pq->head = (pq->head+1)%MAXQUEUESIZE;
    pq->size--;
    return pcb;
}

pcb_t*
top(pq_t* pq)
{
    return &(pq->p_array[pq->tail]);
}


void
displaypq(pq_t* pq)
{
    if (isempty(pq)) {
        printf("is empty\n");
        return;
    }

    int i;
    for (i=0; i<pq->size; i++) {
        int index = (pq->head+i)%MAXQUEUESIZE;
        printf("Process ID: %d, Priority: %d\n",
               pq->p_array[index].pid,
               pq->p_array[index].priority);
    }
}

