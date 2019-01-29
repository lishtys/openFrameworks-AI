#include "DynamicSteering.h"
#include "of3dPrimitives.h"


DynamicSteering::DynamicSteering()
{
}


DynamicSteering::~DynamicSteering()
{
}

float randomBinomial(float max)
{
	
	return  max * (float(rand()) / RAND_MAX)- max * (float(rand()) / RAND_MAX); 
}

void DynamicSeek::getSteering(SteeringOutput* output) 
{
	output->linear -= targetBoid->Position;
	
	  if (output->linear.length() > 0)
        {
		  output->linear=output->linear.getNormalized();
		  output->linear *= maxAcceleration;
        }

}

void DynamicFlee::getSteering(SteeringOutput* output) 
{
	output->linear -= targetBoid->Position;

	if (output->linear.length() > 0)
	{
		output->linear = output->linear.getNormalized();
		output->linear *= maxAcceleration;
	}
}

void DynamicArrive::getSteering(SteeringOutput* output) 
{

	output->linear -= targetBoid->Position;

	
	if (output->linear.length()< TargetRadius)
	{
		output->linear = { 0,0 };
	}
	else if((output->linear.length()>slowRadius))
	{
		output->linear *= maxSpeed;
	}else
	{
		auto factor = (output->linear.length() / slowRadius);
		auto targetSpeed = maxSpeed * factor;
		auto targetVel = output->linear.getNormalized()*targetSpeed;
		auto acc = (targetVel - output->linear) / ofGetLastFrameTime();
		output->linear = acc;
	}

	if(output->linear.length()>maxAcceleration)
	{
		output->linear = output->linear.getNormalized()*maxAcceleration;
	}


}

void DynamicWander::getSteering(SteeringOutput* output)
{
	if (targetBoid->Position.length() == 0) {
		wanderTarget = character->Position;
		wanderTarget.x += viewRange;
	}


	auto distance = targetBoid->Position - character->Position;
	float angle;
	if (distance.x*distance.x + distance.y*distance.y > 0) {
		angle = atan2f(distance.y, distance.x);
	}
	else
	{
		angle = 0;
	}

	wanderTarget = character->Position;
	wanderTarget.x += viewRange * cosf(angle);
	wanderTarget.y+= viewRange * sinf(angle);

	wanderTarget.x += randomBinomial(turnSpeed);
	wanderTarget.y += randomBinomial(turnSpeed);


	// Seek
	output->linear = wanderTarget;
	output->linear -= character->Position;

	if (output->linear.length() > 0)
	{
		output->linear=output->linear.getNormalized();
		output->linear *= maxAcceleration;
	}
}




