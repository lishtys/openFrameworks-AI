#pragma once
#include "Rigidbody.h"
#include "Boid.h"
#include "DynamicSteering.h"
#include "KinematicSteering.h"

class WanderMotion
{
public:
	WanderMotion();
	~WanderMotion();

	void Init();
	void Update();
	void Draw();

	void OnMousePressed(int x,int y);

	//Dynamic 
	DynamicWander wander;
	DynamicAlign align;


	//Kinematic

	KinematicWander kinematic_wander;
	


private:

	Boid m_boid;
	Rigidbody targetRigid;
};

