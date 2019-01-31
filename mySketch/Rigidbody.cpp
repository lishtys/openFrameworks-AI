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
	//Dynamic
	auto linear = steer.linear;


	Velocity.x += linear.x*deltaTime;
	Velocity.y +=linear.y*deltaTime;

	Rotation += deltaTime * steer.angular;

	//Kinematic
	Velocity += steer.Velocity*deltaTime;
	Rotation += steer.Rotation*deltaTime;






	if(Velocity.length()>maxSpeed)
	{
		Velocity= Velocity.getNormalized()*maxSpeed;
	}


	 Position += deltaTime*Velocity;
	 Orientation += deltaTime *Rotation;
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



