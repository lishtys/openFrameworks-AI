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


float mapToRange(float rotRange)
{

	while(rotRange>3.14)
	{
		rotRange -= 3.14;
	}

	return rotRange;
}

void DynamicSeek::getSteering(SteeringOutput* output) 
{
	output->linear = targetBoid->Position-character->Position ;
	
	  if (output->linear.length() > 0)
        {
		  output->linear=output->linear.getNormalized();
		  output->linear *= maxAcceleration;
        }

}

void DynamicFlee::getSteering(SteeringOutput* output) 
{
	output->linear =  character->Position- targetBoid->Position;

	if (output->linear.length() > 0)
	{
		output->linear = output->linear.getNormalized();
		output->linear *= maxAcceleration;
	}
}

void DynamicArrive::getSteering(SteeringOutput* output) 
{

	auto dir = targetBoid->Position - character->Position;

	float targetSpeed;
	
	if (dir.length()< TargetRadius)
	{
		character->Stop();
	}
	else if((dir.length()>slowRadius))
	{
		targetSpeed = maxSpeed;
		output->linear = dir.getNormalized()*maxSpeed;
		if (output->linear.length() > maxAcceleration)
		{
			output->linear = output->linear.getNormalized()*maxAcceleration;
		}
	}
	else
	{
		auto factor = (dir.length() / slowRadius);
		 targetSpeed = maxSpeed * factor;
		auto targetVel =dir.getNormalized()*targetSpeed;
		auto acc = (targetVel - character->Velocity )/ofGetLastFrameTime();
		output->linear = acc;
		character->Linear = acc;
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

void DynamicAlign::getSteering(SteeringOutput* output)
{
	auto rotOffset = targetBoid->Rotation - character->Rotation;

	rotOffset = mapToRange(rotOffset);

	auto absRot = abs(rotOffset);

	if(rotOffset<targetAngleThreshold)  return;

	if(rotOffset>slowAngleThreshold)
	{
		output->angular = maxAngularAcc;
	}
	else
	{
		
		auto factor = absRot / slowAngleThreshold;
		auto targetRot = maxRotation * factor;
		targetRot *= (rotOffset / absRot);
		auto rotAcc = targetRot - character->Rotation/(ofGetLastFrameTime());
		output->angular = rotAcc;
	}

}





