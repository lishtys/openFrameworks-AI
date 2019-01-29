#pragma once
#include <vector>
#include "Boid.h"
#include "DynamicSteering.h"

class FlockSteering 
{
public:
	FlockSteering();
	~FlockSteering();

	std::vector<Boid*> boidTargets;
	Rigidbody *character;
	float maxAccerlation;
};

class Separation : public FlockSteering
{

	float threshold;
	float K;


public:
	virtual void getSteering(SteeringOutput* output);
};


class Align:public FlockSteering
{
public:
	virtual void getSteering(SteeringOutput* output);
};

