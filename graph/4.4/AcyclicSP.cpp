#include "DirectedEdge.h"
#include "EdgeWeightedDigraph.h"


class AcycliSP
{
private:
	vector<DirectedEdge> edgeTo;
	vector<double> distTo;

	void relax(EdgeWeightedDigraph G, int v);
public:
	AcycliSP(EdgeWeightedDigraph G, int s);
};

AcycliSP::AcycliSP(EdgeWeightedDigraph G, int s)
{
	edgeTo.resize(G.GetV());
	distTo.resize(G.GetV());
	Topological top(G);

	for (int v : top.order())
	{
		relax(G, v);
	}
}

void AcycliSP::relax(EdgeWeightedDigraph G, int v)
{
	for (DirectedEdge e : G.Getadj(v))
	{
		int w = e.to();
		if (distTo[w] > distTo[v] + e.Getweight())
		{
			distTo[w] = distTo[v] + e.Getweight();
			edgeTo[w] = e;
			
		}
	}
}