#include "Tree.h"
#include<iterator>

void Tree::deleteTree(DecisionTreeNode* root)
{
	if (root == nullptr) return;
	if (root->_isLeaf == true) delete root;
	//list<ValidAnswer*>::iterator it;
	for (auto it = root->_answersList.begin(); it != root->_answersList.end(); ++it)
		deleteTree((Tree::DecisionTreeNode*)(*it)->_son);
}

void Tree::createTree(string val)
{
	_root = new DecisionTreeNode();
	_root->_value = val;
}

Tree::DecisionTreeNode* Tree::findQestion(string val)
{

}