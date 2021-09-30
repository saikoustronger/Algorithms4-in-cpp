#pragma once
#include <iostream>
#include "Edge.h"
#include <vector>
using namespace std;

class EdgeWeightGraph
{
private:
	int V;	//顶点总数
	int E;	//边的总数
	vector<vector<Edge>> adj;	//邻接表
public:
	EdgeWeightGraph(int V);

	EdgeWeightGraph(istream& in);	//输入流构造图

	int GetV();
	int GetE();
	
	void addEdge(Edge e);
	
	vector<Edge> Getadj(int v);

	vector<Edge> edges();	//返回所有边
	
};