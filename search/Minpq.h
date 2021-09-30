#pragma once

#include <iostream>
#include <stack>
#include <vector>
using namespace std;
#define PQ_LENGTH 100
template<typename val>
class Minpq
{
protected:
	val* Binary_Heap;
	int Current_Length;
	int Max_Length;
public:
	Minpq(val Array[], int ArraySize, int Max_Length);
	Minpq()
	{
		Max_Length = PQ_LENGTH;
		Current_Length = 0;
		Binary_Heap = new val[PQ_LENGTH + 1];
	}
	Minpq(int m_length)
	{
		Max_Length = m_length;
		Current_Length = 0;
		Binary_Heap = new val[m_length + 1];
	}
	~Minpq();

	void Insert(val value);
	val Delete_Min();
	vector<val> Sort();
	void print();
	bool isEmpty()
	{
		return (Current_Length == 0);
	}
	int size()
	{
		return Current_Length;
	}
private:
	int father(int pos);
	int LeftChild(int pos);
	int RightChild(int pos);
	void swim(int pos);
	void down(int pos);
	bool less(int i, int j)
	{
		return Binary_Heap[i]->compareTo(Binary_Heap[j]) < 0;
	}
	
};

template<typename val>
Minpq<val>::Minpq(val Array[], int ArraySize, int Max)
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
Minpq<val>::~Minpq()
{
	delete Binary_Heap;
}

template<typename val>
void Minpq<val>::Insert(val value)
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
val Minpq<val>::Delete_Min()
{
	val out;
	if (Current_Length == 0)
	{
		cout << "The heap is empty" << endl;
	}

	out = Binary_Heap[1];
	Binary_Heap[1] = Binary_Heap[Current_Length];
	Current_Length--;
	down(1);
	cout << "after delete:";
	print();
	return out;
}

template<typename val>
vector<val> Minpq<val>::Sort()
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
int Minpq<val>::father(int pos)
{
	return pos / 2;
}

template<typename val>
int Minpq<val>::LeftChild(int pos)
{
	return 2 * pos;
}

template<typename val>
int Minpq<val>::RightChild(int pos)
{
	return (2 * pos + 1);
}

template<typename val>
void Minpq<val>::swim(int pos)
{
	if (pos == 1)
		return;
	int _father = father(pos);
	if (less(pos , _father))
	{
		swap(Binary_Heap[pos], Binary_Heap[_father]);
	}
	else
		return;
	swim(_father);
}

template<typename val>
void Minpq<val>::down(int pos)
{
	if (pos == Current_Length)
		return;
	int left_child = LeftChild(pos);
	if (left_child > Current_Length)
		return;
	int right_child = RightChild(pos);
	if (right_child > Current_Length)
	{
		if (less(left_child, pos))
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
		if (less(left_child, pos) || less(right_child, pos))
		{
			if (less(right_child, left_child))
			{
				swap(Binary_Heap[pos], Binary_Heap[right_child]);
				down(right_child);
			}
			else
			{
				swap(Binary_Heap[pos], Binary_Heap[left_child]);
				down(left_child);
			}
		}
		else
			return;
	}

}

template<typename val>
void Minpq<val>::print()
{
	for (int i = 1; i <= Current_Length; i++)
	{
		cout << Binary_Heap[i]->Getfreq() << " ";
	}
	cout << endl;
}