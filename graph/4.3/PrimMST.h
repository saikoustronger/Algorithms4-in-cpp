#pragma once

#include <map>
#include <vector>
#include "EdgeWeightGraph.h"
#include "DIY_RBT.h"
using namespace std;
class PrimMST
{
private:
	vector<Edge> edgeTo;
	vector<double> distTo;
	vector<bool> marked;
	RB_TREE<int, Edge> pq;
	void visit(EdgeWeightGraph G, int v)
	{
		marked[v] = true;
		for (Edge e : G.Getadj(v))
		{
			int w = e.other(v);
			if (marked[w])
				continue;
			if (e.Getweight() < distTo[w])
			{
				edgeTo[w] = e;
				distTo[w] = e.Getweight();
				if(pq.)
			}
		}
	}
public:
	PrimMST(EdgeWeightGraph G)
	{
		edgeTo.resize(G.GetV());
		distTo.resize(G.GetV());
		marked.resize(G.GetV());
		for (int v = 0; v < G.GetV(); v++)
		{
			distTo[v] = INFINITY;
		}
		distTo[0] = 0.0;
		pq.Insert()
	}
};