#include "string_algorithms.h"
#include "iostream"
using namespace std;

int MSD::charAt(string s, int d)
{
	if (d < s.length())
		return s[d];
	else
		return -1;
}

void MSD::sort(vector<string>& a)
{
	int n = a.size();
	if (n < 0)
		throw "out of rage";
	aux.resize(n);
	sort(a, 0, n - 1, 0);
}

void MSD::sort(vector<string>& a, int lo, int hi, int d)
{
	if (hi <= lo + M)
	{
		insert_sort(a, lo, hi, d);
		return;
	}

	int* count = new int[R + 2]();
	for (int i = lo; i <= hi; i++)
	{
		count[charAt(a[i], d) + 2]++;
	}

	for (int r = 0; r < R + 1; r++)
		count[r + 1] += count[r];
	for (int i = lo; i <= hi; i++)
	{
		aux[count[charAt(a[i], d) + 1]++] = a[i];
	}

	for (int i = lo; i <= hi; i++)
		a[i] = aux[i - lo];
	for (int r = 0; r < R; r++)
		sort(a, lo + count[r], lo + count[r + 1] - 1, d + 1);
	delete[]count;
}

void MSD::insert_sort(vector<string>& a, int lo, int hi, int d)
{
	for (int i = lo; i <= hi; i++)
	{
		for (int j = i; j > lo && less(a[j], a[j - 1], d); j--)
		{
			swap(a[j], a[j - 1]);
		}
	}
}

bool MSD::less(string v, string w, int d)
{
	bool a = (v.substr(d) < w.substr(d));
	return (v.substr(d) < w.substr(d));
}




int Quick3string::charAt(string s, int d)
{
	if (d < s.length())
		return s[d];
	else
		return -1;
}

void Quick3string::sort(vector<string>& a)
{
	sort(a, 0, a.size() - 1, 0);
}

void Quick3string::sort(vector<string>& a, int lo, int hi, int d)
{
	if (lo >= hi)
		return;
	int v = charAt(a[lo], d);	//ÇÐ·Ö
	int lt = lo;
	int gt = hi;
	int i = lo + 1;

	// a[lo...lt-1] < v = a[lt...gt] < a[gt+1...hi]

	while (i <= gt)
	{
		int t = charAt(a[i], d);
		if (t < v)
			swap(a[i++], a[lt++]);
		else if (t > v)
			swap(a[i], a[gt--]);
		else
			i++;
	}

	cout << "This turn lo = " << lo << ", hi = " << hi << ", d = " << d  << ", v = " << (char)v << endl;
	for (string& str : a)
	{
		cout << str << endl;
	}
	cout << "Next sort turn" << endl;

	sort(a, lo, lt - 1, d);
	if (v >= 0)
		sort(a, lt, gt, d + 1);
	sort(a, gt + 1, hi, d);
}






vector<string> string_algorithms::LSD(vector<string> strs, int length)
{
	int num = strs.size();
	int R = 256;
	
	vector<string> sort_out;
	sort_out.resize(num);
	for (int d = length - 1; d >= 0; d--)
	{
		int* count = new int[R+1]();
		for (int i = 0; i < num; i++)
		{
			count[strs[i][d] + 1]++;
		}

		for (int r = 0; r < R; r++)
			count[r + 1] += count[r];

		for (int i = 0; i < num; i++)
			sort_out[count[strs[i][d]]++] = strs[i];
		for (int i = 0; i < num; i++)
			strs[i] = sort_out[i];
		delete []count;
	}

	return strs;
}

vector<string> string_algorithms::_MSD(vector<string> strs)
{
	MSD MSD1;
	MSD1.sort(strs);
	return strs;
}

void string_algorithms::Quick3(vector<string>& str)
{
	Quick3string q;
	q.sort(str);
}