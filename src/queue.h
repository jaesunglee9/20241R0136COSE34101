#include <stdlib.h>
#include "./process.h"

#define MAXQUEUESIZE 100

#define ARRIVAL 1

typedef struct pq_t
{
    int head;
    int tail;
    int size;
    pcb_t* p_array;
} pq_t;



pq_t*
createpq();

void
deletepq(pq_t* pq);

int
isfull(pq_t* pq);

int
isempty(pq_t* pq);

int
enqueue(pq_t* pq, pcb_t* pcb);

pcb_t
dequeue(pq_t* pq);

pcb_t*
top(pq_t* pq);

void
displaypq(pq_t* pq);
