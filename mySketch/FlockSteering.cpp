#include "FlockSteering.h"



FlockSteering::FlockSteering()
{
	
}


FlockSteering::~FlockSteering()
{
	
}



void Separation::getSteering(SteeringOutput* output)
{
	auto boid_list = mFlock->boid_list;
	auto leader = mFlock->leader;
	auto maxAccerlation = mFlock->maxAccerlation;

	for (auto element : boid_list)
	{
		if(&element==mCharacter) continue;;
		
		ofVec2f targetPos;

		if(leader!=NULL)
		{
			targetPos= leader->mRigidbody.Position;
		}else
		{
			targetPos = mFlock->GetNeighbourhoodCenter();
		}

		auto direction = element.mRigidbody.Position - targetPos;
		auto distance = direction.length();
		
		if(distance<threshold)
		{
			auto strength = maxAccerlation * (threshold - distance) / threshold;
	
			output->linear += strength * direction.normalize();
		}


		if(output->linear.length()>maxAccerlation)
		{
			output->linear=	output->linear.normalize()*maxAccerlation;
		}
	}
}



