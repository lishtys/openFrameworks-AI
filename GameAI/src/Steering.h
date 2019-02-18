#pragma once
#include "Rigidbody.h"
#include "SteeringOutput.h"
#include "Obstacle.h"
#include "Node.h"


class Steering
{
public:
	Steering();
	~Steering();

	Rigidbody* character;
	Rigidbody* targetBoid;
	ofVec2f targetPosition={0,0};
	float maxSpeed=100;
	float maxAcceleration=10;
	float maxAngularAcc=10;
	virtual void getSteering(SteeringOutput* output)  = 0;
};



class DynamicSeek : public Steering
{
public:
	virtual void getSteering(SteeringOutput* output) ;
};



class DynamicFlee : public Steering
{
public:
	virtual void getSteering(SteeringOutput* output) ;
};


class DynamicArrive : public Steering
{
public:
	float timeToTarget;
	float TargetRadius;
	float slowRadius;
	virtual void getSteering(SteeringOutput* output) ;
};


class DynamicWander : public Steering
{
public:
	ofVec2f wanderTarget;
	float wanderRadius = 1000;

	virtual void getSteering(SteeringOutput* output);
};

class DynamicAlign : public Steering
{
public:
	float maxRotation=2;
	float slowAngleThreshold=0.3f;
	float targetAngleThreshold=0.1f;
	float timeToTarget=.2f;

	virtual void getSteering(SteeringOutput* output);
};



class KinematicSeek : public Steering
{
public:
	virtual void getSteering(SteeringOutput* output);
};

class KinematicFlee : public Steering
{
public:
	virtual void getSteering(SteeringOutput* output);
};


class KinematicArrive : public Steering
{
public:
	float targetRadius;
	float timeToTarget;
	virtual void getSteering(SteeringOutput* output);
};

class KinematicWander : public Steering
{
public:
	ofVec2f wanderTarget;
	float wanderRadius = 200;
	virtual void getSteering(SteeringOutput* output);
};


class Avoid : public Steering
{
public:
	std::vector<Obstacle> elements;
	float characterRadius;
	float maxLookahead = 20;
	ofVec2f findTargetPoint;
	float offset = 2;
	virtual void getSteering(SteeringOutput* output);
};


class Follow : public Steering
{
public:
	std::vector<Node> path;
	float pRadius;
	int curIdx;
	virtual void getSteering(SteeringOutput* output);
};