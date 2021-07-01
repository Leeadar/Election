#pragma once
#include "district_header.h"
/*
    A Merge-Sort Template-Algorithem.
	Sort the given array in Descending order.
*/

/// Template Algorithem:
// This function gets two halves of an array and their sizes,
// and copies the elements sorted into the array res
template<class T>
void merge(T* arr1, int n1, T* arr2, int n2, T* res)
{
	int i1 = 0;
	int i2 = 0;
	int i;
	int n = n1 + n2;

	for (i = 0; i < n; i++)
	{
		if (i1 < n1 && i2 < n2)
		{
			if (compare(arr1[i1], arr2[i2]))
			{
				res[i] = arr1[i1];
				i1++;
			}
			else
			{
				res[i] = arr2[i2];
				i2++;
			}
		}
		else if (i1 < n1)	// and i2 == n2
		{
			res[i] = arr1[i1];
			i1++;
		}
		else	// i2 < n2 and i1 == n1
		{
			res[i] = arr2[i2];
			i2++;
		}
	}
}

// Merge sort in descending order
template<class T>
T* mergeSort(T* array, int size)
{
	T* res = NULL;
	int i;

	if (size > 1)
	{
		mergeSort(array, size / 2);	// sort first half of the array
		mergeSort(array + size / 2, size - size / 2);	// sort second half of the array
		res = new T[size];
		merge(array, size / 2, array + size / 2, size - size / 2, res);

		// copy new array into original array
		for (i = 0; i < size; i++)
			array[i] = res[i];

		delete[] res;
	}
	return array;
}

// Compare two T types
template<class T>
bool compare(T t1, T t2)
{
	if (t1 > t2)
	{
		return true;
	}
	else
	{
		return false;
	}
}

// Compare two parties
template<>
bool compare(partySort* p1, partySort* p2)
{
	if (p1->electors > p2->electors)
	{
		return true;
	}
	else
	{
		return false;
	}
}

