#include <stdio.h>
#include "../src/priority_queue.h"

int main(){
    // test create

    printf("Beginning Priority Queue Tests: \n");
    printf("=======================\n\n");

    printf("Creating prio queue\n\n");
    prio_queue p = create_prio_queue();

    array arr = create_array(sizeof(int));
    for (int i = 0; i < 10; i++){
        append(&arr, &i);
    }

    for (int i = 9; i >= 0; i--){
        prio_nodes pnode;
        pnode.item = get(arr, i);
        pnode.weight = i;
        push(&p, pnode);

        int top = 21;
        prio_top(&p, &top, sizeof(int));
        assert(i == top);
    }
   
    printf("Making sure there are 10 items in prio queue\n");
    assert(p.arr.array_size == 10);
    printf("Confirmed\n\n");

    printf("Checking top of pqueue is 0\n");
    int top;
    prio_top(&p, &top, sizeof(int));
    printf("Actual value: %d\n", top);
    assert(top == 0);
    printf("Passed!! \n\n");

    destroy_prio_queue(&p);
    array_destroy(&arr);

    printf("End of Priority Queue Tests\n");
    return 0;
}