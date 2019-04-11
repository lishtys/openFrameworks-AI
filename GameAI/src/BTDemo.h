#pragma once
#include "BTCore.h"
#include "Boid.h"
#include "Steering.h"


class ChaseNode : public Node
{
public:

	Rigidbody* targetRigid;
	Boid* m_monster;
	DynamicArrive* arrive;
	SteeringOutput* steer;
	Status update() override
	{
		arrive->getSteering(steer);
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


class CheckSpin


class RespawnNode : public Node
{
public:

	Boid* m_boid;
	Boid* m_monster;
	DynamicArrive* arrive;
	SteeringOutput* steer;
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


	DynamicArrive arrive;




	BehaviorTree mon_tree;
	BehaviorTree boid_tree;
	shared_ptr<ChaseNode> chase_node;
};





