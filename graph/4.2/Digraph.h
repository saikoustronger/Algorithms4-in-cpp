#pragma once

#include <vector>
#include <iostream>
#include <stack>
#include <queue>
using namespace std;

class Digraph {
private:
	int V;
	int E;
	vector<vector<int>> adj;

public:
	Digraph(int V);
	Digraph(istream& in);
	
	int GetV();
	
	int GetE();
	void addEdge(int v, int w);

	vector<int>& Getadj(int v);
	
	Digraph reverse();
	
};



class DiCycle {
private:
	bool* marked;
	int* edgeTo;
	stack<int> cycle;
	bool* onStack;


	void dfs(Digraph G, int v);

public:
	DiCycle(Digraph G);
	~DiCycle();
	bool hasCycle();
	
	stack<int> GetCycle();
};