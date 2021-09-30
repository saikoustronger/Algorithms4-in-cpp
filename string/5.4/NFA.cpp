
#include "NFA.h"
#include "vector"
#include "stack"
#include "DFS.h"
NFA::NFA(string RE)
{
	M = RE.length();
	this->RE = RE;
	graph.reset(new Digraph(M + 1));
	stack<int> ops;
	for (int i = 0; i < M; i++)
	{
		int lp = i;
		if (RE[i] == '(' || RE[i] == '|')
		{
			ops.push(i);
		}
		else if (RE[i] == ')')
		{
			int Or = ops.top();
			ops.pop();
			if (RE[Or] == '|')
			{
				lp = ops.top();
				ops.pop();
				graph->addEdge(lp, Or + 1);
				graph->addEdge(Or, i);
			}
			else if (RE[Or] == '(')
				lp = Or;
			else;
		}
		if (RE[i + 1] == '*' && i < M - 1)
		{
			graph->addEdge(lp, i + 1);
			graph->addEdge(i + 1, lp);
		}
		if (RE[i] == '(' || RE[i] == '*' || RE[i] == ')')
		{
			graph->addEdge(i, i + 1);
		}
	}
}

bool NFA::recognize(string txt)
{
	DFS<Digraph> dfs(*graph.get(), 0);
	vector<int> pc;
	for (int i = 0; i < graph.get()->GetV(); i++)
		if (dfs.ismarked(i))
			pc.push_back(i);

	for (int i = 0; i < txt.length(); i++)
	{
		vector<int> match;
		for (int v : pc)
		{
			if (v == M)
				continue;
			if (RE[v] == txt[i] || RE[v] == '.')
				match.push_back(v + 1);
		}
		dfs = DFS<Digraph>(*graph.get(), match);
		pc = vector<int>();
		for (int v = 0; v < graph.get()->GetV(); v++)
		{
			if (dfs.ismarked(v))
				pc.push_back(v);
		}
		if (pc.size() == 0)
			return false;
	}

	
	for (int v : pc)
		if (v == M)
			return true;
	return false;
}