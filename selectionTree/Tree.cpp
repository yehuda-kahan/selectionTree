#include "Tree.h"

// delete the tree from the given node
void Tree::clear(DecisionTreeNode* root) const
{
	if (root == NULL) return;
	if (root->_isLeaf == true) delete root;
	//list<ValidAnswer*>::iterator it;
	for (auto it = root->_answersList.begin(); it != root->_answersList.end(); ++it)
		clear((DecisionTreeNode*)(*it)->_son);
	delete root;
}

// create the first node in the tree (with question)
void Tree::addRoot(string val)
{
	_root = new DecisionTreeNode();
	_root->_value = val;
}

// search in the tree the given question/solution 
DecisionTreeNode* Tree::findQestion(string val, DecisionTreeNode* node, DecisionTreeNode*& father) const
{
	//if (!node || (node->_isLeaf && node->_value != val)) //no node or this is not leaf and this is not the value
	//	return NULL;
	if (node->_value == val)
		return node;
	DecisionTreeNode* temp = NULL;
	DecisionTreeNode* theReturn = NULL;

	for (auto it = node->_answersList.begin(); it != node->_answersList.end(); ++it)
	{
		temp = findQestion(val, (*it)->_son, father);
		if (temp)
		{
			theReturn = temp;
			if ((*it)->_son->_value == val)
				father = node;
		}
	}
	return theReturn;
}

// add ValidAnswer and question/solution to the tree
bool Tree::addSon(string fQuestion, string answer, string sol) const
{
	DecisionTreeNode* theFather = NULL;
	DecisionTreeNode* node = findQestion(fQuestion, _root, theFather);
	if (node == NULL) return false;
	ValidAnswer* pAns = new ValidAnswer();   // create a new validAnswer node 
	pAns->_ans = answer;                        // apdate the _ans to the given answer 
	pAns->_son = new DecisionTreeNode();     // apdate the _son to a new node that will contain the - next question/desition 
	pAns->_son->_value = sol;                // apdate teh new node solution/next question
	node->_answersList.push_back(pAns);      // push the pointer whice hold the validAnswer with the _son, to the father list 
	node->_isLeaf = false;                   // apdate the father that he dosen't a leaf anymore
	return true;
}

// print all tree
void Tree::print(DecisionTreeNode* node) const
{
	cout << node->_value <<endl << " ";
	for (auto it = node->_answersList.begin(); it != node->_answersList.end(); ++it)
	{
		cout << (*it)->_ans << endl;
		print((*it)->_son);
	}
}