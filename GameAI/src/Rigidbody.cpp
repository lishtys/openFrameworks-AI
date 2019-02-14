#include "Rigidbody.h"
#include "of3dPrimitives.h"
#include "SteeringOutput.h"


Rigidbody::Rigidbody()
{
}


Rigidbody::~Rigidbody()
{
}

void Rigidbody::Update(const SteeringOutput& steer,float deltaTime)
{
	maxX = ofGetWidth();
	maxY = ofGetHeight();
	auto linear = steer.linear;

	Rotation += deltaTime * steer.angular;

	Velocity += steer.Velocity*deltaTime;
	Rotation += steer.Rotation*deltaTime;


	// limit force
	float distMaxForce = ABS(linear.x) + ABS(linear.y);
	if (distMaxForce > maxForce) {
		distMaxForce = maxForce / distMaxForce;
		linear.x *= distMaxForce;
		linear.y *= distMaxForce;
	}

	Velocity.x += linear.x*deltaTime;
	Velocity.y += linear.y*deltaTime;


	// limit speed

	float distMaxSpeed = ABS(Velocity.x) + ABS(Velocity.y);
	if (distMaxSpeed > maxSpeed) {
		distMaxSpeed = maxSpeed / distMaxSpeed;
		Velocity.x *= distMaxSpeed;
		Velocity.y *= distMaxSpeed;
	}



	Position += deltaTime * Velocity;

	Bound();

	Orientation += deltaTime * Rotation;
	Orientation = fmodf(Orientation, 2 * 3.141592);
}

void Rigidbody::Stop()
{

	Velocity = { 0,0 };
	
}

void Rigidbody::LookToMovment()
{
	if (Velocity.length() > 0) {
		Orientation = atan2(Velocity.y, Velocity.x);
	}
}

void Rigidbody::MoveForword()
{
	auto dir = GetOrientationVector();
	Velocity=	Velocity.length()*dir.getNormalized();
}



