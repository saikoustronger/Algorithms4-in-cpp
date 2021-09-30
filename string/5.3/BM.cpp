#include "BM.h"

BM::BM(string pat)
{
	this->pat = pat;
	int M = pat.length();
	right.reset(new int[R + 1]);

	for (int c = 0; c <= R; c++)
		right.get()[c] = -1;		//模式没有的设为-1
	for (int j = 0; j < M; j++)
		right.get()[pat[j]] = j;	//模式有的，设为最右的位置
}

int BM::search(string txt)
{
	int N = txt.length();
	int M = pat.length();
	
	int skip;	//移动距离
	for (int i = 0; i <= N - M; i += skip)
	{
		skip = 0;
		for (int j = M - 1; j >= 0; j--)
		{
			if (pat[j] != txt[i + j])
			{
				skip = j - right.get()[txt[i + j]];
				if (skip < 1)
					skip = 1;	//至少向前移动一位
				break;
			}
		}
		if (skip == 0)
			return i;	//找到
	}
	return N;	//未找到
}