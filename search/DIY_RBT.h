#pragma once

#include <iostream>

using namespace std;
#define RB_RED   1
#define RB_BLACK 0
#define NULL -1


template<class val, class key>
class RB_TREE;

template<class val, class key>
class Node {
private:
	key keyval;
	val value;
	Node* left, * right;
	int node_num;
	bool color;
	friend class RB_TREE<val, key>;

public:
	Node(val value_, key keyval_, bool color_ = RB_BLACK, int num = 0)
		:color(color_), keyval(keyval_), value(value_), node_num(num), left(nullptr), right(nullptr){}
	key& GetKey()
	{
		return keyval;
	}

	val& GetVal()
	{
		return value;
	}
};

template<class val, class key>
class RB_TREE {
private:
	Node<val, key>* root;
	bool isRed(Node<val, key>* node)
	{
		if (node == nullptr)
			return false;
		return node->color == RB_RED;
	}

	int size(Node<val, key>* node)
	{
		if (node == nullptr)
			return 0;
		return 1 + size(node->left) + size(node->right);
	}
	Node<val, key>* RotateLeft(Node<val, key>* node)
	{
		Node<val, key>* temp = node->right;
		node->right = temp->left;
		temp->left = node;
		temp->color = node->color;
		node->color = RB_RED;
		temp->node_num = 1 + size(temp->left) + size(temp->right);
		return temp;
	}

	Node<val, key>* RotateRight(Node<val, key>* node)
	{
		Node<val, key>* temp = node->left;
		node->left = temp->right;
		temp->right = node;
		temp->color = node->color;
		node->color = RB_RED;
		temp->node_num = 1 + size(temp->left) + size(temp->right);
		return temp;
	}

	void FlipColors(Node<val, key>* node)
	{
		node->color = RB_RED;
		node->left->color = RB_BLACK;
		node->right->color = RB_BLACK;
	}

	void _FlipColors(Node<val, key>* node)
	{
		node->color = !node->color;
		node->left->color = !node->left->color;
		node->right->color = !node->right->color;
	}

	void aux_deleteall(Node<val, key>* node)
	{
		if (node == nullptr) return;
		if (node->left != nullptr) aux_deleteall(node->left);
		if (node->right != nullptr) aux_deleteall(node->right);
		delete node;
	}

	Node<val, key>* put(Node<val, key>* node, key keyval, val value)
	{
		if (node == nullptr)
			return new Node<val, key>(value, keyval, RB_RED, 1);
		if (keyval < node->keyval) node->left = put(node->left, keyval, value);
		else if (keyval > node->keyval) node->right = put(node->right, keyval, value);
		else node->value = value;

		if (!isRed(node->left) && isRed(node->right))
			node = RotateLeft(node);
		if (isRed(node->left) && isRed(node->left->left))
			node = RotateRight(node);
		if (isRed(node->left) && isRed(node->right))
			FlipColors(node);
		node->node_num = 1 + size(node->left) + size(node->right);
		return node;
	}

	val get(Node<val, key>* node, key keyval)
	{
		if (node == nullptr)
			return NULL;
		if (keyval < node->keyval) return get(node->left, keyval);
		else if (keyval > node->keyval) return get(node->right, keyval);
		else return node->value;
	}

	val* AuxGet(Node<val, key>* node, key keyval)
	{
		if (node == nullptr)
			return nullptr;
		if (keyval < node->keyval) return AuxGet(node->left, keyval);
		else if (keyval > node->keyval) return AuxGet(node->right, keyval);
		else return &(node->value);
	}

	void aux_print(Node<val, key>* node)
	{
		if (node == nullptr) return;
		aux_print(node->left);
		cout << node->keyval << " ";
		aux_print(node->right);
	}

	key Min(Node<val, key>* node)
	{
		Node<val, key>* temp = node;
		while (temp->left)
			temp = temp->left;
		return temp->keyval;
	}

	Node<val, key>* AuxMin(Node<val, key>* node)
	{
		Node<val, key>* temp = node;
		while (temp->left)
			temp = temp->left;
		return temp;
	}

	key Max(Node<val, key>* node)
	{
		Node<val, key>* temp = node;
		while (temp->right)
			temp = temp->right;
		return temp->keyval;
	}

