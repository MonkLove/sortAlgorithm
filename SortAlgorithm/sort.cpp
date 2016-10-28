#include "sort.h"
#include "sortutil.h"

void bubbleSort(int* arr, int size)
{
	int i, j;
	for (i = 0; i < size; ++i)
	{
		for (j = 0; j < size - i - 1; ++j)
		{
			if(*(arr + j) > *(arr + j + 1))
			{
				swap(arr + j, arr + j + 1);
			}
		}
	}
}

void optimizedBubbleSort(int* arr, int size)
{
	int flag = size;
	int swap_flag = 0;
	while(flag != 0)
	{
		swap_flag = 0;
		for (int i = 0; i < flag; ++i)
		{
			if(*(arr + i) > *(arr + i + 1) && i < size - 1)
			{
				swap(arr + i, arr + i + 1);
				swap_flag = i;
			}
		}
		flag = swap_flag;
	}
}

void insertSort(int* arr, int size)
{
	int tmp;
	int j;
	for (int i = 1; i < size; ++i)
	{
		if(*(arr + i - 1) > *(arr + i))
		{
			tmp = *(arr + i);
			j = i - 1;
			while( *(arr + j)> tmp)
			{
				*(arr + j + 1) = *(arr + j);
				--j;
			}
			*(arr + j + 1) = tmp;
		}
	}
}

void selectSort(int* arr, int size)
{
	int flag = 0;
	for (int i = 0; i < size - 1; ++i)
	{
		flag = i;
		for (int j = i + 1; j < size; ++j)
		{
			if(*(arr + flag ) > *(arr + j))
			{
				flag = j;
			}
		}
		if(i != flag)
		{
			swap(arr + i, arr + flag);
		}
	}
}

void partition()
{}
void quickSort(int* arr, int size)
{}

void heapAdjust()
{}
void heapSort()
{}