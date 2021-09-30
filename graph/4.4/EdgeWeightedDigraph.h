#pragma once

#include "DirectedEdge.h"
#include <vector>
#include <iostream>
using namespace std;


class EdgeWeightedDigraph
{
private:
	int V;	//顶点数量
	int E;	//边的数量
	vector<vector<DirectedEdge>> adj;
public:
	EdgeWeightedDigraph(int V);

	EdgeWeightedDigraph(istream& in);	//输入流构造图
	void addEdge(DirectedEdge e);
	int GetV();
	int GetE();
	vector<DirectedEdge> edges();
	vector<DirectedEdge> Getadj(int v);
};