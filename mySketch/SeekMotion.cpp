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

	arrive.character = &m_boid.mRigidbody;
	arrive.targetBoid = &targetRigid;
	arrive.maxAcceleration = 50;
	arrive.maxAngularAcc = 10;
	arrive.maxSpeed = 100;


	arrive.TargetRadius = 5;
	arrive.slowRadius = 200;
	arrive.timeToTarget = 5;;
}

void SeekMotion::Update()
{
	auto deltaTime = ofGetLastFrameTime();
	SteeringOutput steer;

	arrive.getSteering(&steer);

	m_boid.Update(steer,deltaTime);

	m_boid.mRigidbody.FaceToMovement();



}

void SeekMotion::Draw()
{
	m_boid.Draw();
	ofSetColor(0, 255, 0);
	ofDrawCircle(targetRigid.Position.x, targetRigid.Position.y, 10);


	ofDrawBitmapString(m_boid.mRigidbody.Velocity, 100, 100);

	
}

void SeekMotion::OnMousePressed()
{
  if(ofGetMousePressed())
  {
	  targetRigid.Position.x = ofGetMouseX();
	  targetRigid.Position.y = ofGetMouseY();
	  m_boid.mRigidbody.Stop();
  }
}
