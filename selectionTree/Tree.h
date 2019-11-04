#pragma once

#include<list>
#include<algorithm>
#include<string>
#include<iostream>
#include<iterator>

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
	// Dtor/Ctor
	Tree() : _root(NULL) {};
	~Tree() {if (_root != NULL) clear(_root); };

	// methods
	void addRoot(string val);
	
	void clear() { if (_root != NULL) clear(_root); }
	void clear(DecisionTreeNode* root) const;
	bool addSon(string fQuestion, string answer, string sol) const;
	DecisionTreeNode* findQestion(string val, DecisionTreeNode* root, DecisionTreeNode*& father) const;
	void print(DecisionTreeNode* node, int level)const;
	void printAllTree() { if(_root != NULL) print(_root, 0); }
	void searchAndPrint(string val) const;
	void deleteSubTree(string val) const;
	void process() const;
};





