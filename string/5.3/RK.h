#pragma once
#include "string"
using namespace std;

class RK
{
private:
	string pat;
	long patHash;	//模式的散列值
	int M;			//模式长度
	long Q;			//很大的素数
	const static int R = 256;	//进制
	long RM;		// R^M-1 % Q

	long hash(string key, int M);
public:
	RK(string pat);
	bool check(int i);
	int search(string txt);
};