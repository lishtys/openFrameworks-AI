#include "Tracking.h"



Tracking::Tracking()
{
}


Tracking::~Tracking()
{
}

void Tracking::AddBoid(Boid boid)
{
	boid.mColor.g = 0;
	boid_list.push_back(boid);

}

void Tracking::Draw()
{
	for (Boid boid : boid_list)
	{
		boid.Draw();
	}
}
