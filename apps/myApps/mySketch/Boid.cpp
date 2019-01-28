#include "Boid.h"
#include "ofGLProgrammableRenderer.h"


Boid::Boid()
{
	mRigidbody.Position.x = 0;
	mRigidbody.Position.y = 0;
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
	auto tri1 = pos; tri1.x += 60;
	auto tri2 = pos; tri2.y += 25; tri2.x += 10;
	auto tri3 = pos; tri3.y -= 25; tri3.x += 10;
	ofDrawTriangle(tri1.x, tri1.y, tri2.x, tri2.y, tri3.x, tri3.y);
	ofPopMatrix();//this restores the transformations saved before so the transformations made in between push and pop matrix dont affect what's drawn after this. 
	
	

	
}

void Boid::Update()
{

	mRigidbody.Update();

	if (mRigidbody.Position.x > ofGetWidth())
	{
		mRigidbody.Position.x = ofGetWidth();
	}
	if (mRigidbody.Position.x < 0)
	{
		mRigidbody.Position.x = 0;
	}

	if (mRigidbody.Position.y > ofGetHeight())
	{
		mRigidbody.Position.y = ofGetHeight();
	}
	
	if (mRigidbody.Position.y < 0)
	{
		mRigidbody.Position.y = 0;
	}
}

void Boid::Rotate(float rad)
{
	mRigidbody.Rotation = rad;
}
