#include "EdgeWeightGraph.h"


EdgeWeightGraph::EdgeWeightGraph(int V)
{
	this->V = V;
	this->E = 0;
	adj.resize(V);
}

EdgeWeightGraph::EdgeWeightGraph(istream& in)	//输入流构造图
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
		addEdge(Edge(v, w, temp_weight));
	}
}

int EdgeWeightGraph::GetV()
{
	return V;
}

int EdgeWeightGraph::GetE()
{
	return E;
}

void EdgeWeightGraph::addEdge(Edge e)
{
	int v = e.either(), w = e.other(v);
	adj[v].push_back(e);
	adj[w].push_back(e);
	E++;
}

vector<Edge> EdgeWeightGraph::Getadj(int v)
{
	return adj[v];
}

vector<Edge> EdgeWeightGraph::edges()	//返回所有边
{
	vector<Edge> ed;
	for (int v = 0; v < V; v++)
	{
		for (Edge e : adj[v])
			if (e.other(v) > v)
				ed.push_back(e);
	}
	return ed;
}
