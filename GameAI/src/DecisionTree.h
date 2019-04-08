#pragma once
class DecisionTree
{
public:
	DecisionTree();
	~DecisionTree();
};


class  DecisionTreeNode
{
public:
	
	virtual DecisionTreeNode* MakeDecision() = 0;
};

class DecisionTreeAction : public DecisionTreeNode
{
public:
	virtual DecisionTreeNode* MakeDecision()
	{
		return this;
	}
	virtual void DoAction()
	{
		
	}

};

class Decision : public DecisionTreeNode
{
public:
	DecisionTreeNode* trueBranch;
	DecisionTreeNode* falseBranch;
	virtual bool GetBranch() = 0;
	virtual DecisionTreeNode* MakeDecision();
};