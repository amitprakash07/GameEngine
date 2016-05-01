#ifndef __SORT_H
#define __SORT_H

namespace Engine
{
	namespace Utils
	{
		class Sort
		{
		public:
			static void TestMergeSort();

			template<typename T>
			static void MergeSort(T* o_List, int iLength, int(*SortFunc)(T i_A, T i_B) = nullptr);

			template<typename T>
			static void QuickSort(T* o_List, int iListlength, int(*SortFunc)(T i_A, T i_B) = nullptr);
		private:
			template<typename T>
			static void InternalMergeSort(T* o_list, unsigned int iStart,
				unsigned int iEnd, int(*SortingFunc)(T i_A, T i_B) = nullptr);
			template<typename T>
			static void Merge(T* o_list, unsigned int iStart,
				unsigned int middle, unsigned int iEnd,
				int(*SortingFunc)(T i_A, T i_B) = nullptr);
		};
	}
}

#endif