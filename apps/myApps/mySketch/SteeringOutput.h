#pragma once
#include "ofVec2f.h"

class SteeringOutput
{
public:
	SteeringOutput();
	~SteeringOutput();

	SteeringOutput(const ofVec2f& linear, float angular = 0)
		: linear(linear), angular(angular)
	{}

	ofVec2f linear;
	float angular;
};

