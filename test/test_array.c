#include <stdio.h>
#include "../src/array.h"

int main(){
    // test create

    printf("Beginning Array Tests: \n");
    printf("=======================\n");
    array arr = create_array(sizeof(int));

    // test append
    for (int i = 0; i < 10; i++)
        append(&arr, &i);

    printf("Array size %ld\n", arr.array_size);
    assert(arr.array_size == 10);
    // test get
    printf("Testing Getting each element\n");
    printf("[");
    for (size_t i = 0; i < arr.array_size; i++){
        // Fucking shouldn't work
        size_t res = *(int*)get(arr, i);
        assert(i == res);
        if (i == 0){
            printf("%d", res);
        } else {
            printf(", %d", res);
        }
    }
    printf("]\n");

    // test pop, etc...

    array_destroy(&arr);
    return 0;
}