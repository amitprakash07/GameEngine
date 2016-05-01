#include "Sort.h"
#include <stdio.h>

template<typename T>
void Engine::Utils::Sort::MergeSort(T* o_List,
	int iListlength,
	int (*SortFunc)(T i_A, T i_B))
{
	  
	InternalMergeSort(o_List, 0, iListlength-1);
}

/*
if (hi <= lo) return;
int mid = lo + (hi - lo) / 2;
mergesort(a, lo, mid);
mergesort(a, mid + 1, hi);
*/

template <typename T>
void Engine::Utils::Sort::InternalMergeSort(T* o_list,
	unsigned int iStart,	
	unsigned int iEnd,
	int(*SortingFunc)(T i_A, T i_B))
{
	if (iEnd <= iStart)
		return;
	unsigned int mid = iStart + (iEnd - iStart) / 2;
	InternalMergeSort(o_list, iStart, mid, SortingFunc);
	InternalMergeSort(o_list, mid + 1, iEnd, SortingFunc);
	Merge(o_list, iStart, mid, iEnd, SortingFunc);
}


template <typename T>
void Engine::Utils::Sort::Merge(T* o_list, 
	unsigned int start, 
	unsigned int middle, 
	unsigned int end, 
	int (* SortingFunc)(T i_A, T i_B))
{
	if (SortingFunc == nullptr)
	{
		T* leftArray = new T[(middle - start) + 1];
		for (int i = 0; i < ((middle - start) + 1); i++)
			leftArray[i] = o_list[start + i];

		T* rightArray = new T[end - middle];
		for (int i = 0; i < (end - middle); i++)
			rightArray[i] = o_list[middle + 1 + i];

		unsigned leftArrayIndexer = 0;
		unsigned rightArrayIndexer = 0;
		unsigned int originalArrayCounter = 0;

		for(int i=start; i < end; i++)
		{
			if(leftArray[leftArrayIndexer] <= rightArray[rightArrayIndexer])
			{
				o_list[i] = leftArray[leftArrayIndexer];
				if(leftArrayIndexer < end)
					leftArrayIndexer++;
			}
			else
			{
				o_list[i] = rightArray[rightArrayIndexer];
				if(rightArrayIndexer < middle)
					rightArrayIndexer++;
			}
			originalArrayCounter++;
		}		

		delete leftArray;
		delete rightArray;
	}	
}



template <typename T>
void Engine::Utils::Sort::QuickSort(T* o_list,
	int iListlength,
	int (*SortFunc) (T i_A, T i_B))
{
	
}

void Engine::Utils::Sort::TestMergeSort()
{
	int a[] = { 10,12,-1,2,1,0,-18 };
	MergeSort<int>(a, 7);
}
