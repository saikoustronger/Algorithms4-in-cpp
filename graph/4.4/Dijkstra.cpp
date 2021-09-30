#include "Dijkstra.h"


class Dijkstra
{
private:
	vector<DirectedEdge> edgeTo;
	vector<double> distTo;
	IndexMinpq<double>* pq;
	void relax(EdgeWeightedDigraph G, int v);
public:
	Dijkstra(EdgeWeightedDigraph G, int s);

};

Dijkstra::Dijkstra(EdgeWeightedDigraph G, int s)
{
	edgeTo.resize(G.GetV());
	distTo.resize(G.GetV());
	pq = new IndexMinpq<double>(G.GetV());

	for (int v = 0; v < G.GetV(); v++)
	{
		distTo[v] = DBL_MAX;
	}
	distTo[s] = 0.0;
	pq->insert(s, 0.0);
	while (!pq->isEmpty())
	{
		relax(G, pq->delMin());
	}
}

void Dijkstra::relax(EdgeWeightedDigraph G, int v)
{
	for (DirectedEdge e : G.Getadj(v))
	{
		int w = e.to();
		if (distTo[w] > distTo[v] + e.Getweight())
		{
			distTo[w] = distTo[v] + e.Getweight();
			edgeTo[w] = e;
			if (pq->contains(w))
				pq->change(w, distTo[w]);
			else
				pq->insert(w, distTo[w]);
		}
	}
}