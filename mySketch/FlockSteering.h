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

	float maxSpeed = 100;
	
};

class DynamicSeparation : public FlockSteering
{

public:
	float sepDistance;
	float timeToTarget;
	float maxAcc;
	virtual void getSteering(SteeringOutput* output);
};


class Align:public FlockSteering
{
public:
	virtual void getSteering(SteeringOutput* output);
};




class KinematicSeparation : public FlockSteering
{

public:
	float sepDistance;
	virtual void getSteering(SteeringOutput* output);
};

class KinematicAvoid : public FlockSteering
{

public:
	virtual void getSteering(SteeringOutput* output);
};

class DynamicMatchVel : public FlockSteering
{
public:
	float radius=80;
	virtual void getSteering(SteeringOutput* output);
};

