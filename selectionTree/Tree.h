#pragma once

#include<list>
#include<algorithm>
#include<string>

using namespace std;

class DecisionTreeNode;


class Tree
{
public:

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

	DecisionTreeNode* _root;

	Tree() : _root(nullptr) {};
	~Tree() { deleteTree(_root); };
	
	void createTree(string val);
	void deleteTree(DecisionTreeNode* root);
	DecisionTreeNode* findQestion(string val);
};





