#include "DynamicSteering.h"
#include "of3dPrimitives.h"


DynamicSteering::DynamicSteering()
{
	character = nullptr;
	targetBoid = nullptr;
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

	while(rotRange>3.1415926)
	{
		rotRange -=2*3.1415926;
	}

	while (rotRange<2*-3.1415926)
	{
		rotRange +=2* 3.1415926;
	}



	return rotRange;
}

void DynamicSeek::getSteering(SteeringOutput* output) 
{
	if(targetBoid!=NULL)
	{
		output->linear = targetBoid->Position - character->Position;
	}
	else
	{
		output->linear =( targetPosition - character->Position)/50;
	}

	  if (output->linear.length()> maxAcceleration)
        {
		  output->linear=output->linear.getNormalized();
		  output->linear *= maxAcceleration;
        }

}

void DynamicFlee::getSteering(SteeringOutput* output) 
{
	if(targetBoid!=nullptr)
	{
		output->linear = character->Position- targetBoid->Position ;
	}
	else
	{
		output->linear = character->Position- targetPosition ;
	}


	if (output->linear.length() > maxAcceleration)
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
	
	}


}

float GetRandom(int max)
{
	return  ofRandom(max) - ofRandom(max);
}


void DynamicWander::getSteering(SteeringOutput* output)
{

	auto wanderDelta = GetRandom(4); 
	auto dir = character->Velocity.getNormalized(); 
	dir *= (200); // Multiply by distance
	auto center = dir + (character->Position);
	// Apply offset to get new target    
	auto offset = ofVec2f(wanderRadius*cos(wanderDelta), wanderRadius*sin(wanderDelta));
	wanderTarget = center + offset;

	// Steer toward new target    
	auto seekDir = wanderTarget - character->Position;

	if (seekDir.length() > 0)
	{
		output->linear = seekDir.getNormalized();
		output->linear *= 25;
	}

}

void DynamicAlign::getSteering(SteeringOutput* output)
{
	auto rotOffset = targetBoid->Orientation - character->Orientation;

	rotOffset = mapToRange(rotOffset);

	auto absRot = abs(rotOffset);

	if (absRot < targetAngleThreshold)
	{
		character->Rotation = 0;
		return;
	}

	if(absRot >slowAngleThreshold)
	{
		character->Rotation = maxRotation;
	}
	else
	{
		
		auto factor = absRot / slowAngleThreshold;
		auto targetRot = maxRotation * factor;
		targetRot *= (rotOffset / absRot);
		auto rotAcc = (targetRot - character->Orientation)/timeToTarget;
		output->angular = rotAcc;

		if(output->angular>maxAngularAcc)
		{
			output->angular = maxAngularAcc;
		}
	}

}







