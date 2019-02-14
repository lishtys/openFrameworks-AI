#include "Tracking.h"


Tracking::Tracking()
{
}


Tracking::~Tracking()
{
}

void Tracking::AddBoid(ofVec2f vec2_f)
{
	if(points.size()<=30)
	{
		points.push_back(vec2_f);
	}else
	{
		points.erase(points.begin());
		points.push_back(vec2_f);
	}
}


