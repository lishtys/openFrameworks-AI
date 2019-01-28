#pragma once
#include "Kinematic.h"



 struct  Color
{
	float r = 255;
	float g = 255;
	float b = 255;
};

class Boid
{
public:
	Boid();
	~Boid();

	// Parameter
	float CircleRadius = 30.0f;
	Color mColor;
	// AI Motion
	Kinematic mRigidbody;
	
	
	void Draw();

	void Update();

	void Rotate(float rad);
};




