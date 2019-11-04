#include "Tree.h"

// delete the tree from the given node
void Tree::clear(DecisionTreeNode* node) const
{
	// Note : The test if is this NULL we did in the Dtor and in deleteSubTree function, only them use it .

	if (node->_isLeaf == true)
	{
		delete node; return;
	}
	// else : he has sans
	for (auto it = node->_answersList.begin(); it != node->_answersList.end(); ++it)
	{
		if ((*it)->_son == NULL) continue;
		clear((*it)->_son);
		delete* it;         // delete the ValidAnswer pointer in the list
	}
	delete node; // after delete all his sans, delete the node
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
	father = NULL;
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
void Tree::print(DecisionTreeNode* node, int level) const
{
	for (int i = 0; i < level; ++i)
		cout << " ";
	cout << node->_value << endl;
	for (auto it = node->_answersList.begin(); it != node->_answersList.end(); ++it)
	{
		for (int i = 0; i < level; ++i)
			cout << " ";
		cout <<": " <<(*it)->_ans << endl;
		print((*it)->_son, level+1);
	}
}

// print the path from the given question/solution until the root
void Tree::searchAndPrint(string val) const
{
	DecisionTreeNode* father = NULL;
	DecisionTreeNode* current = findQestion(val, _root, father);
	while (current != NULL)
	{
		cout << current->_value;  // print the current question/solution
		if (father == NULL)
			break;
		cout << " => ";
		// check in all the "suns" of the father, who is the current - and print the answer which bringe to him
		for (auto it = father->_answersList.begin(); it != father->_answersList.end(); ++it)
			if ((*it)->_son == current)
				cout << (*it)->_ans << " => ";
		current = findQestion(father->_value, _root, father);
	}
}

// delete the sub tree of the given question/solution
void Tree::deleteSubTree(string val) const
{
	DecisionTreeNode* father = NULL;
	DecisionTreeNode* current = findQestion(val, _root, father);

	if (current == NULL)
	{
		cout << "ERROR : There is no question/solution - " << val; return;
	}

	for (auto it = current->_answersList.begin(); it != current->_answersList.end(); ++it)
	{
		clear((*it)->_son);
		delete* it;
	}
	current->_answersList.clear();   // clear the list of the current node
	current->_isLeaf = true;         // make him a leaf
}

// the process on the tree for the costumer
void Tree::process() const
{
	if (_root == NULL)
	{
		cout << "ERROR : there is no tree to process on it" << endl; return;
	}
	DecisionTreeNode* current = _root;
	cout << current->_value << endl;

	while (current->_isLeaf == false)
	{
		string ans;
		cin >> ans;
		for (auto it = current->_answersList.begin(); it != current->_answersList.end(); ++it)
			if ((*it)->_ans == ans)
			{
				current = (*it)->_son;
				break;
			}
		cout << current->_value;
	}
}