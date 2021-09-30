#pragma once

#include <vector>
#include <iostream>
#include <stack>
#include <queue>
using namespace std;
template<class Graph>
class BFS
{
private:
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
	BFS(Graph G, int s)
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

	bool ismarked(int w)
	{
		return marked[w];
	}
};