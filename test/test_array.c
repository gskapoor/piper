#include <stdio.h>
#include "../src/array.h"

int main(){
    // test create

    printf("Beginning Array Tests: \n");
    printf("=======================\n\n");
    array arr = create_array(sizeof(int));

    // test append

    printf("Creating array [0..9]\n");
    for (int i = 0; i < 10; i++)
        append(&arr, &i);

    printf("Array size %ld\n\n", arr.array_size);
    assert(arr.array_size == 10);

    printf("Attempting to remove one element: \n");
    decrease_array_size(&arr, 1);
    printf("Array size %ld\n\n", arr.array_size);
    assert(arr.array_size == 9);
    // test get
    printf("Testing Getting each element, expecting [0..8]\n");
    printf("Custom array: [");
    for (size_t i = 0; i < arr.array_size; i++){
        // Fucking shouldn't work
        size_t res = *(int*)get(arr, i);
        assert(i == res);
        if (i == 0){
            printf("%ld", res);
        } else {
            printf(", %ld", res);
        }
    }
    printf("]\n");

    // test pop, etc...

    array_destroy(&arr);

    printf("End of Array Tests\n");
    return 0;
}