#include <stdio.h>
#include "../src/priority_queue.h"

int main(){
    // test create

    printf("Beginning Priority Queue Tests: \n");
    printf("=======================\n\n");

    printf("Creating prio queue\n\n");
    prio_queue p = create_prio_queue(sizeof(int));

    for (int i = 9; i >= 0; i--){
        push(&p, &i, i);
        printf("%d\n", i);

        int top = 21;
        prio_top(&p, &top);
        assert(i == top);
    }
   
    printf("Making sure there are 10 items in prio queue\n");
    assert(p.arr.array_size == 10);
    printf("Confirmed\n\n");

    printf("Checking top of pqueue is 0\n");
    int top;
    prio_top(&p, &top);
    printf("Actual value: %d\n", top);
    assert(top == 0);
    printf("Passed!! \n\n");

    printf("Checking pop is 1\n");
    prio_pop(&p, &top);
    prio_pop(&p, &top);
    assert(top == 1);
    prio_pop(&p, &top);
    assert(top == 2);
    printf("Passed!!\n\n");

    destroy_prio_queue(&p);

    printf("End of Priority Queue Tests\n");
    return 0;
}