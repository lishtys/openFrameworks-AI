#pragma once

#include "DynamicSteering.h"
#include "Flock.h"

class FlockSteering 
{
public:
	FlockSteering();
	~FlockSteering();

	Flock* mFlock;
	Boid * mCharacter;
	
};

class Separation : public FlockSteering
{

public:
	float threshold;
	float K;
	virtual void getSteering(SteeringOutput* output);
};


class Align:public FlockSteering
{
public:
	virtual void getSteering(SteeringOutput* output);
};



