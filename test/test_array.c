#include <stdio.h>
#include "../src/array.h"

int main(){
    // test create
    array arr = create_array(sizeof(int));

    // test append
    for (int i = 0; i < 10; i++)
        append(&arr, &i);

    // test get
    for (size_t i = 0; i < arr.array_size; i++)
        printf("%d\n", *(int*)get(&arr, i));

    // test pop, etc...

    array_destroy(&arr);
    return 0;
}