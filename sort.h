#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <assert.h>

typedef int DataType ;

void print(DataType *array, int size);
void insertSort(DataType * array, int size);
void shellSort(DataType * array, int size);
void BubbleSort(DataType *array, int size);
void selectSort(DataType * array, int size);
void quickSort(DataType * array, int left, int right);
void heapSort(DataType * array, int size);
void mergeSort(DataType * array, int size);
void radixSort(DataType * array, int size);
