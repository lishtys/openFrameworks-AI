#pragma once
#include "Rigidbody.h"
#include "SteeringOutput.h"
class SteeringOutput;

class KinematicMovment
{
public:
	KinematicMovment();
	~KinematicMovment();

	Rigidbody* targetBoid;
	ofVec2f targetPoint;
	float maxSpeed;
	virtual void getSteering(SteeringOutput* output) const = 0;
};



class KinematicSeek : public KinematicMovment
{
public:
	virtual void getSteering(SteeringOutput* output) const;
};



class KinematicFlee : public KinematicMovment
{
public:
	virtual void getSteering(SteeringOutput* output) const;
};


class KinematicArrive : public KinematicMovment
{
public:
	float timeStop;
	float radius;
	virtual void getSteering(SteeringOutput* output) const;
};


class KinematicWander : public KinematicMovment
{
public:
	float maxRotation;
	virtual void getSteering(SteeringOutput* output) const;
};