	Node<val, key>* moveRedleft(Node<val, key>* node)
	{
		if (node == nullptr)
			return nullptr;
		_FlipColors(node);
		if (isRed(node->right->left))
		{
			node->right = RotateRight(node->right);
			node = RotateLeft(node);
			_FlipColors(node);
		}
		return node;
	}

	Node<val, key>* balance(Node<val, key>* node)
	{
		if (nullptr == node)
			return nullptr;
		if (!isRed(node->left) && isRed(node->right))
			node = RotateLeft(node);
		if (isRed(node->left) && isRed(node->left->left))
			node = RotateRight(node);
		if (isRed(node->left) && isRed(node->right))
			_FlipColors(node);
		node->node_num = 1 + size(node->left) + size(node->right);
		return node;
	}

	Node<val, key>* deleteMin(Node<val, key>* node)
	{
		if (node->left == nullptr)
			return nullptr;
		if (isRed(node->left) && isRed(node->left->left))
			node = moveRedleft(node);
		node->left = deleteMin(node->left);
		node = balance(node);
		return node;
	}

	Node<val, key>* moveRedRight(Node<val, key>* node)
	{
		if (nullptr == node)
			return nullptr;
		_FlipColors(node);
		if (isRed(node->left->left))
		{
			node = RotateRight(node);
			_FlipColors(node);
		}
		return node;
	}

	Node<val, key>* deleteMax(Node<val, key>* node)
	{
		if (isRed(node->left))
			node = RotateRight(node);
		if (node->right == nullptr)
			return nullptr;

		if (!isRed(node->right) && !isRed(node->right->left))
			node = moveRedRight(node);
		node->right = deleteMax(node->right);
		return balance(node);
	}

	Node<val, key>* Delete(Node<val, key>* node, key keyval)
	{
		if (node == nullptr)
			throw "null pointer";
		if (keyval < node->keyval)
		{
			if (!isRed(node->left) && !isRed(node->left->left))
			{
				node = moveRedleft(node);
			}
			node->left = Delete(node->left, keyval);
		}
		else
		{
			if (isRed(node->left))
				node = RotateRight(node);
			if (keyval == node->keyval && (node->right == nullptr))
				return nullptr;
			if (!isRed(node->right) && !isRed(node->right->left))
				node = moveRedRight(node);
			if (keyval == node->keyval)
			{
				Node<val, key>* temp = AuxMin(node->right);
				node->keyval = temp->keyval;
				node->value = temp->value;
				node->right = deleteMin(node->right);
			}
			else
			{
				node->right = Delete(node->right, keyval);
			}
		}
		return balance(node);
	}
	bool isEmpty()
	{
		return (root == nullptr) ? true : false;
	}
public:
	RB_TREE()
	{
		root = nullptr;
	}
	~RB_TREE()
	{
		aux_deleteall(root);
	}
	void put(key keyval, val value)
	{
		root = put(root, keyval, value);
		root->color = RB_BLACK;
	}

	val get(key keyval)
	{
		return get(root, keyval);
	}

	val& operator[](key keyval)
	{
		Node<val, key>* temp;
		val* tempValpt = AuxGet(root, keyval);
		if (tempValpt == nullptr)
		{
			put(keyval, NULL);
		}
		tempValpt = AuxGet(root, keyval);
		val& tempval = *(tempValpt);
		return tempval;
		
	}

	void print()
	{
		aux_print(root);
		cout << endl;
	}
	
	key Min()
	{
		return Min(root);
	}

	key Max()
	{
		return Max(root);
	}

	void deleteMin()
	{
		if (isEmpty())
		{
			throw "The tree is empty!";
		}

		if (!isRed(root->left) && !isRed(root->right))
			root->color = RB_RED;

		root = deleteMin(root);
		if (!isEmpty())
			root->color = RB_BLACK;
	}

	void deleteMax()
	{
		if (isEmpty())
		{
			throw "The tree is empty!";
		}
		if (!isRed(root->left) && !isRed(root->right))
			root->color = RB_RED;

		root = deleteMax(root);
		if (!isEmpty())
			root->color = RB_BLACK;
	}

	void Delete(key keyval)
	{
		if (isEmpty())
		{
			throw "The tree is empty!";
		}
		if (get(keyval) == NULL)
			return;
		if (!isRed(root->left) && !isRed(root->right))
			root->color = RB_RED;
		root = Delete(root, keyval);
		if (!isEmpty())
			root->color = RB_BLACK;
	}
};