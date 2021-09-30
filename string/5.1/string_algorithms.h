#pragma once

#include "string"
#include "vector"

using namespace std;


class MSD
{
private:
	int R = 256;	//字母表大小
	int M = 2;		//插入排序的阈值
	vector<string> aux;	//辅助数组
	int charAt(string s, int d);
	void sort(vector<string>& a, int lo, int hi, int d);
	void insert_sort(vector<string>& a, int lo, int hi, int d);
	bool less(string v, string w, int d);
public:
	void sort(vector<string>& a);
};

class Quick3string
{
private:
	int charAt(string s, int d);
	void sort(vector<string>& a, int lo, int hi, int d);
public:
	void sort(vector<string>& a);
};

class string_algorithms
{
public:
	vector<string> LSD(vector<string> strs, int length);
	vector<string> _MSD(vector<string> strs);
	void Quick3(vector<string>& str);
};