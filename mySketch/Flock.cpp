#include "Flock.h"



Flock::Flock()
{
}


Flock::~Flock()
{
}

ofVec2f Flock::GetNeighbourhoodCenter()
{
	ofVec2f center;
	std::vector<Boid>::iterator iterator;

	int i = 0;
	int count = 0;
	
	for (iterator = boid_list.begin(); iterator != boid_list.end(); iterator++, i++)
	{
		
		{
			center += (iterator)->mRigidbody.Position;
			count++;
		}
	}
	center *= 1.0 / count;

	return  center;
}
