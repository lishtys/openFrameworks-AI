#pragma once
#include "BTCore.h"
#include "Boid.h"
#include "Steering.h"
#include "AStarPathfinding.h"
#include "DecisionTree.h"


class ChaseNode : public Node
{
public:

	Rigidbody* targetRigid;
	Boid* m_monster;


	AStarPathfinding* a_star_pathfinding;


//	DynamicArrive* arrive;
	SteeringOutput* steer;
	Status update() override
	{
		a_star_pathfinding->path_follow.character = &m_monster->mRigidbody;
		a_star_pathfinding->path_follow.pRadius = 20;
		a_star_pathfinding->path_follow.path = a_star_pathfinding->pathList;
	

		a_star_pathfinding->path_follow.getSteering(steer);
		// arrive->getSteering(steer);
		return Node::Status::Success;
	}
};

class WanderNode : public Node
{
public:

	Rigidbody* targetRigid;
	Boid* m_monster;
	DynamicWander* wander;
	SteeringOutput* steer;
	Status update() override
	{
		wander->getSteering(steer);
		return Node::Status::Success;
	}
};

class CheckNearNode : public Node
{
public:

	Boid* m_boid;
	Boid* m_monster;
	DynamicArrive* arrive;
	SteeringOutput* steer;
	Status update() override
	{
		auto Position = m_monster->mRigidbody.Position;
		auto targetPos = m_boid->mRigidbody.Position;
		auto dist = Position.distanceSquared(targetPos);
		if (dist < 20) return Node::Status::Success;
		return Node::Status::Failure;
	}
};





class RespawnNode : public Node
{
public:

	Boid* m_boid;
	Boid* m_monster;
	AStarPathfinding* a_pathfinding;
	Status update() override
	{

		m_boid->mRigidbody.Position.x = ofRandomWidth();
		m_boid->mRigidbody.Position.y = ofRandomHeight();
		m_monster->mRigidbody.Position = ofVec2f(ofGetWindowWidth() / 2, ofGetWindowHeight() / 2);
		a_pathfinding->GetPathForTarget(m_boid->mRigidbody.Position.x, m_boid->mRigidbody.Position.y);
		return Node::Status::Success;
	}
};

class CheckExsitNode : public Node
{
public:

	Boid* m_boid;
	Boid* m_monster;
	DynamicArrive* arrive;
	SteeringOutput* steer;
	Status update() override
	{
		return Node::Status::Failure;
	}
};

//------------------------------------------------------------------



class BoidTDecisionNode :public Decision
{
public:
	Rigidbody* targetRigid;
	Boid* m_boid;
	virtual bool GetBranch();
};

class BoidTActionNode : public DecisionTreeAction
{
public:
	Rigidbody* targetRigid;
	Boid* m_boid;
	virtual void DoAction();
};



class BoidChasActionNode :public DecisionTreeAction
{
public:
	Boid* mon_boid;
	AStarPathfinding* pathfinding;
	SteeringOutput* steer;
	virtual void DoAction();
};

//------------------------------------------------------------------

class BTDemo
{
public:
	BTDemo();
	~BTDemo();


	void Draw();

	void OnKeyReleased(int key);
	void OnKeyPressed(int key);

	void OnMousePressed(int x, int y, int button);
	void OnMouseClick(int x, int y, int button);

	void Init();
	void Update();


	Boid m_boid;
	Boid m_monster;
	Rigidbody targetRigid;

	DynamicArrive arrive;
	DynamicWander wander;



	AStarPathfinding a_pathfinding;
	ofImage img_node;
	ofImage* cur_img;

	BehaviorTree mon_tree;
	BehaviorTree boid_tree;
	shared_ptr<ChaseNode> chase_node;
	shared_ptr<RespawnNode> respawn_node;
	shared_ptr<CheckNearNode> check_near_node;
	shared_ptr<WanderNode> wander_node;



	// DT Learning 
	BoidTDecisionNode target_dec_node;

	BoidChasActionNode chase_action_node;
	BoidTActionNode target_action_node;
	Boid learn_monster;
	AStarPathfinding learn_pathfinding;

};





