#include <iostream>
#include "sortutil.h"
using namespace std;

void swap(int* val1, int*val2)
{
	if(val1 == NULL || val2 == NULL)
	{
		return;
	}
	int temp = *val1;
	*val1 = *val2;
	*val2 = temp;
}

void show(const int* arr, int size)
{
	int i = 0;
	for (i = 0; i < size; ++i)
	{
		cout << *(arr + i) << "  ";
	}
	cout << endl;
}