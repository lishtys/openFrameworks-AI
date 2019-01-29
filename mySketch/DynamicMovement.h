#pragma once
#include "Rigidbody.h"
#include "SteeringOutput.h"





class DynamicMovement
{
public:
	DynamicMovement();
	~DynamicMovement();

	Rigidbody *targetRigidbody;
	ofVec2f targetPosition;
	virtual void getSteering(SteeringOutput* output) = 0;
};


class DynamicSeek : public DynamicMovement
{
	float maxAccel;
	virtual void getSteering(SteeringOutput* output);
};

class DynamicFlee : public DynamicMovement
{
	float maxAccel;
	virtual void getSteering(SteeringOutput* output);
};

class DynamicWonder : public DynamicMovement
{
	ofVec2f rangeTarget;
	float Tolerence;
	ofVec2f turnSpeed;

	virtual void getSteering(SteeringOutput* output);
};

class DynamicSeperation : public DynamicMovement
{
	ofVec2f rangeTarget;
	float Tolerence;
	ofVec2f turnSpeed;

	virtual void getSteering(SteeringOutput* output);
};


struct BehaviourAndWeight
{
	DynamicMovement *behaviour;
	float weight;

	BehaviourAndWeight(DynamicMovement *behaviour, float weight = 1.0)
		:
		behaviour(behaviour), weight(weight)
	{}
};


class BlendedSteering : DynamicMovement
{
	std::vector<BehaviourAndWeight> behaviours;
	virtual void getSteering(SteeringOutput* output);

};