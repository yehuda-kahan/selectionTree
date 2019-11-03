#include "Tree.h"
#include<iterator>

void Tree::clear(DecisionTreeNode* root) const
{
	if (root == nullptr) return;
	if (root->_isLeaf == true) delete root;
	//list<ValidAnswer*>::iterator it;
	for (auto it = root->_answersList.begin(); it != root->_answersList.end(); ++it)
		clear((DecisionTreeNode*)(*it)->_son);
	delete root;
}

void Tree::addRoot(string val)
{
	_root = new DecisionTreeNode();
	_root->_value = val;
}

DecisionTreeNode* Tree::findQestion(string val, DecisionTreeNode* node, DecisionTreeNode* &father) const
{
	//if (!node || (node->_isLeaf && node->_value != val)) //no node or this is not leaf and this is not the value
	//	return nullptr;
	if (node->_value == val)
		return node;
	DecisionTreeNode* temp = nullptr;
	DecisionTreeNode* theReturn = nullptr;
	for (auto it = node->_answersList.begin(); it != node->_answersList.end(); ++it)
	{
		temp = findQestion(val, (*it)->_son, father);
		if (temp)
		{
			theReturn = temp;
			father = node;
		}
	}
	return theReturn;
}

bool Tree::addSon(string father, string val, string sol) const
{
	DecisionTreeNode* theFather = nullptr;
	DecisionTreeNode* node = findQestion(father, _root, theFather);
}