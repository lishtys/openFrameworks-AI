#include "SeekMotion.h"
#include "of3dPrimitives.h"
#include "ofBitmapFont.h"


SeekMotion::SeekMotion()
{
}


SeekMotion::~SeekMotion()
{
}

void SeekMotion::Init()
{
	m_boid.mRigidbody.Position = ofVec2f(ofGetWindowWidth()/2, ofGetWindowHeight()/2);

	seek.character = &m_boid.mRigidbody;
	seek.targetBoid = &targetRigid;
	seek.maxAcceleration = 5;
	seek.maxAngularAcc = 10;
	seek.maxSpeed = 20;
}

void SeekMotion::Update()
{
	auto deltaTime = ofGetLastFrameTime();
	SteeringOutput steer;

	seek.getSteering(&steer);

	m_boid.Update(steer,deltaTime);



	if (m_boid.mRigidbody.Position.y == ofGetHeight() && m_boid.mRigidbody.Position.x == ofGetWidth())
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





}

void SeekMotion::Draw()
{
	m_boid.Draw();

	ofSetColor(0, 255, 0);
	ofDrawCircle(targetRigid.Position.x, targetRigid.Position.y, 10);
}

void SeekMotion::OnMousePressed()
{
  if(ofGetMousePressed())
  {
	  targetRigid.Position.x = ofGetMouseX();
	  targetRigid.Position.y = ofGetMouseY();
  }
}
