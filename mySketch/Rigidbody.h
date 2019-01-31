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



	// Limits

	float maxSpeed = 50;
	float maxAcceleration = 50;
	float maxAngularAcc = 10;

	//Weights

	float wWan = 1;
	float wAvo = 1;
	float wSeek = 1;
	float wSep = 1;
	float wVel = 1;



	void Update(const SteeringOutput& steer, float deltaTime);
	void Stop();

	void LookToMovment();

	ofVec2f GetOrientationVector()
	{
		return ofVec2f(sinf(Orientation),
			cosf(Orientation));
	}
	float GetMovementOrientation()
	{
		return atan2(Velocity.y, Velocity.x);
	}

	void MoveForword();
};

