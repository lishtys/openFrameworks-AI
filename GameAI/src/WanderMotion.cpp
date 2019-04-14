#include "WanderMotion.h"
#include "ofMesh.h"
#include "ofGLProgrammableRenderer.h"


WanderMotion::WanderMotion()
{
}


WanderMotion::~WanderMotion()
{
}

void WanderMotion::Init()
{
	m_boid.mRigidbody.Position = ofVec2f(ofGetWindowWidth() / 2, ofGetWindowHeight() / 2);
	
	// Dynamic
	wander.character = &m_boid.mRigidbody;
	wander.targetBoid = &targetRigid;



	
	
	align.character = &m_boid.mRigidbody;
	align.targetBoid = &targetRigid;
	align.maxAngularAcc = 1;
	align.maxSpeed = 100;

	align.maxRotation = 5;
	align.slowAngleThreshold = .5;
	align.targetAngleThreshold = 0.1;
	align.timeToTarget = .2;



	//Kinematic

	kinematic_wander.character= &m_boid.mRigidbody;
	kinematic_wander.maxSpeed = 10;
	


}

void WanderMotion::Update()
{
	auto deltaTime = ofGetLastFrameTime();
	SteeringOutput steer;

	 // kinematic_wander.getSteering(&steer);

	 wander.getSteering(&steer);
 
	 targetRigid.Orientation = m_boid.mRigidbody.GetMovementOrientation();
	 align.getSteering(&steer);
	 m_boid.Update(steer, deltaTime);

	
	// m_boid.mRigidbody.LookToMovment();

	
}

void WanderMotion::Draw()
{
	m_boid.Draw();
	ofDrawCircle(targetRigid.Position.x, targetRigid.Position.y, 10);
	ofDrawBitmapString(targetRigid.Orientation,100, 200);
}

void WanderMotion::OnMousePressed(int x,int y,int button)
{
	if (ofGetMousePressed())
	{
		targetRigid.Position.x = ofGetMouseX();
		targetRigid.Position.y = ofGetMouseY();
	}
}
