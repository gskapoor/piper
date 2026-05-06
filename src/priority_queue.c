#include "priority_queue.h"

prio_queue create_prio_queue(){
    array arr = create_array(sizeof(prio_nodes));
    prio_queue prio;
    prio.arr = arr;
    return prio;
}

void push(prio_queue* prio, prio_nodes prio_node){
    // prio->arr
    append(&(prio->arr), &prio_node);
}

void prio_top(prio_queue* prio_queue, void* res, size_t element_size){
    prio_nodes prio_top = *(prio_nodes*)get(prio_queue->arr, 0);
    memcpy(res, prio_top.item, element_size);
}

void destroy_prio_queue(prio_queue* prio){
    array_destroy(&(prio->arr));
}