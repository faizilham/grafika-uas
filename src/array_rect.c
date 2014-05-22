/*File : array.c */ //Array implisit statik, dengan elemen tabel terurut membesar

#include "array_rect.h"

void array_init(Array *array) {
  // initialize size and capacity
  array->size = 0;
  array->capacity = MAXSIZE;

  // allocate memory for array->data
  array->data = malloc(sizeof(ElType) * array->capacity);
}

void array_append(Array *array, ElType value) {
  // make sure there's room to expand into
  array_double_capacity_if_full(array);

  // append the value and increment array->size
  array->data[array->size++] = value;
}

ElType array_get(Array *array, int index) {
  if (index >= array->size || index < 0) {
    printf("Index %d out of bounds for array of size %d\n", index, array->size);
    exit(1);
  }
  return array->data[index];
}

void array_set(Array *array, int index, ElType value) {
  // zero fill the array up to the desired index
  while (index >= array->size) {
    //array_append(array, 0); //careful if the type of the array is not int
  }

  // set the value at the desired index
  array->data[index] = value;
}

void array_double_capacity_if_full(Array *array) {
  if (array->size >= array->capacity) {
    // double array->capacity and resize the allocated memory accordingly
    array->capacity *= 2;
    array->data = realloc(array->data, sizeof(ElType) * array->capacity);
  }
}

void array_free(Array *array) {
  free(array->data);
}