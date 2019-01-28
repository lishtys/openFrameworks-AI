#include "Rigidbody.h"
#include "of3dPrimitives.h"


Rigidbody::Rigidbody()
{
}


Rigidbody::~Rigidbody()
{
}

void Rigidbody::Update()
{
	 Position += ofGetLastFrameTime()*Velocity;
	
}
