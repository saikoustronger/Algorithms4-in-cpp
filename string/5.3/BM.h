#pragma once

#include "memory"
#include "string"
using namespace std;

#define R 256
class BM
{
private:
	unique_ptr<int> right;	//移动数组
	string pat;				//模式
public:
	BM(string _pat);
	int search(string txt);
};