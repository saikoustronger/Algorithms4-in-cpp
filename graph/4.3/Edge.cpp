#include "Edge.h"


Edge::Edge(int v, int w, double weight)
{
	if (v < 0 || w < 0)
		throw string("vertex index must "
			"be a non-negative integer");
	this->v = v;
	this->w = w;
	this->weight = weight;
}
Edge::Edge()
{

}
double Edge::Getweight()
{
	return weight;
}

int Edge::either()	//返回一个顶点
{
	return v;
}

int Edge::other(int vertex)//返回另一个顶点
{
	if (vertex == v)
		return w;
	else if (vertex == w)
		return v;
	else
	{
		throw "Inconsistent edge";
	}
}

int Edge::compareTo(Edge that)//和另一条边比较权值
{
	if (this->Getweight() < that.Getweight())
		return -1;
	else if (this->Getweight() > that.Getweight())
		return +1;
	else
		return 0;
}

string Edge::toString()		//字符串输出
{
	char str[50];
	sprintf(str, "%d-%d %.2f", v, w, weight);
	return string(str);
}