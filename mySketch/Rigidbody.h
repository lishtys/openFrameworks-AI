#pragma once
#include "ofVec2f.h"

class SteeringOutput;

class Rigidbody
{
public:
	Rigidbody();
	~Rigidbody();


	ofVec2f Position;
	ofVec2f Velocity;
	float Orientation; // radians
	float Rotation; // angular Vel


	void Update(const SteeringOutput& steer, float deltaTime);

};

