#include "DecisionTree.h"
#include <cstddef>


DecisionTree::DecisionTree()
{
}


DecisionTree::~DecisionTree()
{
}


DecisionTreeNode* Decision::MakeDecision()
{
	// Choose a branch based on the getBranch method
	if (GetBranch()) {
		// Make sure its not null before recursing.
		if (trueBranch == NULL) return NULL;
		else return trueBranch->MakeDecision();
	}
	else {
		// Make sure its not null before recursing.
		if (falseBranch == NULL) return NULL;
		else return falseBranch->MakeDecision();
	}
}