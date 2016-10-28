#include "sort.h"
#include "sortutil.h"
#include <cstdlib>

void main()
{
	int arr[] = { 4, 1, 11, 3, 8, 9, 2, -1, 0, 88, 66, 5 };
	int size = sizeof(arr) / sizeof(*arr);

	//bubbleSort(arr, size);
	//optimizedBubbleSort(arr, size);
	//selectSort(arr, size);
	insertSort(arr, size);
	show(arr, size);

	system("pause");
}