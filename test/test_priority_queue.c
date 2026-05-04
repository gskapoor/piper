#include <stdio.h>
#include "../src/priority_queue.h"

int main(){
    // test create

    printf("Beginning Priority Queue Tests: \n");
    printf("=======================\n\n");

    printf("Creating prio queue\n\n");
    prio_queue p = create_prio_queue();
    
    // assert(p.arr.array_size == 10);

    destroy_prio_queue(&p);

    printf("End of Array Tests\n");
    return 0;
}