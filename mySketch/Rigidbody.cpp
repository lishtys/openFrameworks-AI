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

	Velocity.x += steer.linear.x*deltaTime;
	Velocity.y += steer.linear.y*deltaTime;
	
	Rotation += deltaTime * steer.angular;

	 Position += ofGetLastFrameTime()*Velocity;
	 Orientation += ofGetLastFrameTime()*Rotation;
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



