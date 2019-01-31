#pragma once
#include "Rigidbody.h"
#include "SteeringOutput.h"
#include "Obstacle.h"
#include "Boid.h"


class KinematicSteering
{
public:
	KinematicSteering();
	~KinematicSteering();

	Rigidbody* character;
	Rigidbody* targetBoid;

	float maxSpeed;
	virtual void getSteering(SteeringOutput* output) = 0;
};

class KinematicSeek : public KinematicSteering
{
public:
	virtual void getSteering(SteeringOutput* output);
};



class KinematicFlee : public KinematicSteering
{
public:
	virtual void getSteering(SteeringOutput* output);
};


class KinematicArrive : public KinematicSteering
{
public:
	float targetRadius;
	float timeToTarget;
	virtual void getSteering(SteeringOutput* output);
};


class KinematicWander : public KinematicSteering
{
public:
	ofVec2f wanderTarget;
	float wanderRadius=200;
	virtual void getSteering(SteeringOutput* output);
};


class Avoid : public KinematicSteering
{
public:

    std::vector<Obstacle>	 elements;
    std::vector<Boid*>	 boids;
	float characterRadius;
	float maxLookahead=20;
	ofVec2f findTargetPoint;
	float offset = 2;
	virtual void getSteering(SteeringOutput* output);
};

