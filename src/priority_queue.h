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

#endif