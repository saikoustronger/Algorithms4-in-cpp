
#include "Digraph.h"

Digraph::Digraph(int V)
{
	this->V = V; this->E = 0;
	adj.resize(V);
}

Digraph::Digraph(istream& in)
{
	int tempV, tempE, v, w;
	in >> tempV >> tempE;
	V = tempV;
	E = tempE;
	adj.resize(tempV);
	for (int i = 0; i < tempE; i++)
	{
		in >> v >> w;
		addEdge(v, w);
	}
}

int Digraph::GetV()
{
	return V;
}

int Digraph::GetE()
{
	return E;
}

void Digraph::addEdge(int v, int w)
{
	adj[v].push_back(w);
	E++;
}

vector<int>& Digraph::Getadj(int v)
{
	return adj[v];
}

Digraph Digraph::reverse()
{
	Digraph g(V);
	for (int v = 0; v < V; v++)
	{
		for (int w : Getadj(v))
			g.addEdge(w, v);
	}
	return g;
}



void DiCycle::dfs(Digraph G, int v)
{
	onStack[v] = true;
	marked[v] = true;
	for (int w : G.Getadj(v))
		if (this->hasCycle())
			return;
		else if (!marked[w])
		{
			edgeTo[w] = v;
			dfs(G, w);
		}
		else if (onStack[w])
		{
			for (int x = v; x != w; x = edgeTo[x])
				cycle.push(x);
			cycle.push(w);
			cycle.push(v);
		}
	onStack[v] = false;
}

DiCycle::DiCycle(Digraph G)
{
	marked = new bool[G.GetV()]();
	edgeTo = new int[G.GetV()]();
	onStack = new bool[G.GetV()]();

	for (int i = 0; i < G.GetV(); i++)
		if (!marked[i])
			dfs(G, i);
}
DiCycle::~DiCycle()
{
	delete[] marked;
	delete[] edgeTo;
	delete[] onStack;
}
bool DiCycle::hasCycle()
{
	return !cycle.empty();
}

stack<int> DiCycle::GetCycle()
{
	return cycle;
}
