#include "Boid.h"
#include "ofGLProgrammableRenderer.h"


Boid::Boid()
{
	mRigidbody.Position.x = 0;
	mRigidbody.Position.y = 0;
	UpdateWeight();
	
}


Boid::~Boid()
{
}

void Boid::Draw()
{

	auto pos = mRigidbody.Position;
	ofSetColor(mColor.r, mColor.g, mColor.b);
	ofPushMatrix();//this saves the current transformations, so you can restore them later.
	ofTranslate(pos.x,pos.y);
	ofRotateZRad(mRigidbody.Orientation);
	ofTranslate(-pos.x, -pos.y); //note the negative sign. this is to bring back the drawing position to 0,0.
	ofDrawCircle(pos.x, pos.y, CircleRadius);
	auto tri1 = pos; tri1.x += CircleRadius+7;
	auto tri2 = pos; tri2.y += (CircleRadius-2); tri2.x += CircleRadius/1.5f;
	auto tri3 = pos; tri3.y -= (CircleRadius-2); tri3.x += CircleRadius / 1.5f;
	ofDrawTriangle(tri1.x, tri1.y, tri2.x, tri2.y, tri3.x, tri3.y);
	ofPopMatrix();//this restores the transformations saved before so the transformations made in between push and pop matrix dont affect what's drawn after this. 


	for (auto point : mTrack.points)
	{
		ofDrawCircle(point.x, point.y,2);
	}
	
	
}
float timeCnt;
void Boid::Update(const SteeringOutput& steer, float deltaTime)
{
	mRigidbody.Update(steer, deltaTime);


	if(isPassingEdge)
	{
		if (mRigidbody.Position.x > ofGetWidth() + CircleRadius)
		{
			mRigidbody.Position.x = -CircleRadius;
		}
		if (mRigidbody.Position.x < -CircleRadius)
		{
			mRigidbody.Position.x = ofGetWidth() + CircleRadius;
		}

		if (mRigidbody.Position.y > ofGetHeight() + CircleRadius)
		{
			mRigidbody.Position.y = -CircleRadius;
		}

		if (mRigidbody.Position.y < -CircleRadius)
		{
			mRigidbody.Position.y = ofGetHeight() + CircleRadius;
		}
	}
	else
	{
		if (mRigidbody.Position.x > ofGetWidth() - CircleRadius)
		{
			mRigidbody.Position.x = ofGetWidth() -CircleRadius;
		}
		if (mRigidbody.Position.x < CircleRadius)
		{
			mRigidbody.Position.x = CircleRadius;
		}

		if (mRigidbody.Position.y > ofGetHeight() - CircleRadius)
		{
			mRigidbody.Position.y = ofGetHeight() - CircleRadius;
		}

		if (mRigidbody.Position.y < CircleRadius)
		{
			mRigidbody.Position.y =  CircleRadius;
		}
	}

	// Add Tracking

	timeCnt += ofGetLastFrameTime();
	if (timeCnt > .5)
	{
		mTrack.AddBoid(mRigidbody.Position);
		timeCnt = 0;
	}
	
	UpdateWeight();

}

void Boid::UpdateWeight()
{
	mRigidbody.wAvo = KAvoid;
	mRigidbody.wSeek = KSeek;
	mRigidbody.wWan = KWander;
	mRigidbody.wSep = KSeparate;
	mRigidbody.wVel = kVelMatch;
}


