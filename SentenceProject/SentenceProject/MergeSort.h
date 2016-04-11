// MergeSort.h
// Jack Murdock

#ifndef __MERGESORT_CLASS_H__
#define __MERGESORT_CLASS_H__
#include <vector>
#include <thread>

using namespace std;

void merge(vector<vector<unsigned long long>>& vec, int start, int mid, int end)
{
	vector<vector<unsigned long long>> one(vec.begin() + start, vec.begin() + mid + 1);
	vector<vector<unsigned long long>> two(vec.begin() + mid + 1, vec.begin() + end + 1);

	int a = 0;
	int b = 0;
	int index = start;
	while (a < one.size() && b < two.size())
	{
		if (one[a].size() < two[b].size())
			vec[index++] = one[a++];
		else
			vec[index++] = two[b++];
	}

	// merge the left-over elements
	while (a < one.size())
		vec[index++] = one[a++];
	while (b < two.size())
		vec[index++] = two[b++];
}

void merge_sort(vector<vector<unsigned long long>>& vec, int start, int end)
{
	if (start >= end){
		return;
	}

	int mid = start + (end - start) / 2;

	thread first(merge_sort, ref(vec), start, mid);
	thread second(merge_sort, ref(vec), mid + 1, end);
	first.join();
	second.join();

	merge(vec, start, mid, end);
}

#endif /*__MERGESORT_CLASS_H__*/