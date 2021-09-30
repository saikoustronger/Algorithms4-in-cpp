#pragma once

#include <vector>
#include <iostream>
#include <stack>
#include <queue>
using namespace std;

template<class Graph>
class DFP {
private:
	bool* marked;
	int* edgeTo;
	int start;
	void dfs(Graph G, int v)
	{
		marked[v] = true;

		for (int w : G.Getadj(v))
			if (!marked[w])
			{
				edgeTo[w] = v;
				dfs(G, w);
			}
	}

public:
	DFP(Graph G, int s)
	{
		marked = new bool[G.GetV()]();
		edgeTo = new int[G.GetV()]();
		start = s;
		dfs(G, s);
	}

	~DFP()
	{
		delete[] marked;
		delete[] edgeTo;
	}

	bool hasPathTo(int v)
	{
		return marked[v];
	}

	stack<int> GetPathTo(int v)
	{
		stack<int> path;
		if (!hasPathTo(v))
		{
			return path;
		}

		for (int x = v; x != start; x = edgeTo[x])
			path.push(x);
		path.push(start);
		return path;
	}
};