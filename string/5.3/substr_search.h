#pragma once

#include "string"
#include "vector"
using namespace std;

int normal_subsearch(string pat, string txt);

class KMP
{
private:
	string pat;		//ģʽ
	vector<vector<int>> dfa;		//״̬��
public:
	KMP(string _pat);
	int search(string txt);
};