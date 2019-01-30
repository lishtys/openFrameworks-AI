#pragma once
#include "Rigidbody.h"



 struct  Color
{
	float r = 0;
	float g = 0;
	float b = 0;
};

class Boid
{
public:
	Boid();
	~Boid();

	// Parameter
	float CircleRadius = 10;
	Color mColor;
	// AI Motion
	Rigidbody mRigidbody;

	
	
	void Draw();

	void Update(const SteeringOutput& steer, float deltaTime);

	void Rotate(float rad);

};




