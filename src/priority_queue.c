#include "priority_queue.h"

prio_queue create_prio_queue(){
    array arr = create_array(sizeof(prio_nodes));
    prio_queue prio;
    prio.arr = arr;
    return prio;
}

// Helper functions for traversing the "Tree"
size_t parent_index(size_t node_index){
    return (node_index - 1) / 2;
}

size_t left_child_index(size_t node_index){
    return node_index * 2 + 1;
}

size_t right_child_index(size_t node_index){
    return node_index * 2 + 2;
}

prio_nodes get_prio_node(prio_queue* prio, size_t index){
    return *(prio_nodes*)get(prio->arr, index);
}

void reorganize_from_bottom(prio_queue* prio){
    size_t index = prio->arr.array_size - 1;

    while (index > 0 && get_prio_node(prio, index).weight < get_prio_node(prio, parent_index(index)).weight ){
        // Inshallah I hope this works
        size_t parent = parent_index(index);
        prio_nodes tmp = *(prio_nodes*)get(prio->arr, index);
        *(prio_nodes*)get(prio->arr, index) = *(prio_nodes*)get(prio->arr, parent);
        *(prio_nodes*)get(prio->arr, parent) = tmp;

        index = parent;
    }
}

void push(prio_queue* prio, prio_nodes prio_node){
    // prio->arr
    append(&(prio->arr), &prio_node);
    reorganize_from_bottom(prio);
}

void prio_top(prio_queue* prio_queue, void* res, size_t element_size){
    prio_nodes prio_top = *(prio_nodes*)get(prio_queue->arr, 0);
    memcpy(res, prio_top.item, element_size);
}

void destroy_prio_queue(prio_queue* prio){
    array_destroy(&(prio->arr));
}