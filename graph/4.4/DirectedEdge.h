#pragma once
#include <string>
using namespace std;
class DirectedEdge
{
private:
	int v;	//起点
	int w;	//终点
	double weight;	//权重
public:
	DirectedEdge(int v, int w, double weight);

	double Getweight();

	int from();	//获得边的起点

	int to();	//获得边的终点
	

	string toString();		//字符串输出
};


extern DirectedEdge null;