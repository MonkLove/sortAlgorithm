#ifndef _SORT_H_
#define _SORT_H_

void bubbleSort(int* arr, int size);
void optimizedBubbleSort(int* arr, int size);

void insertSort(int* arr, int size);

void selectSort(int* arr, int size);

int partition(int* arr, int low, int high);
void quickSort(int* arr, int low, int size);

void heapAdjust(int* arr, int parent, int size);
void heapSort(int* arr, int size);

void merge(int* src_arr, int*tmp, int start, int mid, int end);
void MergeSort(int* src_arr, int* tmp, int start, int end);
void mergeSort(int* src_arr, int size);

void shellSort(int* arr, int size);

#endif  /* _SORT_H_ */