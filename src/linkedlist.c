#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

#include "linkedlist.h"

ll_t*
createll ()
{
    ll_t* ll = (ll_t*) malloc (sizeof (ll_t));
    ll->head = NULL;
    return ll;
}

node_t*
createnode (pcb_t* parray, int pid)
{
    node_t* new = (node_t*) malloc (sizeof (node_t));
    new->pcb = &parray[pid-1];
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

void
insertpcb (ll_t* ll, pcb_t* parray, int pid)
{
    node_t* node = createnode (parray, pid);
    insertnode(ll, node);
}

void
insertnode (ll_t* ll, node_t* node)
{
    node->next = ll->head;
    ll->head = node;
}

void
movenode (ll_t* from, ll_t* to, int pid)
{
    node_t* current = deletenode(from, pid);
    insertnode(to, current);
}


node_t*
deletenode (ll_t* ll, int pid)
{
    node_t* current = ll->head;
    node_t* previous = NULL;

    while (current != NULL) {
        if (current->pcb->pid == pid) {
            if (previous == NULL) {  // if first node
                ll->head = current->next;
            } else {
                previous->next = current->next;
            }
            return current;  // successfully deleted
        }
        previous = current;
        current = current->next;
    }
}

int
findmin(ll_t* ll, int find_flag) {
    int pid;
    switch (find_flag) {
        case ARRIVAL:
            pid = findminarrival (ll);
            break;
        case REMAINING:
            pid = findminremaining (ll);
            break;
        case PRIORITY:
            pid = findminpriority (ll);
            break;
        default:
            pid = -1;
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
    node_t* current = ll->head;
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
    node_t* current = ll->head;
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
    node_t* current = ll->head;
    while (current != NULL) {
        if (current->pcb->priority < min_priority) {
            pid = current->pcb->pid;
            min_priority = current->pcb->priority;
        }
        current = current->next;
    }
    return pid;
}

void
displayll(ll_t* ll)
{
    if (isempty(ll)) {
        printf("is empty\n");
        return;
    }

    node_t* current = ll->head;
    while (current != NULL) {
        printf("Process ID: %d, Priority: %d, Arrival: %d, Burst: %d, Remaining: %d, Completion: %d\n",
               current->pcb->pid,
               current->pcb->priority,
               current->pcb->arrival,
               current->pcb->cpu_burst,
               current->pcb->cpu_remaining,
               current->pcb->completion);
        current = current->next;
    }
}













