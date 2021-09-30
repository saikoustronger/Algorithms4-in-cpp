#pragma once

#include "vector"
#include "string"
using namespace std;

template<class val>
class TST
{
private:
	class Node
	{
	public:
		char c;
		Node* left;
		Node* mid;
		Node* right;
		val* value;
		Node()
		{
			left = right = mid = nullptr;
			value = nullptr;
		}
	};

	Node* root;
	Node* get(Node* node, string key, int d)
	{
		if (node == nullptr)
			return nullptr;
		char c = key[d];
		if (c < node->c)
			return get(node->left, key, d);
		else if (c > node->c)
			return get(node->right, key, d);
		else if (d < key.length() - 1)
			return get(node->mid, key, d + 1);
		else
			return node;

	}

	Node* put(Node* node, string key, val value, int d)
	{
		char c = key[d];
		if (node == nullptr)
		{
			node = new Node();
			node->c = c;
		}

		if (c < node->c)
			node->left = put(node->left, key, value, d);
		else if (c > node->c)
			node->right = put(node->right, key, value, d);
		else if (d < key.length() - 1)
			node->mid = put(node->mid, key, value, d + 1);
		else
			node->value = new val(value);
		return node;
	}
public:
	TST()
	{
		root = nullptr;
	}
	val* get(string key)
	{
		Node* node = get(root, key, 0);
		if (node == nullptr)
			return nullptr;
		return node->value;
	}

	void put(string key, val value)
	{
		root = put(root, key, value, 0);
	}
};
