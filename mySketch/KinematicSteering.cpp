#include "KinematicSteering.h"
#include <ofAppGlutWindow.h>
#include "SeekMotion.h"
#include "of3dPrimitives.h"


KinematicSteering::KinematicSteering()
{
}


KinematicSteering::~KinematicSteering()
{
}

void KinematicSeek::getSteering(SteeringOutput* output)
{
	auto dir = targetBoid->Position - character->Position;

	if(dir.length()>0)
	{
	   output->Velocity= 	dir.normalize()*maxSpeed;
	}
}

void KinematicFlee::getSteering(SteeringOutput* output)
{
	auto dir = character->Position- targetBoid->Position;

	if (dir.length() > 0)
	{
		output->Velocity = dir.normalize()*maxSpeed;
	}
}

void KinematicArrive::getSteering(SteeringOutput* output)
{
	auto dir = character->Position - targetBoid->Position;
	auto distance = dir.length();

	ofVec2f targetVel;
	if(distance<targetRadius)
	{
		targetVel = dir.getNormalized()* maxSpeed*(distance / targetRadius);
		output->Velocity = (targetVel - character->Velocity) / timeToTarget;
	}else
	{
		output->Velocity = dir.getNormalized()*maxSpeed;
	}
}

float GetBiRandom(int max)
{
	return  ofRandom(max) - ofRandom(max);
}


void KinematicWander::getSteering(SteeringOutput* output)
{
	auto wanderDelta = GetBiRandom(3); // Determine noise ratio
	auto dir = character->Velocity.getNormalized(); // Get center of wander circle
	dir*=(60); // Multiply by distance
	auto center =dir+(character->Position);
	// Apply offset to get new target    
	auto offset =  ofVec2f(wanderRadius*cos(wanderDelta), wanderRadius*sin(wanderDelta));
	wanderTarget =center+ offset; 

	// Steer toward new target    
	auto seekDir = wanderTarget - character->Position;

	if (seekDir.length() > 0)
	{
		output->Velocity = seekDir.getNormalized()*maxSpeed;
	}
}

void Avoid::getSteering(SteeringOutput* output)
{
	
	if(character->Velocity.length()>0)
	{
		{
			auto diff = element->mRigidbody.Position - character->Position;
			auto dist = diff.length();

			auto bound = element->CircleRadius+characterRadius + offset;

			if(dist<bound)
			{
				character->wAvo= 100.0f;
				character->wWan = 0.1f;
				float collision = (element->CircleRadius + characterRadius) ;

				if(dist <collision)
				{
					auto dir = character->Position - element->mRigidbody.Position;
					output->linear = diff;
					output->linear *= output->linear.getNormalized()*100;
					
				}
				else
				{
					auto moveDir = element->mRigidbody.Position - (character->Position + character->Velocity*ofGetLastFrameTime());

					if(moveDir.length()<dist)
					{
						if (abs(character->Velocity.x) <= abs(character->Velocity.y)) {

							output->linear = ofVec2f((character->Position.x - element->mRigidbody.Position.x), character->Velocity.y);
							output->linear = output->linear.getNormalized()*(50*((bound) / dist));
						}
						else {
							output->linear = ofVec2f(character->Velocity.x, (character->Position.y - element->mRigidbody.Position.y));
							output->linear = output->linear.getNormalized()*(50*((bound) / dist));
						}
					}
				}
			}

		}


	}







}


