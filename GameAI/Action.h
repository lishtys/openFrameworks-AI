#pragma once
class Action
{
public:
	Action();
	~Action();


	float priority;
	Action* next;
	Action* GetLast();

};

class ActionManager
{
public:

	float activePriority;
	Action * actionQueue;
	Action * active;
protected:
	
	void RunActive();


public:

	ActionManager();
	void Execute();
};