#include "BasicMotion.h"
#include "of3dPrimitives.h"


BasicMotion::BasicMotion()
{

}


BasicMotion::~BasicMotion()
{
}

void BasicMotion::Init()
{
	m_boid.mRigidbody.Velocity = ofVec2f(100, 0);

}

void BasicMotion::Update()
{
	//SteeringOutput steer;
	//m_boid.Update(&steer,ofGetLastFrameTime());

	if(m_boid.mRigidbody.Position.y == ofGetHeight() && m_boid.mRigidbody.Position.x == ofGetWidth())
	{
		m_boid.mRigidbody.Orientation = 3.14;
		m_boid.mRigidbody.Velocity = ofVec2f(-100, 0);
	}
	else if (m_boid.mRigidbody.Position.y == ofGetHeight() && m_boid.mRigidbody.Position.x == 0)
	{
		m_boid.mRigidbody.Orientation = 4.6;
		m_boid.mRigidbody.Velocity = ofVec2f(0, -100);
	}
	else if (m_boid.mRigidbody.Position.y == 0 && m_boid.mRigidbody.Position.x == ofGetWidth())
	{
		m_boid.mRigidbody.Orientation = 1.571;
		m_boid.mRigidbody.Velocity = ofVec2f(0, 100);

	}
	else if (m_boid.mRigidbody.Position.y == 0 && m_boid.mRigidbody.Position.x == 0)
	{
		m_boid.mRigidbody.Orientation = 0;

	}

	

	// Add Tracking

	timeCnt += ofGetLastFrameTime();
	if(timeCnt>2)
	{
		Boid boid;
		boid.mRigidbody.Position = m_boid.mRigidbody.Position;
		boid.mRigidbody.Orientation = m_boid.mRigidbody.Orientation;
		mTrack.AddBoid(boid);
		timeCnt = 0;
	}


}

void BasicMotion::Draw()
{
	mTrack.Draw();
	m_boid.Draw();
}


void BasicMotion::Rotate(float rad)
{
	m_boid.Rotate(rad);
}



