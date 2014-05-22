/*File : array.h */ //ADT Array eksplisit statik, dengan elemen tabel terurut membesar
#ifndef ARRAYPOLYGON_H
#define ARRAYPOLYGON_H

#include <stdio.h>

#include "boolean.h"
#include "rect.h"

#define MAXSIZE 100
//might help in making the generic-type array
typedef Rect ElType;
// Define an array type
typedef struct {
  int size;      // slots used so far
  int capacity;  // total available slots
  ElType *data;     // array of integers we're storing
} Array;

void array_init(Array *array);

void array_append(Array *array, ElType value);

ElType array_get(Array *array, int index);

void array_set(Array *array, int index, ElType value);

void array_double_capacity_if_full(Array *array);

void array_free(Array *array);

#endif
