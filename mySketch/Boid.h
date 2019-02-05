#pragma once
#include "Rigidbody.h"
#include "Tracking.h"


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

	void UpdateWeight();

	//kWeight
	float KArrive = 1.0f;
	float KDepart = 1.0f;
	float KPursue = 1.0f;
	float KEvade = 1.0f;
	float KWander = 1.0f;
	float KAvoid = 1000.0f;
	float KSeek = 2.0f;
	float KCohesion = 1.0f;
	float KSeparate = 2.0f;
	float KAlignment = 1.0f;
	float kVelMatch = 5.0f;

	bool isPassingEdge = true;

	Tracking mTrack;
};




