/***************************************************************\
**
** File Name    : sort.cpp
** Created Time : 2016-10
** Author       : Quasimodo
** Description  : Implementation of sort algorithm
** Modified     : 2016-10-31 by Quasimodo    Bubble sort optimized
**
\****************************************************************/


#include "sort.h"
#include "sortutil.h"
#include <cstdlib>
#include <cstdio>
#include <iostream>
using namespace std;

/* Bubble sort */
void bubbleSort(int* arr, int size)
{
#if 0
	int i, j;
	for (i = 0; i < size; ++i)
	{
		for (j = 0; j < size - i - 1; ++j)
		{
			if(*(arr + j) > *(arr + j + 1))
			{
				/* Donot have to swap every time */
				swap(arr + j, arr + j + 1);
			}
		}
	}
#else    /* 2016-10-31 Modified by Quasimodo */
	int flag;
	for (int i = 0; i < size; ++i)
	{
		flag = 0;
		for (int j = 1; j < size - i; ++j)
		{
			if (*(arr + flag) < *(arr + j))
			{
				/* Mark the max number */
				flag = j;  
			}
		}
		if(flag != size - i - 1)
		{
			swap(arr + flag, arr + size - i - 1);
		}
	}
#endif
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
}/* Bubble sort */

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
static int partition(int* arr, int low, int high)
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

static void quickSort(int* arr, int low, int high)
{
	int mid = 0;
	if(low < high)
	{
		mid = partition(arr, low, high);
		quickSort(arr, low, mid - 1);
		quickSort(arr, mid + 1, high);
	}
}

void quickSort(int* arr, int size)
{
	quickSort(arr, 0, size - 1);
}/* Quick sort */


/* Heap sort */
static void heapAdjust(int* arr, int parent, int size)
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


/* Merge sort */
static void mergeInsert(int* src_arr, int* dest_arr, int start, int mid, int end)
{
	int iindex = start;
	int jindex = mid + 1;
	int tmp_start= start;
	while (iindex <= mid  && jindex <= end)
	{
		if (*(src_arr + iindex) > *(src_arr + jindex))
		{
			dest_arr[tmp_start++] = src_arr[jindex++];
			//++tmp_start;
			//++jindex;
		}
		else
		{
			dest_arr[tmp_start++] = src_arr[iindex++];
			//++tmp_start;
			//++iindex;
		}
	}
	while (iindex < mid + 1)
		dest_arr[tmp_start++] = src_arr[iindex++];
	while (jindex <= end)
		dest_arr[tmp_start++] = src_arr[jindex++];

	for (iindex = start; iindex <= end; ++iindex)
		src_arr[iindex] = dest_arr[iindex];
}

static void MergeSort(int* src_arr, int* dest_arr, int start, int end)
{
	int mid;
	if(start < end)
	{
		mid = (start + end) / 2;
		MergeSort(src_arr, dest_arr, start, mid);
		MergeSort(src_arr, dest_arr, mid + 1, end);
		mergeInsert(src_arr, dest_arr, start, mid, end);
	}
}

void mergeSort(int* src_arr, int size)
{
	int *tmp = new int[size];
	if (tmp == NULL)
		return;
	MergeSort(src_arr, tmp, 0, size - 1);
	delete[] tmp;
}
/* Merge sort */

void shellSort(int* arr, int size)
{
	int i;
	int gap;

	for (gap = size / 2; gap > 0; gap /= 2)
	{
		for (i = gap; i < size; ++i)
		{
			if (*(arr + i) < *(arr + i - gap))
			{
				int temp = *(arr + i);
				int j = i - gap;
				while (j >= 0 && *(arr + j) > temp)
				{
					*(arr + j + gap) = *(arr + j);
					j -= gap;
				}
				*(arr + j + gap) = temp;
			}
		}
		show(arr, size);
	}

	//	for (gap = size / 2; gap > 0; gap /= 2)	//{	//	for (i = gap; i < size; ++i)	//	{	//		for (j = i - gap; j >= 0 && *(arr + j) > *(arr + j + gap); j -= gap)	//		{	//			swap(arr + j, arr + j + gap);	//		}	//	}	//}
}