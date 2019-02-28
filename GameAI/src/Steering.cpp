#include "Steering.h"
#include "of3dPrimitives.h"


Steering::Steering()
{
	character = nullptr;
	targetBoid = nullptr;
}


Steering::~Steering()
{
}

float randomBinomial(float max)
{
	
	return  max * (float(rand()) / RAND_MAX)- max * (float(rand()) / RAND_MAX); 
}

float GetRandom(int max)
{
	return  ofRandom(max) - ofRandom(max);
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

	auto dir = targetPosition - character->Position;
	if (targetBoid != NULL)
	{
		dir = targetBoid->Position - character->Position;
	}

	float targetSpeed;
	
	if (dir.length()< TargetRadius)
	{
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





void KinematicArrive::getSteering(SteeringOutput* output)
{
	auto dir = character->Position - targetBoid->Position;
	auto distance = dir.length();

	ofVec2f targetVel;
	if (distance < targetRadius)
	{
		targetVel = dir.getNormalized()* maxSpeed*(distance / targetRadius);
		output->Velocity = (targetVel - character->Velocity) / timeToTarget;
	}
	else
	{
		output->Velocity = dir.getNormalized()*maxSpeed;
	}
}


void KinematicWander::getSteering(SteeringOutput* output)
{
	auto wanderDelta = randomBinomial(3)*1.5; // Determine noise ratio
	auto dir = character->Velocity.getNormalized(); // Get center of wander circle
	dir *= (60); // Multiply by distance
	auto center = dir + (character->Position);
	// Apply offset to get new target    
	auto offset = ofVec2f(wanderRadius*cos(wanderDelta), wanderRadius*sin(wanderDelta));
	wanderTarget = center + offset;

	// Steer toward new target    
	auto seekDir = wanderTarget - character->Position;

	if (seekDir.length() > 0)
	{
		output->Velocity = seekDir.getNormalized()*maxSpeed;
	}
}


void Avoid::getSteering(SteeringOutput* output)
{
	{
		for (auto element : elements)
		{
			auto diff = element.mRigidbody.Position - character->Position;
			auto dist = diff.length();

			auto bound = element.CircleRadius + characterRadius + offset;

			if (dist < bound)
			{
				character->wAvo = 200.0f;
				character->wWan = 0.1f;
				float collision = (element.CircleRadius + characterRadius);

				if (dist < collision)
				{
					auto dir = character->Position - element.mRigidbody.Position;
					output->linear = diff;
					output->linear *= output->linear.getNormalized() * 100;

				}
				else
				{
					auto moveDir = element.mRigidbody.Position - (character->Position + character->Velocity*ofGetLastFrameTime());

					if (moveDir.length() < dist)
					{
						if (abs(character->Velocity.x) <= abs(character->Velocity.y)) {

							output->linear = ofVec2f((character->Position.x - element.mRigidbody.Position.x), character->Velocity.y);
							output->linear = output->linear.getNormalized()*(50 * ((bound) / dist));
						}
						else {
							output->linear = ofVec2f(character->Velocity.x, (character->Position.y - element.mRigidbody.Position.y));
							output->linear = output->linear.getNormalized()*(50 * ((bound) / dist));
						}
					}
				}
			}

		}


	}
}

void Follow::getSteering(SteeringOutput* output)
{
	if(path.size()==0) return;

	auto predict = character->Velocity;
	predict.normalize();
	auto targetNode = path[path.size() - curIdx - 1];
	
	
	{
		if (character->Position.distance(targetNode->worldPos) < pRadius)
		{
			if (curIdx < path.size() - 1)
			{
				curIdx++;
			}
			else
			{
				return;
			}
		}

		if (curIdx >= path.size())
			return;

	}
	

	
	if (curIdx < path.size() - 1)
	{
		KinematicSeek seek;
		seek.character = character;
		seek.maxSpeed = 100;
		seek.targetPosition = path[path.size()-curIdx-1]->worldPos;
		seek.getSteering(output);
	}

	if (curIdx == path.size() - 1)
	{
		DynamicArrive arrive;
		arrive.character = character;
		arrive.maxAcceleration = 50;
		arrive.maxAngularAcc = 10;
		arrive.maxSpeed = 100;


		arrive.TargetRadius = 5;
		arrive.slowRadius = 200;
		arrive.timeToTarget = 5;
		arrive.targetPosition = path[path.size() - curIdx - 1]->worldPos;
		arrive.getSteering(output);
	}
}


void KinematicSeek::getSteering(SteeringOutput* output)
{
	auto dir = targetPosition - character->Position;
	if (targetBoid != NULL)
	{
		 dir = targetBoid->Position - character->Position;
	}
	


	if (dir.length() > 0)
	{
		output->Velocity = dir.normalize()*maxSpeed;
	}
}

void KinematicFlee::getSteering(SteeringOutput* output)
{
	auto dir = character->Position - targetBoid->Position;

	if (dir.length() > 0)
	{
		output->Velocity = dir.normalize()*maxSpeed;
	}
}