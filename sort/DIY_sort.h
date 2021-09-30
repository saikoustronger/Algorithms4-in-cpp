#pragma once
#include <iostream>
#include <array>
#include <vector>
using namespace std;




template<typename val>
class DIY_sort {
protected:
	vector<val> Sort_Array;
public:
	DIY_sort(vector<val>& vals);
	void print();
	void Selection_Sort();

	void Curve_Sort();

	void Sier_Sort();

	void Merge_Sort();

	void Fast_Sort();
private:
	void Merge_Down(int lo, int hi);
	void Merge(int lo, int mid, int hi);

	void Fast_Sort_Down(int lo, int hi);
	int Partition(int lo, int hi);

	
	
};

template<typename val>
DIY_sort<val>::DIY_sort(vector<val>& vals)
{
	Sort_Array = vals;
}

template<typename val>
void DIY_sort<val>::print()
{
	for (val Val : Sort_Array)
		cout << Val << " ";
	cout << endl;
}


template<typename val>
void DIY_sort<val>::Selection_Sort()
{
	int Min = 0;
	for (int i = 0; i < Sort_Array.size() - 1; i++)
	{
		Min = i;
		for (int j = i + 1; j < Sort_Array.size(); j++)
			if (Sort_Array[i] > Sort_Array[j])
				Min = j;
		swap(Sort_Array[i], Sort_Array[Min]);
	}
}

template<typename val>
void DIY_sort<val>::Curve_Sort()
{
	for (int i = 1; i < Sort_Array.size(); i++)
	{
		for (int j = i; j > 0 && Sort_Array[j - 1] > Sort_Array[j]; j--)
			swap(Sort_Array[j-1], Sort_Array[j]);
	}
}

template<typename val>
void DIY_sort<val>::Sier_Sort()
{
	int h = 1;
	while (3 * h < Sort_Array.size()) h *= 3;

	for (; h != 0; h /= 3)
	{
		for (int i = h; i < Sort_Array.size(); i++)
		{
			for (int j = i; j >= h && Sort_Array[j - h] > Sort_Array[j]; j -= h)
				swap(Sort_Array[j - h], Sort_Array[j]);
		}
	}
}

template<typename val>
void DIY_sort<val>::Merge_Sort()
{
	Merge_Down(0, Sort_Array.size()-1);
}

template<typename val>
void DIY_sort<val>::Merge_Down(int lo, int hi)
{
	if (lo >= hi) return;
	int mid = lo + (hi - lo) / 2;
	Merge_Down(lo, mid);
	Merge_Down(mid + 1, hi);
	Merge(lo, mid, hi);
}

template<typename val>
void DIY_sort<val>::Merge(int lo, int mid, int hi)
{
	vector<val> copy(Sort_Array.begin() + lo, Sort_Array.begin() + hi);
	vector<val> cpy(Sort_Array);
	int i = lo, j = mid + 1;
	for (int k = lo; k <= hi; k++)
	{
		if (i > mid) Sort_Array[k] = cpy[j++];
		else if (j > hi) Sort_Array[k] = cpy[i++];
		else if (cpy[i] > cpy[j]) Sort_Array[k] = cpy[j++];
		else Sort_Array[k] = cpy[i++];
	}
}

template<typename val>
void DIY_sort <val>::Fast_Sort()
{
	Fast_Sort_Down(0, this->Sort_Array.size() - 1);
}

template<typename val>
void DIY_sort<val>::Fast_Sort_Down(int lo, int hi)
{
	if (lo >= hi) return;
	int j = Partition(lo, hi);
	Fast_Sort_Down(lo, j - 1);
	Fast_Sort_Down(j + 1, hi);
}

template<typename val>
int DIY_sort<val>::Partition(int lo, int hi)
{
	
	
	int i = lo, j = hi + 1;
	vector<val>& sort_qoute = Sort_Array;
	val partition_value = sort_qoute[lo];

	while (true)
	{
		while (sort_qoute[++i] < partition_value)
		{
			if (i == hi)
				break;
		}
		
		while (sort_qoute[--j] > partition_value)
		{
			if (j == lo)
				break;
		}
		if (i >= j) break;
		swap(sort_qoute[i], sort_qoute[j]);
	}
	swap(sort_qoute[lo], sort_qoute[j]);
	return j;
}