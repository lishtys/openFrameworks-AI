#pragma once
#include "Rigidbody.h"
#include "Boid.h"
#include "Steering.h"
#include "Steering.h"

class WanderMotion
{
public:
	WanderMotion();
	~WanderMotion();

	void Init();
	void Update();
	void Draw();

	void OnMousePressed(int x,int y,int button);

	//Dynamic 
	DynamicWander wander;
	DynamicAlign align;


	//Kinematic

	KinematicWander kinematic_wander;
	


private:

	Boid m_boid;
	Rigidbody targetRigid;
};

