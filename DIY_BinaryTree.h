#pragma once
#include <vector>
#include <cassert>
#include <iostream>

#define DEBUG
using namespace std;

template<typename val, typename key>
class DIY_BinaryTree;

template<typename val, typename key>
class Node {
	friend DIY_BinaryTree<val, key>;
private:
	val value;
	key keyval;
	Node* left, * right;
	int ChildTree_NodeNum;
public:
	Node(val val, key keyval) :value(val), keyval(keyval), left(nullptr), right(nullptr), ChildTree_NodeNum(1){};
};

template<typename val, typename key>
class DIY_BinaryTree {
private:
	Node<val, key>* root;
	Node<val, key>* put(Node<val, key>* node, val value, key keyval);
	val get(Node<val, key>* node, key keyval);
	key Min(Node<val, key>* node);
	key Max(Node<val, key>* node);
	key floor(Node<val, key>* node, key keyval);
	key ceiling(Node<val, key>* node, key keyval);
	void aux_deleteall(Node<val, key>* node);
	Node<val, key>* DeleteMin(Node<val, key>* node);
	Node<val, key>* DeleteMax(Node<val, key>* node);
	Node<val, key>* Delete(Node<val, key>* node, key keyval);
	void keys(Node<val, key>* node, vector<key>& array1, key keylo, key keyhi);
	void aux_print(Node<val, key>* node);
public:
	//basic operation
	DIY_BinaryTree();
	~DIY_BinaryTree();
	void put(val value, key keyval);
	val get(key);
	int size(Node<val, key>* node);
	//standard operation
	int rank(key keyval);
	key select(int n);
	key Min();
	key Max();
	key floor(key keyval);
	key ceiling(key keyval);
	void Delete(key keyval);
	void DeleteMax();
	void DeleteMin();

	val& operator[](key keyval);

	//range search
	vector<key> range_find(void);
	vector<key> range_find(key keyval1, key keyval2);

	void print();
};

template<typename val, typename key>
DIY_BinaryTree<val, key>::DIY_BinaryTree()
{
	root = nullptr;
}

template<typename val, typename key>
DIY_BinaryTree<val, key>::~DIY_BinaryTree()
{
	aux_deleteall(root);
}

template<typename val, typename key>
void DIY_BinaryTree<val, key>::aux_deleteall(Node<val, key>* node)
{
	if (node == nullptr) return;
	if (node->left != nullptr) aux_deleteall(node->left);
	if (node->right != nullptr) aux_deleteall(node->right);
	delete node;
}

template<typename val, typename key>
void DIY_BinaryTree<val, key>::put(val value, key keyval)
{
	root = put(root, value, keyval);
}

template<typename val, typename key>
Node<val, key>* DIY_BinaryTree<val, key>::put(Node<val, key>* node, val value, key keyval)
{
	if (node == nullptr) return new Node<val, key>(value, keyval);
	if (keyval < node->keyval) node->left = put(node->left, value, keyval);
	else if (keyval > node->keyval) node->right = put(node->right, value, keyval);
	else node->value = value;
	node->ChildTree_NodeNum = size(node->left) + size(node->right) + 1;
#ifdef DEBUG
	print();
#endif // DEBUG

	return node;

}

template<typename val, typename key>
int DIY_BinaryTree<val, key>::size(Node<val, key>* node)
{
	if (node == nullptr)
		return 0;
	else
		return node->ChildTree_NodeNum;
}

template<typename val, typename key>
val DIY_BinaryTree<val, key>::get(key keyval)
{
	return get(root, keyval);
}

template<typename val, typename key>
val DIY_BinaryTree<val, key>::get(Node<val, key>* node, key keyval)
{
	if (node == nullptr) return NULL;
	if (keyval < node->keyval) return get(node->left, keyval);
	else if (keyval > node->keyval) return get(node->right, keyval);
	else
		return node->value;
}

template<typename val, typename key>
int DIY_BinaryTree<val, key>::rank(key keyval)
{
	int rank = 0;
	Node<val, key>* temp = root;

	while (temp)
	{
		if (temp->keyval == keyval)
		{
			rank += size(temp->left)+ 1;
			break;
		}

		else if (keyval < temp->keyval)
		{
			temp = temp->left;
		}

		else
		{
			rank += size(temp->left) + 1;
			temp = temp->right;
		}
	}

	if (temp)
		return rank;
	else
		return NULL;
}

template<typename val, typename key>
key DIY_BinaryTree<val, key>::select(int n)
{
	if (n <= 0)
		return NULL;
	int rank = 0;
	int temp_num = 0;
	Node<val, key>* temp = root;

	while (temp)
	{
		temp_num = rank += size(temp->left) + 1;
		if (temp_num == n)
		{
			return temp->keyval;
		}

		else if (temp_num < n)
		{
			temp = temp->right;
			rank += size(temp->left) + 1;
		}

		else
		{
			temp = temp->left;
		}
	}
	return NULL;
}

template<typename val, typename key>
key DIY_BinaryTree<val, key>::Min(Node<val, key>* node)
{
	Node<val, key>* temp = node;
	while (temp->left)
		temp = temp->left;
	return temp->keyval;
}

template<typename val, typename key>
key DIY_BinaryTree<val, key>::Min()
{
	return Min(root);
}

template<typename val, typename key>
key DIY_BinaryTree<val, key>::Max()
{
	return Max(root);
}

template<typename val, typename key>
key DIY_BinaryTree<val, key>::Max(Node<val, key>* node)
{
	Node<val, key>* temp = node;
	while (temp->right)
		temp = temp->right;
	return temp->keyval;
}

