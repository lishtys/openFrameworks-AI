#pragma once
#include "Rigidbody.h"

class Obstacle
{
public:
	Obstacle();
	~Obstacle();

	float CircleRadius = 50;

	Rigidbody mRigidbody;

	void Draw();

};

