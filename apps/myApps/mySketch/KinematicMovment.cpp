#include "KinematicMovment.h"


KinematicMovment::KinematicMovment()
{
}


KinematicMovment::~KinematicMovment()
{
}

float randomBinomial(float max)
{
	
	return  max * (float(rand()) / RAND_MAX)- max * (float(rand()) / RAND_MAX); 
}

void KinematicSeek::getSteering(SteeringOutput* output) const
{
	output->linear -= targetBoid->Position;
	
	  if (output->linear.length() > 0)
        {
		  output->linear=output->linear.getNormalized();
		  output->linear *= maxSpeed;
        }

}

void KinematicFlee::getSteering(SteeringOutput* output) const
{
	output->linear -= targetBoid->Position;

	if (output->linear.length() > 0)
	{
		output->linear = output->linear.getNormalized();
		output->linear *= maxSpeed;
	}
}

void KinematicArrive::getSteering(SteeringOutput* output) const
{
	



	output->linear -= targetBoid->Position;

	
	if (output->linear.length()< radius)
	{
		output->linear = { 0,0 };
	}
	else
	{
		output->linear *= ((float)1.0 / timeStop);

		if (output->linear.length() > maxSpeed)
		{
			output->linear=output->linear.getNormalized();
			output->linear *= maxSpeed;
		}
	}


}

void KinematicWander::getSteering(SteeringOutput* output) const
{
	auto orien = targetBoid->Orientation;
	auto linear = ofVec2f(sin(orien), cos(orien));
	output->linear = linear;
	output->linear *= maxSpeed;

	float view = randomBinomial(1);
	output->angular = view * maxRotation;
}


