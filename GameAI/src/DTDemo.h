#pragma once
#include "Boid.h"
#include "Steering.h"
#include "DecisionTree.h"

class BoidWallDecisionNode :public Decision
{
public:
	Rigidbody* targetRigid;
	Boid* m_boid;
	virtual bool GetBranch();
};

class BoidTargetDecisionNode :public Decision
{
public:
	Rigidbody* targetRigid;
	Boid* m_boid;
	virtual bool GetBranch();
};

class BoidTargetActionNode : public DecisionTreeAction
{
public:
	Rigidbody* targetRigid;
	Boid* m_boid;
	virtual void DoAction();
};

class BoidWallActionNode :public DecisionTreeAction
{
public:
	Rigidbody* targetRigid;
	Boid* m_boid;
	virtual void DoAction();
};

class BoidArriveActionNode :public DecisionTreeAction
{
public:
	Rigidbody* targetRigid;
	Boid* m_boid;
	DynamicArrive* arrive;
	SteeringOutput* steer;
	virtual void DoAction();
};




class DTDemo
{
public:
	DTDemo();
	~DTDemo();


	void Draw();

	void OnKeyReleased(int key);
	void OnKeyPressed(int key);

	void OnMousePressed(int x, int y, int button);
	void OnMouseClick(int x, int y, int button);


	void Init();
	void Update();


	Boid m_boid;

	DynamicArrive arrive;
	Rigidbody targetRigid;

	BoidWallDecisionNode wall_dec_node;
	BoidTargetDecisionNode target_dec_node;

	BoidArriveActionNode arrive_action_node;
	BoidTargetActionNode target_action_node;
	BoidWallActionNode wall_action_node;


	
	void RandomPosition();
	
};




