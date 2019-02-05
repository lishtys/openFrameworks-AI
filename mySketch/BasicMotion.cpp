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
	m_boid.isPassingEdge = false;
	m_boid.mRigidbody.Velocity = ofVec2f(100, 0);
	m_boid.mRigidbody.Position = ofVec2f(0, ofGetHeight()- m_boid.CircleRadius);


	

}

void BasicMotion::Update()
{
	SteeringOutput steer;
	auto cRadius = m_boid.CircleRadius;
	if(m_boid.mRigidbody.Position.y == ofGetHeight()- cRadius && m_boid.mRigidbody.Position.x == ofGetWidth()- cRadius)
	{
		m_boid.mRigidbody.Velocity = ofVec2f(-100, 0);
	}
	else if (m_boid.mRigidbody.Position.y == ofGetHeight()- cRadius && m_boid.mRigidbody.Position.x == cRadius)
	{
		m_boid.mRigidbody.Velocity = ofVec2f(0, -100);
	}
	else if (m_boid.mRigidbody.Position.y == cRadius && m_boid.mRigidbody.Position.x == ofGetWidth()- cRadius)
	{
		m_boid.mRigidbody.Velocity = ofVec2f(0, 100);

	}
	else if (m_boid.mRigidbody.Position.y == cRadius && m_boid.mRigidbody.Position.x == cRadius)
	{
		m_boid.mRigidbody.Velocity = ofVec2f(100, 0);

	}

	m_boid.Update(steer, ofGetLastFrameTime());

	m_boid.mRigidbody.LookToMovment();






}

void BasicMotion::Draw()
{
	m_boid.Draw();
}

void BasicMotion::OnMousePressed(int x,int y,int button)
{

	

}




