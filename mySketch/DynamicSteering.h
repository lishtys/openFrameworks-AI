#pragma once
#include "Rigidbody.h"
#include "SteeringOutput.h"


class DynamicSteering
{
public:
	DynamicSteering();
	~DynamicSteering();

	Rigidbody* character;
	Rigidbody* targetBoid;
	ofVec2f targetPosition={0,0};
	float maxSpeed=100;
	float maxAcceleration=10;
	float maxAngularAcc=10;
	virtual void getSteering(SteeringOutput* output)  = 0;
};



class DynamicSeek : public DynamicSteering
{
public:
	virtual void getSteering(SteeringOutput* output) ;
};



class DynamicFlee : public DynamicSteering
{
public:
	virtual void getSteering(SteeringOutput* output) ;
};


class DynamicArrive : public DynamicSteering
{
public:
	float timeToTarget;
	float TargetRadius;
	float slowRadius;
	virtual void getSteering(SteeringOutput* output) ;
};


class DynamicWander : public DynamicSteering
{
public:
	ofVec2f wanderTarget;
	float wanderRadius = 1000;

	virtual void getSteering(SteeringOutput* output);
};

class DynamicAlign : public DynamicSteering
{
public:
	float maxRotation=2;
	float slowAngleThreshold=0.3f;
	float targetAngleThreshold=0.1f;
	float timeToTarget=.2f;

	virtual void getSteering(SteeringOutput* output);
};
