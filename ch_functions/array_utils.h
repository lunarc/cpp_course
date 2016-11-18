#ifndef __array_utils_h__
#define __array_utils_h__

int** createArray(int rows, int cols);
void zeroArray(int**& array, int rows, int cols);
void deleteArray(int**& array);

#endif