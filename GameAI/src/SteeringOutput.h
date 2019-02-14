#pragma once
#include "ofVec2f.h"

class SteeringOutput
{
public:
	SteeringOutput();
	~SteeringOutput();

	SteeringOutput(const ofVec2f& linear, float angular = 0);

	//Dynamic
	ofVec2f linear;
	float angular;

	// Kinematic
	ofVec2f Velocity;
	float Rotation;

};

