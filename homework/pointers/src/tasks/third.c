#include <stdio.h>

#define PFN printf("\n")

void print_array_using_pointer(int* array, int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%d ", *(array + i));
    }
    PFN;
}
