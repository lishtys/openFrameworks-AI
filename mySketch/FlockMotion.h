#pragma once
#include "Flock.h"
#include "SteeringOutput.h"
#include "FlockSteering.h"

class FlockMotion
{
public:
	FlockMotion();
	~FlockMotion();

	void Init();
	void Update();
	void Draw();
	void OnMousePressed(int x,int y);

	Flock flock;


	Separation separation;


	Boid leader;
};

