#pragma once
#include "ofVec2f.h"

class Kinematic
{
public:
	Kinematic();
	~Kinematic();


	ofVec2f Position;
	ofVec2f Velocity;
	float Orientation; // radians
	float Rotation; // angular Vel


	void Update();

};

