#pragma once

#include "vector"
#include "iostream"
#include "string"
using namespace std;


template<class val>
class TrieST
{
private:
	const static int R = 256;

	class Node					// 在类中定义
	{
	public:
		val* value;				// 值的指针
		vector<Node*> next;		// 大小为256 + 1，引索代指字符
		Node()
		{
			value = nullptr;
			next.resize(R + 1);
			for (int i = 0; i <= R; i++)
				next[i] = nullptr;
		}
	};

	Node* root;

	Node* get(Node* node, string s, int d)
	{
		if (node == nullptr)
			return nullptr;
		if (d == s.length())
			return node;
		return get(node->next[s[d]], s, d + 1);
	}

	Node* put(Node* node, string s, val value, int d)
	{
		if (node == nullptr)
			node = new Node();
		if (d == s.length())
		{
			node->value = new val(value);
			return node;
		}
		node->next[s[d]] = put(node->next[s[d]], s, value, d + 1);
		return node;
	}

	int size(Node* node)
	{
		if (node == nullptr)
			return 0;
		int cnt = 0;
		for (int c = 1; c <= R; c++)
			cnt += size(node->next[c]);
		return cnt;
	}

	void collect(Node* node, string pre, vector<string>& find)
	{
		if (node == nullptr)
			return;
		if (node->value != nullptr)
			find.push_back(pre);

		for (int c = 0; c <= R; c++)
			collect(node->next[c], pre + (char)c, find);
	}

	void collect(Node* node, string pre, string pat, vector<string>& q)
	{
		if (node == nullptr)
			return;
		uint32_t d = pre.length();
		if (d == pat.length() && node->value != nullptr)
			q.push_back(pre);
		if (d == pat.length())
			return;

		int next = pat[d];
		for (int c = 0; c <= R; c++)
			if (next == '.' || next == c)
				collect(node->next[c], pre + (char)c, pat, q);
	}

	int search(Node* node, string s, int d, int length)
	{
		if (node == nullptr)
			return length;
		if (node->value != nullptr)
			length = d;
		if (d == s.length())
			return length;
		return search(node->next[s[d]], s, d + 1, length);
	}

	Node* Delete(Node* node, string key, int d)
	{
		if (node == nullptr)
			return nullptr;
		if (d == key.length())
			node->value = nullptr;
		else
		{
			char c = key[d];
			node->next[c] = Delete(node->next[c], key, d + 1);
		}

		if (node->value != nullptr)
			return node;
		for (int i = 0; i <= R; i++)
			if (node->next[i] != nullptr)
				return node;
		delete node;
		return nullptr;
	}
public:
	TrieST()
	{
		root = new Node();
	}

	val* get(string s)
	{
		Node* node = get(root, s, 0);
		if (node == nullptr)
			return nullptr;
		return node->value;
	}

	void put(string s, val value)
	{
		root = put(root, s, value, 0);
	}

	int size()
	{
		return size(root);
	}

	vector<string> KeysWithPrefix(string pre)
	{
		vector<string> find;
		collect(get(root, pre, 0), pre, find);
		return find;
	}

	vector<string> Keys()
	{
		return KeysWithPrefix("");
	}

	vector<string> KeysWithMatch(string pat)
	{
		vector<string> out;
		collect(root, "", pat, out);
		return out;
	}

	string LongestPrefixOf(string s)
	{
		int length = search(root, s, 0, 0);
		return s.substr(0, length);
	}

	void Delete(string key)
	{
		root = Delete(root, key, 0);
	}
};

