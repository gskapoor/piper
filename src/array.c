#include "array.h"

// Creates an "empty" array object
array create_array(size_t element_size){
    array arr;
    arr.internal_array_size = 8;
    arr.internal_array = malloc(element_size * 8);

    arr.array_size = 0;
    arr.element_size = element_size;
    return arr;
}

// Create an array, copy this from a C array
array create_array_from_carray(size_t element_size, void* array_ptr, size_t array_size){
    array arr;
    arr.internal_array_size = 8;
    while (arr.internal_array_size < array_size){
        arr.internal_array_size *= 2;
    }
    arr.internal_array = malloc(element_size * arr.internal_array_size);

    // Copy internal array
    memcpy(arr.internal_array, array_ptr, element_size * array_size);

    arr.array_size = array_size;
    arr.element_size = element_size;

    return arr;
}

// Creates a deep copy of an array
array create_array_from_array(array old_arr){
    array arr;
    arr.internal_array_size = old_arr.internal_array_size;
    arr.element_size = old_arr.element_size;
    arr.array_size = old_arr.array_size;

    arr.internal_array = malloc(arr.element_size * arr.internal_array_size);
    memcpy(arr.internal_array, old_arr.internal_array, arr.element_size * arr.array_size);

    return arr;
}

void append_many(array* arr, void* elems, size_t elems_size){
    // first, expand the array
    bool expand = false;
    while (arr->internal_array_size < arr->array_size + elems_size){
        arr->internal_array_size *= 2;
        expand = true;
    }
    if (expand){
        void* new_ptr = realloc(arr->internal_array, arr->internal_array_size);
        if (new_ptr == NULL){
            return;
        }
        arr->internal_array = new_ptr;
    }
    
    memcpy(
        arr->internal_array + arr->array_size * arr->element_size, 
        elems, 
        elems_size * arr->element_size
    );
}

void append(array* arr, void* elem){
    append_many(arr, elem, 1);
}

void* get(array arr, size_t index){
    assert(index < arr.array_size);
    return (arr.internal_array + index * arr.element_size);
}

void array_destroy(array* arr){
    free(arr->internal_array);
    arr->internal_array = NULL;
    arr->array_size = 0;
    arr->internal_array_size = 0;
}