#include "RK.h"

long RK::hash(string key, int M)
{
	long h = 0;
	for (int j = 0; j < M; j++)
		h = (R * h + key[j]) % Q;
	return h;
}

RK::RK(string pat)
{
	this->pat = pat;
	M = pat.length();
	Q = 9999991;
	RM = 1;

	for (int i = 1; i <= M - 1; i++)
		RM = (R * RM) % Q;		//用于减去第一个数字的结果
	patHash = hash(pat, M);
}

bool RK::check(int i)
{
	return true;
}

int RK::search(string txt)
{
	int N = txt.length();
	long txtHash = hash(txt, M);
	if (patHash == txtHash && check(0))
		return 0;	//初始就匹配成功
	for (int i = M; i < N; i++)
	{
		//减去第一个数字，再加上最后一个数字
		txtHash = (txtHash + Q - RM * txt[i - M] % Q) % Q;	//加上Q是为了保持正数，无影响
		txtHash = (txtHash * R + txt[i]) % Q;
		if (patHash == txtHash)
			if (check(i - M + 1))
				return i - M + 1;
	}
	return N;
}