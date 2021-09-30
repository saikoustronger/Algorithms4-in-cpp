#pragma once

#include <vector>
#include <iostream>
#include <stack>
#include <queue>
using namespace std;

class Graph{
private:
	int V;
	int E;
	vector<vector<int>> adj;

public:
	Graph(int V);
	
	
	Graph(istream& in);
	

	int GetV();
	

	int GetE();
	
	void addEdge(int v, int w);
	
	
	vector<int>& Getadj(int v);
	
};








