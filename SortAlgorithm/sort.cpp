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

/* Quick sort */
int partition(int* arr, int low, int high)
{
	int flag = *(arr + low);
	while(low < high)
	{
		while (flag > *(arr + high) && low < high/* It is necessary*/)
			--high;
		if (low < high)
		{
			*(arr + low) = *(arr + high);
			++low;
		}
		while (flag < *(arr + low) && low < high/* It is necessary*/)
			++low;
		if(low < high)
		{
			*(arr + high) = *(arr + low);
			--high;
		}
	}
	*(arr + low) = flag;
	return low;
}
void quickSort(int* arr, int low, int high)
{
	int mid = 0;
	if(low < high)
	{
		mid = partition(arr, low, high);
		quickSort(arr, low, mid - 1);
		quickSort(arr, mid + 1, high);
	}
}/* Quick sort */

/* Heap sort*/
void heapAdjust(int* arr, int parent, int size)
{
	int lchild = 2 * parent + 1;      /* Left child */
	int rchild = lchild + 1;          /* Right child */
	int flag = parent;
	
	if (*(arr + flag) > *(arr + lchild) && lchild < size)
			flag = lchild;
	if (*(arr + flag) > *(arr + rchild) && rchild < size)
			flag = rchild;

	if(flag != parent)
	{
		swap(arr + flag, arr + parent);
		heapAdjust(arr, flag, size);
	}
}
void heapSort(int* arr, int size)
{
	int parent = size / 2;
	for (int i = parent; i >= 0; --i)
	{
		heapAdjust(arr, i, size);
	}

	for (int i = size; i > 0; --i)
	{
		swap(arr, arr + i - 1);
		heapAdjust(arr, 0, i - 1);
	}
}/* Heap sort*/