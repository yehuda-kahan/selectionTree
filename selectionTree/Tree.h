#pragma once

#include<list>
#include<algorithm>
#include<string>

using namespace std;

class DecisionTreeNode;

class ValidAnswer
{
public:
	string _ans;
	DecisionTreeNode* _son;

};

class DecisionTreeNode
{
public:
	string _value;
	bool _isLeaf;
	list<ValidAnswer*> _answersList;

	DecisionTreeNode() : _isLeaf(true) {};
};

class Tree
{
public:

	DecisionTreeNode* _root;

	Tree() : _root(nullptr) {};
	~Tree() { clear(_root); };
	
	void addRoot(string val);
	void clear() { clear(_root); }
	void clear(DecisionTreeNode* root) const;
	
	bool addSon(string father, string val, string sol);
	DecisionTreeNode* findQestion(string val, DecisionTreeNode* root, DecisionTreeNode*& father);
};





