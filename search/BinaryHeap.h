#pragma once
#include <iostream>
#include <stack>
#include <vector>
using namespace std;

template<typename val>
class DIY_BinaryHeap
{
protected:
	val* Binary_Heap;
	int Current_Length;
	int Max_Length;
public:
	DIY_BinaryHeap(val Array[], int ArraySize, int Max_Length);
	~DIY_BinaryHeap();
	void Insert(val value);
	void Delete_Max(val& object);
	vector<val> Sort();
	void print(vector<val>& sortout);
private:
	int father(int pos);
	int LeftChild(int pos);
	int RightChild(int pos);
	void swim(int pos);
	void down(int pos);
};

template<typename val>
DIY_BinaryHeap<val>::DIY_BinaryHeap(val Array[], int ArraySize, int Max)
{
	Binary_Heap = new val[Max + 1];
	Current_Length = ArraySize;
	Max_Length = Max;
	for (int i = ArraySize; i > 0; i--)
	{
		Binary_Heap[i] = Array[i - 1];
		down(i);
	}
}

template<typename val>
DIY_BinaryHeap<val>::~DIY_BinaryHeap()
{
	delete Binary_Heap;
}

template<typename val>
void DIY_BinaryHeap<val>::Insert(val value)
{
	if (Current_Length == Max_Length)
	{
		cout << "The heap is full" << endl;
		return;
	}

	Current_Length++;
	Binary_Heap[Current_Length] = value;
	swim(Current_Length);

}

template<typename val>
void DIY_BinaryHeap<val>::Delete_Max(val& object)
{
	if (Current_Length == 0)
	{
		cout << "The heap is empty" << endl;
	}

	object = Binary_Heap[1];
	Binary_Heap[1] = Binary_Heap[Current_Length];
	Current_Length--;
	down(1);
}

template<typename val>
vector<val> DIY_BinaryHeap<val>::Sort()
{
	vector<val> Sort_output;
	stack<val> aux_stack;
	val temp;
	while (Current_Length)
	{
		Delete_Max(temp);
		aux_stack.push(temp);
	}

	while (aux_stack.size() != 0)
	{
		Sort_output.push_back(aux_stack.top());
		aux_stack.pop();
	}

	return Sort_output;
	
}

template<typename val>
int DIY_BinaryHeap<val>::father(int pos)
{
	return pos / 2;
}

template<typename val>
int DIY_BinaryHeap<val>::LeftChild(int pos)
{
	return 2 * pos;
}

template<typename val>
int DIY_BinaryHeap<val>::RightChild(int pos)
{
	return (2 * pos + 1);
}

template<typename val>
void DIY_BinaryHeap<val>::swim(int pos)
{
	if (pos == 1)
		return;
	int father = father(pos);
	if (Binary_Heap[pos] > Binary_Heap[father])
	{
		swap(Binary_Heap[pos], Binary_Heap[father]);
	}
	else
		return;
	swim(father);
}

template<typename val>
void DIY_BinaryHeap<val>::down(int pos)
{
	if (pos == Current_Length)
		return;
	int left_child = LeftChild(pos);
	if (left_child > Current_Length)
		return;
	int right_child = RightChild(pos);
	if (right_child > Current_Length)
	{
		if (Binary_Heap[pos] < Binary_Heap[left_child])
		{
			swap(Binary_Heap[pos], Binary_Heap[left_child]);
			down(left_child);
		}
		else
		{
			return;
		}
	}
	else
	{
		if (Binary_Heap[pos] < Binary_Heap[left_child] || Binary_Heap[pos] < Binary_Heap[right_child])
		{
			if (Binary_Heap[left_child] > Binary_Heap[right_child])
			{
				swap(Binary_Heap[pos], Binary_Heap[left_child]);
				down(left_child);
			}
			else
			{
				swap(Binary_Heap[pos], Binary_Heap[right_child]);
				down(right_child);
			}
		}
		else
			return;
	}
	
}

template<typename val>
void DIY_BinaryHeap<val>::print(vector<val>& Sort_output)
{
	for (auto& rin : Sort_output)
	{
		cout << rin << " ";
	}
	cout << endl;
}