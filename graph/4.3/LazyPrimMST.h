#pragma once
#include <iostream>
#include <queue>
#include <vector>
#include <Minpq.h>
#include "EdgeWeightGraph.h"
using namespace std;


class LazyPrimMST
{
private:
	bool* marked;			//表示顶点是否在MST
	vector<Edge> mst;		//储存MST的边
	Minpq<Edge> pq;//储存所有横切边
	void visit(EdgeWeightGraph G, int v)//标记顶点，并将未被标记的邻接边加入优先队列
	{
		marked[v] = true;
		for (Edge e : G.Getadj(v))
		{
			if (!marked[e.other(v)])
			{
				pq.Insert(e);
			}
		}
	}
public:
	LazyPrimMST(EdgeWeightGraph G)
	{
		marked = new bool[G.GetV()];
		visit(G, 0);
		while (!pq.isEmpty())
		{
			Edge e = pq.Delete_Min();

			int v = e.either(), w = e.other(v);
			if (marked[v] && marked[w])
				continue;
			mst.push_back(e);
			if (!marked[v])
				visit(G, v);
			if (!marked[w])
				visit(G, w);
		}
	}

	vector<Edge> edges()
	{
		return mst;
	}
};