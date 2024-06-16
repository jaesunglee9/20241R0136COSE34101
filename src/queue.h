#include <stdlib.h>
#include "./process.h"

#define MAXQUEUESIZE 100

#define ARRIVAL 1

typedef struct pn_t
{
    int pid;
    int priority;
    int arrival;
    int cpu_burst;
    int cpu_remaining;
    int waiting;
    int turnaround;
    int completion;
    int is_complete;
    struct pn_t* next;
} pn_t;

typedef struct pq_t
{
    pn_t* front;
    pn_t* rear;
} pq_t;



pn_t*
newprocess(int pid, int arrival, int cpu_burst);

pq_t*
createq();

void
enqueue(pq_t* q, pn_t* p);

pn_t*
dequeue(pq_t* q);

int
isqempty(pq_t* q);


