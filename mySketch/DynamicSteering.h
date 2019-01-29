#pragma once
#include "Rigidbody.h"
#include "SteeringOutput.h"
class SteeringOutput;

class DynamicSteering
{
public:
	DynamicSteering();
	~DynamicSteering();

	Rigidbody* character;
	Rigidbody* targetBoid;
	float maxSpeed;
	float maxAcceleration;
	float maxAngularAcc;
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
	float turnSpeed;
	ofVec2f wanderTarget;
	float viewRange;

	virtual void getSteering(SteeringOutput* output);
};

class DynamicAlign : public DynamicSteering
{
public:
	float maxRotation;
	float slowAngleThreshold;
	float targetAngleThreshold;
	float timeToTarget;


	virtual void getSteering(SteeringOutput* output);
};