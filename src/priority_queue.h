#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include "array.h"
#include <stdint.h>

typedef struct {
    void* item;
    uint32_t weight;
} prio_nodes;

typedef struct {
    array arr;
    size_t element_size;
} prio_queue;

void destroy_prio_node(prio_nodes n);

prio_queue create_prio_queue(size_t weight);

void push(prio_queue* prio, void* item, uint32_t weight);

void prio_pop(prio_queue* prio_queue, void* res);
void prio_top(prio_queue* prio_queue, void* res);

void destroy_prio_queue(prio_queue* prio_queue);

#endif