#pragma once

#include "Digraph.h"
#include "string"
#include "memory"

using namespace std;
class NFA
{
private:
	string RE;		//正则表达式
	int M;			//模式长度
	unique_ptr<Digraph> graph;	//构造自动机用的图
public:
	NFA(string RE);
	bool recognize(string txt);
};