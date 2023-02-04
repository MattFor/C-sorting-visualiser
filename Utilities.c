#define STRICT

#include "Utilities.h"


void swapNumbers(int* n1, int* n2)
{
    int temp = *n1;
    *n1 = *n2;
    *n2 = temp;
}

int randInt(int lowerBound, int upperBound)
{
    return (rand() % (upperBound - lowerBound + 1)) + lowerBound;
}

int indexOf(const int arr[], int arr_size, int value)
{
    int index = 0;

    while (index < arr_size && arr[index] != value) ++index;

    return (index == arr_size ? -1 : index);
}
