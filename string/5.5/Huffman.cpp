#include "Huffman.h"
#include "iostream"
#include "fstream"

Node::Node(char ch, int freq, Node* left, Node* right)
{
	this->ch = ch;
	this->freq = freq;
	this->left = left;
	this->right = right;
}

bool Node::isLeaf()
{
	return left == nullptr && right == nullptr;
}

bool Node::operator>(Node* that)
{
	return this->freq > that->freq;
}

bool Node::operator<(Node* that)
{
	return this->freq < that->freq;
}

bool Node::operator==(Node* that)
{
	return this->freq == that->freq;
}

int Node::compareTo(Node* that)
{
	return this->freq - that->freq;
}

int Node::Getfreq()
{
	return freq;
}

void Node::print(Node* node)
{
	if (node == nullptr)
		return;
	cout << node->ch  << "-" << node->freq << " ";
	print(node->left);
	print(node->right);
}

void Node::print()
{
	print(this);
	cout << endl;
}


void Huffman::bulidCode(vector<string>& st, Node* node, string s)
{
	if (node->isLeaf())
	{
		st[node->ch] = s;
		return;
	}

	bulidCode(st, node->left, s + '0');
	bulidCode(st, node->right, s + '1');

}

Node* Huffman::bulidTrie(vector<int> freq)
{
	Minpq<Node*> pq;
	for (int c = 0; c < R; c++)
	{
		if (freq[c] > 0)
			pq.Insert(new Node(c, freq[c], nullptr, nullptr));
	}
	pq.print();
	while (pq.size() > 1)
	{
		Node* x = pq.Delete_Min();
		Node* y = pq.Delete_Min();
		Node* parent = new Node('\0', x->freq + y->freq, x, y);
		pq.Insert(parent);
		
	}

	
	return pq.Delete_Min();
}

void Huffman::writeTrie(Node* node, vector<string>& st)
{
	if (node->isLeaf())
	{
		cout << node->ch;
		cout << ":";
		cout << st[node->ch];
		cout << "  ";
		return;
	}
	writeTrie(node->left, st);
	writeTrie(node->right, st);
}

Node* Huffman::readTrie()
{
	bool c;
	cin >> c;
	if (c)
	{
		char ch;
		cin >> ch;
		return new Node(ch, 0, nullptr, nullptr);
	}
	return new Node('\0', 0, readTrie(), readTrie());
}

void Huffman::expand()
{
	ifstream filein("test_exp.txt", ios::binary);
	ofstream fileout("test_exp_out.txt", ios::binary);
	Node* root = readTrie();
	int N;
	cin >> N;
	char c = 0;
	for (int i = 0; i < N; i++)
	{
		Node* x = root;
		while (!x->isLeaf())
		{
			filein.read(&c, 1);
			if (c)
				x = x->right;
			else
				x = x->left;

		}
		fileout.write(&x->ch, 1);
	}
	filein.close();
	fileout.close();
}

vector<string> Huffman::bulidCode(Node* root)
{
	vector<string> st(R);
	bulidCode(st, root, "");
	return st;
}

void Huffman::compress(string& s)
{
	vector<int> freq(R);
	for (int i = 0; i < s.length(); i++)
		freq[s[i]]++;

	Node* root = bulidTrie(freq);
	root->print();
	Node* temp = root;
	
	vector<string> st(R);
	bulidCode(st, root, "");
	writeTrie(root, st);
	cout << "×Ö·û×ÜÊý£º" << s.length() << endl;
	for (int i = 0; i < s.length(); i++)
	{
		string code = st[s[i]];
		for (int j = 0; j < code.length(); j++)
		{
			if (code[j] == '1')
				cout << 1;
			else
				cout << 0;
		}
	}

}