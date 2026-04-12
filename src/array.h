#ifndef ARRAY_H 
#define ARRAY_H

#include <assert.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct array
{
    void*  internal_array;
    size_t internal_array_size;
    size_t array_size;

    size_t element_size;
} array;

array create_array(size_t element_size);
array create_array_from_carray(size_t element_size, void* array_ptr, size_t array_size);
array create_array_from_array(array arr);

void array_destroy(array* arr);

#endif