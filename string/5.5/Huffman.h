#pragma once

#include "string"
#include "vector"
#include "Minpq.h"

using namespace std;


class Node
{
private:
	char ch;
	int freq;
	Node* left, *right;
	friend class Huffman;
	void print(Node* node);
public:
	Node(char ch, int freq, Node* left, Node* right);
	bool isLeaf();
	void print();
	int Getfreq();
	int compareTo(Node* that);
	bool operator>(Node* that);
	bool operator<(Node* that);
	bool operator==(Node* that);
};


class Huffman
{
private:
	int R = 256;
	void bulidCode(vector<string>& st, Node* node, string s);
	Node* bulidTrie(vector<int> freq);
	void writeTrie(Node* node, vector<string>& st);
	Node* readTrie();
public:
	void expand();
	vector<string> bulidCode(Node* root);
	void compress(string& s);

};