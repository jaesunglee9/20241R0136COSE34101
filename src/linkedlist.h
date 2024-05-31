#include "./process.h"

#ifndef __LL
#define __LL

#define ARRIVAL 1
#define REMAINING 2
#define PRIORITY 3

/* All find functions search for minimum values because generally we
 * want to find either the earliest, shortest, or most urgent(low priority)
 *
 */

typedef struct node_t
{
    pcb_t* pcb;
    struct node_t* next;
} node_t;

typedef struct ll_t
{
    node_t* head;
} ll_t;

ll_t*
createll();

node_t*
createnode (pcb_t* parray, int pid);

int
isempty(ll_t* ll);

void
insertpcb (ll_t* ll, pcb_t* parray, int pid);

void
insertnode (ll_t* ll, node_t* node);

void
movenode (ll_t* from, ll_t* to, int pid);


node_t*
deletenode(ll_t* ll, int pid);

int
findmin(ll_t* ll, int find_flag);

int
findminarrival(ll_t* ll);

int
findminremaining(ll_t* ll);

int
findminpriority(ll_t* ll);

void
displayll(ll_t* ll);

#endif
