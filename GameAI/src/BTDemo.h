#pragma once
#include "BTCore.h"
#include "Boid.h"
#include "Steering.h"
#include "AStarPathfinding.h"


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
	Status update() override
	{

		m_boid->mRigidbody.Position.x = ofRandomWidth();
		m_boid->mRigidbody.Position.y = ofRandomHeight();
		m_monster->mRigidbody.Position = ofVec2f(ofGetWindowWidth() / 2, ofGetWindowHeight() / 2);
		
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

};





