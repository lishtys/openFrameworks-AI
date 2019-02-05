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

	targetRigid.Orientation =5;
	arrive.character = &m_boid.mRigidbody;
	arrive.targetBoid = &targetRigid;
	arrive.maxAcceleration = 50;
	arrive.maxAngularAcc = 10;
	arrive.maxSpeed = 100;


	arrive.TargetRadius = 5;
	arrive.slowRadius = 200;
	arrive.timeToTarget = 5;;

	align.character = &m_boid.mRigidbody;
	align.targetBoid = &targetRigid;

	align.maxAcceleration = 50;
	align.maxAngularAcc = 1;
	align.maxSpeed = 100;

	align.maxRotation = 2;
	align.slowAngleThreshold = 0.3;
	align.targetAngleThreshold = 0.1;
	align.timeToTarget = .2;

}

void SeekMotion::Update()
{
	auto deltaTime = ofGetLastFrameTime();
	SteeringOutput steer;

	arrive.getSteering(&steer);

	targetRigid.Orientation = align.character->GetMovementOrientation();
	align.getSteering(&steer);

	m_boid.Update(steer, deltaTime);




}

void SeekMotion::Draw()
{
	m_boid.Draw();
	ofSetColor(0, 255, 0);
	ofDrawCircle(targetRigid.Position.x, targetRigid.Position.y, 10);


	ofDrawBitmapString(m_boid.mRigidbody.Velocity, 100, 100);

	
}

void SeekMotion::OnMousePressed(int x,int y,int button)
{
  if(ofGetMousePressed())
  {
	  targetRigid.Position.x = ofGetMouseX();
	  targetRigid.Position.y = ofGetMouseY();
  }
}
