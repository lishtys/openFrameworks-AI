#include "SteeringOutput.h"



SteeringOutput::SteeringOutput()
{
	angular = 0.0;
	Velocity = {0,0};
	Rotation = 0;
	linear = { 0,0 };
}


SteeringOutput::~SteeringOutput()
{
}

SteeringOutput::SteeringOutput(const ofVec2f& linear, float angular): linear(linear), angular(angular)
{
}