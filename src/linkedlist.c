 
#include "linkedlist.h"

ll_t*
createll ()
{
    ll_t* ll = (ll_t*) malloc (sizeof (ll_t));
    ll->head = NULL;
    return ll;
}

node_t*
createnode (pcb_t* pcb)
{
    node_t* new = (node_t*) malloc (sizeof (node_t));
    new->pcb = pcb;
    new->next = NULL;
    return new;
}

int
isempty(ll_t* ll)
{
    if (ll->head == NULL) {
        return 1;
    } else {
        return 0;
    }
    return 0;
}

int
iscomplete(ll_t* ll, pid)
{
    node_t* current = ll->head;
    while (current != NULL) {
        if (current->pcb->pid == pid) {
            if (current->pcb->cpu_remaining == 0) {
                current->pcb->completion = 1;
                return 1;
            } else {
                return 0;
            }
        }
        current = current->next;
    }
    return 0;
}


void
insertnode (ll_t* ll, pcb_t* pcb)
{
    node_t* node = createnode (pcb);
    if (isempty(ll)) {
        ll->head = node;
    } else {
        ll->head->next = node;
    }
}

int
deletenode (ll_t* ll, int pid)
{
    if (isempty(ll)) {
        return -1;  // is empty
    }
    node_t* current = ll->head;
    node_t* previous = NULL;

    while (current != NULL) {
        if (current->pcb->pid == pid) {
            if (previous == NULL) {  // if first node
                ll->head = current->next;
            } else {
                previous->next = current->next;
            }
            free(current);
            return 0;  // successfully deleted
        }
        previous = current;
        current = current->next;
    }
    return -1;  // no such node found
}

int
findmin(ll_t* ll, int find_flag) {
    int pid;
    switch find_flag {
        case ARRIVAL:
            pid = findminarrival (ll_t* ll);
            break;
        case REMAINING:
            pid = findminremaining (ll_t* ll);
            break;
        case PRIORITY:
            pid = findminpriority (ll_t* ll);
            break;
    }
    return pid;
}

int
findminarrival (ll_t* ll)
{
    int pid;
    int min_arrival_time = INT_MAX;

    if (isempty(ll)) {
        return 0;  // isempty
    }
    node_t* current = ll->head
    while (current != NULL) {
        if (current->pcb->arrival < min_arrival_time) {
            pid = current->pcb->pid;
            min_arrival_time = current->pcb->arrival;
        }
        current = current->next;
    }
    return pid;
}

int
findminremaining (ll_t* ll)
{
    int pid;
    int min_remaining = INT_MAX;

    if (isempty(ll)) {
        return 0;  // isempty
    }
    node_t* current = ll->head
    while (current != NULL) {
        if (current->pcb->cpu_remaining < min_remaining) {
            pid = current->pcb->pid;
            min_remaining = current->pcb->cpu_remaining;
        }
        current = current->next;
    }
    return pid;
}


/* The lower the priority, the more urgent */
int
findminpriority (ll_t* ll)
{
    int pid;
    int min_priority = INT_MAX;

    if (isempty(ll)) {
        return 0;  // isempty
    }
    node_t* current = ll->head
    while (current != NULL) {
        if (current->pcb->priority < min_priority) {
            pid = current->pcb->pid;
            min_priority = current->pcb->priority;
        }
        current = current->next;
    }
    return pid;
}













