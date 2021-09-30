#pragma once

#include <vector>
#include <iostream>
#include <stack>
#include <queue>
using namespace std;
template<class Graph>
class DFS {
private:
	vector<bool> marked;
	int count;
	void dfs(Graph G, int v)
	{
		marked[v] = true;
		count++;
		for (int w : G.Getadj(v))
			if (!marked[w])
				dfs(G, w);
	}
public:
	DFS(Graph G, int s)
	{
		count = 0;
		marked.resize(G.GetV());
		dfs(G, s);
	}

	DFS(Graph G, vector<int> s)
	{
		marked.resize(G.GetV());
		for(int v : s)
			if(!marked[v])
				dfs(G, v);
	}

	

	

	bool ismarked(int w)
	{
		return marked[w];
	}

	int GetCount() { return count; }
};