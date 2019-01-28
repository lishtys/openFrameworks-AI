#include "Kinematic.h"
#include "of3dPrimitives.h"


Kinematic::Kinematic()
{
}


Kinematic::~Kinematic()
{
}

void Kinematic::Update()
{
	 Position += ofGetLastFrameTime()*Velocity;
	
}
