#pragma once
#include <vector>
#include <queue>
#include "Minpq.h"
#include "EdgeWeightGraph.h"
using namespace std;
class KruskalMST
{
private:
	queue<Edge> mst;
public:
	KruskalMST(EdgeWeightGraph G)
	{
		Minpq<Edge> pq;
		for (Edge e : G.edges())
		{
			pq.Insert(e);
		}

		Uf uf(G.GetV());				//来自Union-find算法
		while (!pq.isEmpty() && mst.size() < G.GetV() - 1)
		{
			Edge e = pq.Delete_Min();
			int v = e.either(), w = e.other(v);
			if (uf.connected(v, w))		//检测两个点是否被合并,是则忽略这个边，防止成环 
				continue;
			uf.Union(v, w);				//合并分量
			mst.push(e);
		}
	}
	queue<Edge> edges()
	{
		return mst;
	}
};
