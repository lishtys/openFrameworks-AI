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




	BehaviorTree tree;
};





