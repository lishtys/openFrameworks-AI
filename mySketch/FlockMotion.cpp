#include "FlockMotion.h"
#include <ofAppGlutWindow.h>
#include "of3dPrimitives.h"
#include "ofBitmapFont.h"


FlockMotion::FlockMotion()
{
}


FlockMotion::~FlockMotion()
{
}

void FlockMotion::Init()
{


	for (unsigned i = 0; i < 20; i++)
	{
		Boid boid;
		boid.mRigidbody.Position.x = ofRandomWidth();
		boid.mRigidbody.Position.y = ofRandomHeight();
		boid.mRigidbody.Orientation = ofRandomf() * 2 * 3.141592;
		// boid.mRigidbody.Velocity.x = ofRandomf() * 4;
		// boid.mRigidbody.Velocity.y = ofRandomf() * 10;
		boid.mRigidbody.Rotation = 0;
		flock.boid_list.push_back(boid);
	
	}

	flock.maxAccerlation = 10;

	separation.mFlock = &flock;
	separation.threshold = 200;
	separation.K = 10000000;

}

void FlockMotion::Update()
{
	for (unsigned i = 0; i < 20; i++)
	{
	
		SteeringOutput steering_output;
		separation.mCharacter = &flock.boid_list[i];
		separation.getSteering(&steering_output);
		flock.boid_list[i].Update(steering_output, ofGetLastFrameTime());
	}
}

void FlockMotion::Draw()
{
	for (unsigned i = 0; i < 20; i++)
	{

		flock.boid_list[i].Draw();
	}

	
}

void FlockMotion::OnMousePressed(int x, int y)
{
	for (unsigned i = 0; i < 20; i++)
	{
		auto boid = &flock.boid_list[i];
		auto pos= flock.boid_list[i].mRigidbody.Position;
		float dist = ofDist(pos.x, pos.y,x , y);
		 if (dist < boid->CircleRadius)
		{
			if (flock.leader != nullptr) flock.leader->mColor = { 0,0,0 };
			flock.leader = boid;  boid->mColor = { 255,0,0 };
			flock.leader->mRigidbody.Stop();
		}
	}

	
}
