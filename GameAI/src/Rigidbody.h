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
	float maxForce=20;


	//Weights
	float wWan = 1;
	float wAvo = 1;
	float wSeek = 1;
	float wSep = 1;
	float wVel = 1;
	
	//Bound Mode
	int boundMode =1;
	float minX;
	float minY;
	float maxX;
	float maxY;
	
	


	void Update(const SteeringOutput& steer, float deltaTime);


	void Bound()
	{
		switch (boundMode) {
		case 0: // CLAMP

			if (Position.x < minX) {
				Position.x = minX;
				Velocity.x = -Velocity.x;
			}
			if (Position.x > maxX) {
				Position.x = maxX;
				Velocity.x = -Velocity.x;
			}
			if (Position.y < minY) {
				Position.y = minY;
				Velocity.y = -Velocity.y;
			}
			if (Position.y > maxY) {
				Position.y = maxY;
				Velocity.y = -Velocity.y;
			}
			break;
			case 1: // WRAP
				if (Position.x <minX) {
					Position.x += maxX;
				}
				if (Position.x > maxX) {
					Position.x -= maxX;
				}
				if (Position.y < minY) {
					Position.y += maxY;
				}
				if (Position.y > maxY) {
					Position.y -= maxY;
				}
		}
	}
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

