#include "EdgeWeightedDigraph.h"


EdgeWeightedDigraph::EdgeWeightedDigraph(int V)
{
	this->V = V;
	this->E = 0;
	adj.resize(V);
}

EdgeWeightedDigraph::EdgeWeightedDigraph(istream& in)	//输入流构造图
{
	int tempV, tempE, v, w;
	double temp_weight;
	in >> tempV >> tempE;
	V = tempV;
	E = tempE;
	adj.resize(tempV);
	for (int i = 0; i < tempE; i++)
	{
		in >> v >> w >> temp_weight;
		addEdge(DirectedEdge(v, w, temp_weight));
	}
}

void EdgeWeightedDigraph::addEdge(DirectedEdge e)
{
	adj[e.from()].push_back(e);
	E++;
}

int EdgeWeightedDigraph::GetV()
{
	return V;
}

int EdgeWeightedDigraph::GetE()
{
	return E;
}
vector<DirectedEdge> EdgeWeightedDigraph::edges()
{
	vector<DirectedEdge> temp;
	for (int w = 0; w < V; w++)
		for (DirectedEdge e : Getadj(w))
			temp.push_back(e);
	return temp;
}

vector<DirectedEdge> EdgeWeightedDigraph::Getadj(int v)
{
	return adj[v];
}


