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
} prio_queue;

prio_queue create_prio_queue();

void destroy_prio_queue(prio_queue* prio_queue);

#endif