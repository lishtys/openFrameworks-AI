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
	Rotation += steer.angular*Rotation;

	


	 Position += ofGetLastFrameTime()*Velocity;
	
}

void Rigidbody::Stop()
{

	Velocity = { 0,0 };
	
}

void Rigidbody::FaceToMovement()
{

	if (Velocity.length() > 0) {
		Orientation = atan2(Velocity.y, Velocity.x);
	}
}
