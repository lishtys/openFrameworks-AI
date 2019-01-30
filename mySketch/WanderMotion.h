#pragma once
#include "Rigidbody.h"
#include "Boid.h"
#include "DynamicSteering.h"

class WanderMotion
{
public:
	WanderMotion();
	~WanderMotion();

	void Init();
	void Update();
	void Draw();

	void OnMousePressed();

	DynamicWander wander;
	DynamicAlign align;


	


private:

	Boid m_boid;
	Rigidbody targetRigid;
};

