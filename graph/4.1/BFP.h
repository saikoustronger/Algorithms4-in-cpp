#pragma once

#include <vector>
#include <iostream>
#include <stack>
#include <queue>
using namespace std;

template<class Graph>
class BFP {
	bool* marked;
	int* edgeTo;
	int start;
	void bfs(Graph G, int s)
	{
		queue<int> q;
		marked[s] = true;
		q.push(s);
		while (!q.empty())
		{
			int v = q.front();
			q.pop();
			for (int w : G.Getadj(v))
				if (!marked[w])
				{
					edgeTo[w] = v;
					marked[w] = true;
					q.push(w);
				}
		}
	}

public:
	BFP(Graph G, int s)
	{
		marked = new bool[G.GetV()]();
		edgeTo = new int[G.GetV()]();
		start = s;
		bfs(G, s);
	}

	~BFP()
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