#include "sort.h"

int main(void)
{
    DataType array[] = {10, 99, 2, 32, 275, 3214, 234, 41};
    int size = sizeof(array) / sizeof(array[0]);

    print(array, size);
    mergeSort(array, size);
    print(array, size);

    return 0;
}
