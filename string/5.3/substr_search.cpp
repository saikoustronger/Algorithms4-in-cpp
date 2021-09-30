#include "substr_search.h"

int normal_subsearch(string pat, string txt)
{
	int m = pat.length();
	int n = txt.length();

	for (int i = 0; i <= n - m; i++)
	{
		int j = 0;
		for (; j < m; j++)
		{
			if (pat[j] != txt[i + j])
				break;
		}
		if (j == m)
			return i;
	}
	return n;			// 没找到返回文本长度
}


KMP::KMP(string _pat)
{
	pat = _pat;
	int R = 256;
	int M = _pat.length();
	dfa.resize(R);
	for (vector<int>& a : dfa)
		a.resize(M);
	dfa[_pat[0]][0] = 1;
	int X = 0;
	for (int j = 1; j < M; j++)
	{
		for (int c = 0; c < R; c++)
			dfa[c][j] = dfa[c][X];
		dfa[_pat[j]][j] = j + 1;
		X = dfa[_pat[j]][X];	//更新X始终是对应j范围内的最长前后公共子字符串长度
								//如果j处出现一样的字符，则代表最长前后公共子字符串长度+1

	}
}
int KMP::search(string txt)
{
	int N = txt.length();
	int M = pat.length();
	int i = 0, j = 0;
	for (; i < N && j < M; i++)
	{
		j = dfa[txt[i]][j];
	}
	if (j == M)
		return i - M;	//识别到返回模式在文本中开始位置
	else
		return N;
}