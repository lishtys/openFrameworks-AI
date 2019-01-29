#include "FlockSteering.h"



FlockSteering::FlockSteering()
{
	
}


FlockSteering::~FlockSteering()
{
}

void Separation::getSteering(SteeringOutput* output)
{
	for (auto element : boidTargets)
	{
		auto direction = element->mRigidbody.Position-character->Position;
		auto distance = direction.length();
		if(distance<threshold)
		{
			auto strength = K / (distance*distance);
			if(strength>maxAccerlation)
			{
				strength = maxAccerlation;
			}
			output->linear += strength * direction.normalize();
		}


		if(output->linear.length()>maxAccerlation)
		{
			output->linear=	output->linear.normalize()*maxAccerlation;
		}
	}
}



