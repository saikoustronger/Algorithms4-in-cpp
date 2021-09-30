#include "DirectedEdge.h"




DirectedEdge::DirectedEdge(int v = 0, int w = 0, double weight = 0.0)
{
	this->v = v;
	this->w = w;
	this->weight = weight;
}

double DirectedEdge::Getweight()
{
	return weight;
}

int DirectedEdge::from()	//获得边的起点
{
	return v;
}

int DirectedEdge::to()	//获得边的终点
{
	return w;
}

string DirectedEdge::toString()		//字符串输出
{
	char str[50];
	sprintf(str, "%d-%d %.2f", v, w, weight);
	return string(str);
}

DirectedEdge null;

