#include "priority_queue.h"

void destroy_prio_node(prio_nodes n){
    free(n.item);
}

prio_queue create_prio_queue(size_t element_size){
    array arr = create_array(sizeof(prio_nodes));
    prio_queue prio;
    prio.arr = arr;
    prio.element_size = element_size;
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

void remove_last_node(prio_queue* prio){
    free(get_prio_node(prio, prio->arr.array_size - 1).item);

    decrease_array_size(&prio->arr, 1);
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

void reorganize_from_top(prio_queue* prio){
    size_t index = 0;
    size_t child = 0;
    // while the index has a child
    while (left_child_index(index) < prio->arr.array_size){
        if (get_prio_node(prio, index).weight > get_prio_node(prio, left_child_index(index)).weight){
            if (right_child_index(index) < prio->arr.array_size && get_prio_node(prio, left_child_index(index)).weight > get_prio_node(prio, right_child_index(index)).weight){
                child = right_child_index(index);
            } else {
                child = left_child_index(index);
            }

            prio_nodes tmp = *(prio_nodes*)get(prio->arr, index);
            *(prio_nodes*)get(prio->arr, index) = *(prio_nodes*)get(prio->arr, child);
            *(prio_nodes*)get(prio->arr, child) = tmp;

            index = child;

        } else if (right_child_index(index) < prio->arr.array_size && get_prio_node(prio, index).weight > get_prio_node(prio, right_child_index(index)).weight){
            child = right_child_index(index);
            
            prio_nodes tmp = *(prio_nodes*)get(prio->arr, index);
            *(prio_nodes*)get(prio->arr, index) = *(prio_nodes*)get(prio->arr, child);
            *(prio_nodes*)get(prio->arr, child) = tmp;

            index = child;


        } else {
            return;
        }
    }
}

void push(prio_queue* prio, void* item, uint32_t weight){
    // prio->arr

    prio_nodes node;

    node.item = malloc(prio->element_size);
    memcpy(node.item, item, prio->element_size);
    node.weight = weight;
    
    append(&(prio->arr), &node);
    reorganize_from_bottom(prio);
}

void prio_top(prio_queue* prio_queue, void* res){
    prio_nodes prio_top = *(prio_nodes*)get(prio_queue->arr, 0);
    memcpy(res, prio_top.item, prio_queue->element_size);
}

void prio_pop(prio_queue* prio_queue, void* res){
    prio_top(prio_queue, res);

    // make the top of the tree the bottom most element
    // Swap to deallocate the head's pointer (I hate memory leaks)
    prio_nodes tmp = *(prio_nodes*)get(prio_queue->arr, 0);
    *(prio_nodes*)get(prio_queue->arr, 0) = *(prio_nodes*)get(prio_queue->arr, prio_queue->arr.array_size - 1);
    *(prio_nodes*)get(prio_queue->arr, prio_queue->arr.array_size - 1) = tmp;

    remove_last_node(prio_queue);

    if (prio_queue->arr.array_size > 0){
        reorganize_from_top(prio_queue);
    }
}

void destroy_prio_queue(prio_queue* prio){
    for (size_t i = 0; i < prio->arr.array_size; i++){
        free(get_prio_node(prio, i).item);
    }
    array_destroy(&(prio->arr));
}