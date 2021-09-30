#pragma once
#include <vector>
using namespace std;

#define MAX_NUM 100


template<class Key>
class IndexMinpq
{
private:
	int maxN;			//maxium num of element on pq
	int n;				//num of ele on pq
	vector<int> pq;		//pq
	vector<int> qp;		//inverse of pq
	vector<Key> keys;	//keys[i] = priority of i
public:
	IndexMinpq(int maxN = MAX_NUM)
	{
		if (maxN < 0)
			throw "MaxN is less than 0";
		this->maxN = maxN;
		n = 0;
		keys.resize(maxN + 1);
		pq.resize(maxN + 1);
		qp.resize(maxN + 1);

		for (int i = 0; i <= maxN; i++)
		{
			qp[i] = -1;
		}
	}

	bool isEmpty()
	{
		return n == 0;
	}

	bool contains(int i)
	{
		return qp[i] != -1;
	}

	int size()
	{
		return n;
	}

	bool greater(int i, int j)
	{
		return keys[pq[i]] > keys[pq[j]] > 0;
	}

	void exch(int i, int j)
	{
		int swap = pq[i];
		pq[i] = pq[j];
		pq[j] = swap;
		qp[pq[i]] = i;
		qp[pq[j]] = j;
	}

	void swim(int k)
	{
		while (k > 1 && greater(k / 2, k))
		{
			exch(k, k / 2);
			k = k / 2;
		}
	}

	void sink(int k)
	{
		while (2 * k <= n)
		{
			int j = 2 * k;
			if (j < n && greater(j, j + 1))
				j++;
			if (!greater(k, j))
				break;
			exch(k, j);
			k = j;
		}
	}

	void insert(int i, Key key)
	{
		if (contains(i))
			throw "index is already in the priority queues";
		n++;
		qp[i] = n;
		pq[n] = i;
		keys[i] = key;
		swim(n);
	}

	int minIndex()
	{
		if (n == 0)
			throw "priority queue underflow";
		return pq[1];
	}

	Key minKey()
	{
		if (n == 0)
			throw "priority queue underflow";
		return keys[pq[1]];
	}

	int delMin()
	{
		if (n == 0)
			throw "priority queue underflow";
		int min = pq[1];
		exch(1, n--);
		sink(1);
		qp[min] = -1;
		pq[n + 1] = -1;
		return min;
	}

	Key keyOf(int i)
	{
		if (!contains(i))
			throw "index isn't in pq";
		else
			return keys[i];
	}

	void changeKey(int i, Key key)
	{
		if (!contains(i))
			throw "index isn't in pq";
		keys[i] = key;
		swim(qp[i]);
		sink(qp[i]);
	}

	void change(int i, Key key)
	{
		changeKey(i, key);
	}

	void decreaseKey(int i, Key key)
	{
		if (!contains(i))
			throw "index isn't in pq";
		if (keys[i] == key)
			throw "Calling decreaseKey() with a key equal to the key in the priority queue";
		if (keys[i] < key)
			throw "Calling decreaseKey() with a key strictly greater than the key in the priority queue";
		keys[i] = key;
		swim(qp[i]);
	}

	void increaseKey(int i, Key key)
	{
		if (!contains(i))
			throw "index isn't in pq";
		if (keys[i] == key)
			throw "Calling decreaseKey() with a key equal to the key in the priority queue";
		if (keys[i] > key)
			throw "Calling decreaseKey() with a key strictly greater than the key in the priority queue";
		keys[i] = key;
		sink(qp[i]);
	}

	void delete(int i)
	{
		if (!contains(i))
			throw "index isn't in pq";
		int index = qp[i];
		exch(index, n--);
		swim(index);
		sink(index);
		qp[i] = -1;

	}

	
};