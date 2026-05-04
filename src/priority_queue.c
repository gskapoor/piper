#include "priority_queue.h"

prio_queue create_prio_queue(){
    array arr = create_array(sizeof(prio_nodes));
    prio_queue prio;
    prio.arr = arr;
    return prio;
}

void destroy_prio_queue(prio_queue* prio){
    array_destroy(&(prio->arr));
}