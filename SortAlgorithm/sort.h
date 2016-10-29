#ifndef _SORT_H_
#define _SORT_H_

void bubbleSort(int* arr, int size);
void optimizedBubbleSort(int* arr, int size);

void insertSort(int* arr, int size);

void selectSort(int* arr, int size);

int partition(int* arr, int low, int high);
void quickSort(int* arr, int low, int size);

void heapAdjust();
void heapSort();

#endif  /* _SORT_H_ */