
#include "Graph.h"

Graph::Graph(int V)
{
	this->V = V; this->E = 0;
	adj.resize(V);
}

Graph::Graph(istream& in)
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

int Graph::GetV()
{
	return V;
}

int Graph::GetE()
{
	return E;
}

void Graph::addEdge(int v, int w)
{
	adj[v].push_back(w);
	adj[w].push_back(v);
	E++;
}

vector<int>& Graph::Getadj(int v)
{
	return adj[v];
}
