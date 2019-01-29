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

	//Always face to move direction

	if (Velocity.length() > 0) {
		Orientation = atan2(Velocity.x, Velocity.y);
	}


	 Position += ofGetLastFrameTime()*Velocity;
	
}
