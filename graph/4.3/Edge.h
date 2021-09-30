#pragma once

#include <iostream>
#include <string>
#include <atlstr.h>
using namespace std;

class Edge
{
private:
	double weight;
	int v;
	int w;
public:
	Edge(int v, int w, double weight);

	Edge();
	double Getweight();
	

	int either();	//返回一个顶点
	

	int other(int vertex);//返回另一个顶点
	

	int compareTo(Edge that);//和另一条边比较权值
	
	
	string toString();		//字符串输出
	
};