template<typename val, typename key>
key DIY_BinaryTree<val, key>::floor(key keyval)
{
	return floor(root, keyval);
}

template<typename val, typename key>
key DIY_BinaryTree<val, key>::floor(Node<val, key>* node, key keyval)
{
	if (node == nullptr) return NULL;

	if (node->keyval == keyval) return keyval;
	else if (node->left == nullptr && node->right == nullptr)
	{
		if (node->keyval < keyval) return node->keyval;
		else
			return NULL;
	}
	else if (node->keyval < keyval)
	{
		if (node->right == nullptr) return node->keyval;
		else if (node->right->keyval > keyval) return node->keyval;
		else
		{
			return floor(node->right, keyval);
		}
	}
	else if (node->keyval > keyval)
	{
		if (node->left == nullptr) return NULL;
		else return floor(node->left, keyval);
	}
	else;

}

template<typename val, typename key>
key DIY_BinaryTree<val, key>::ceiling(key keyval)
{
	return floor(root, keyval);
}

template<typename val, typename key>
key DIY_BinaryTree<val, key>::ceiling(Node<val, key>* node, key keyval)
{
	if (node == nullptr) return NULL;

	if (node->keyval == keyval) return keyval;
	else if (node->left == node->right == nullptr)
	{
		if (node->keyval > keyval) return node->keyval;
		else
			return NULL;
	}
	else if (node->keyval > keyval)
	{
		if (node->left == nullptr) return node->keyval;
		else if (node->left->keyval < keyval) return node->keyval;
		else
		{
			return floor(node->left, keyval);
		}
	}
	else if (node->keyval < keyval)
	{
		if (node->right == nullptr) return NULL;
		else return floor(node->right, keyval);
	}
	else;
}

template<typename val, typename key>
Node<val, key>* DIY_BinaryTree<val, key>::DeleteMin(Node<val, key>* node)
{
	if (node->left == nullptr) return node->right;
	node->left = DeleteMin(node->left);
	node->ChildTree_NodeNum = size(node->left) + size(node->right) + 1;
	return node;
}

template<typename val, typename key>
void DIY_BinaryTree<val, key>::DeleteMin()
{
	root = DeleteMin(root);
}

template<typename val, typename key>
Node<val, key>* DIY_BinaryTree<val, key>::DeleteMax(Node<val, key>* node)
{
	if (node->right == nullptr) return node->left;
	node->right = DeleteMax(node->right);
	node->ChildTree_NodeNum = size(node->left) + size(node->right) + 1;
	return node;
}


template<typename val, typename key>
void DIY_BinaryTree<val, key>::DeleteMax()
{
	root = DeleteMax(root);
}

template<typename val, typename key>
void DIY_BinaryTree<val, key>::Delete(key keyval)
{
	root = Delete(root, keyval);
}

template<typename val, typename key>
Node<val, key>* DIY_BinaryTree<val, key>::Delete(Node<val, key>* node, key keyval)
{
	if (node == nullptr) return nullptr;

	if (keyval < node->keyval) node->left = Delete(node->left, keyval);
	else if (keyval > node->keyval) node->right = Delete(node->right, keyval);
	else
	{
		if (node->left == nullptr) return node->right;
		else if (node->right == nullptr) return node->left;
		else
		{
			Node<val, key>* temp = node, * right_min = Min(node->right);
			right_min->right = DeleteMin(temp->right);
			right_min->left = temp->left;
			node = right_min;
		}
		

	}
	node->ChildTree_NodeNum = size(node->left) + size(node->right) + 1;
	return node;
}


template<typename val, typename key>
val& DIY_BinaryTree<val, key>::operator[](key keyval)
{
	Node<val, key>* temp = root;

	while (temp)
	{
		if (temp->keyval < keyval)
		{
			temp = temp->right;
		}
		else if (temp->keyval > keyval)
		{
			temp = temp->left;
		}
		else
		{
			break;
		}
	}
	if (temp == nullptr)
	{
		temp = new Node<val, key>(NULL, keyval);
		return temp->value;
	}
	else
	{
		return temp->value;
	}
}

template<typename val, typename key>
vector<key> DIY_BinaryTree<val, key>::range_find(key keyval1, key keyval2)
{
	if (keyval1 > keyval2)
	{
		vector<key> null;
		return null;
	}
	vector<key> vector_range;
	keys(root, vector_range, keyval1, keyval2);
	return vector_range;
}

template<typename val, typename key>
void DIY_BinaryTree<val, key>::keys(Node<val, key>* node, vector<key>& array1, key keylo, key keyhi)
{
	if (node == nullptr)
		return;
	
	if (node->keyval > keylo) keys(node->left, array1, keylo, keyhi);
	if (node->keyval < keyhi) keys(node->right, array1, keylo, keyhi);
	if(node->keyval <= keyhi && node->keyval >= keylo) array1.push_back(node->keyval);
}

template<typename val, typename key>
vector<key> DIY_BinaryTree<val, key>::range_find(void)
{
	keys(this->Min(), this->Max());
}

template<typename val, typename key>
void DIY_BinaryTree<val, key>::print()
{
	aux_print(root);
	cout << endl;
}

template<typename val, typename key>
void DIY_BinaryTree<val, key>::aux_print(Node<val, key>* node)
{
	if (node == nullptr) return;
	aux_print(node->left);
	cout << node->keyval << " ";
	aux_print(node->right);
}