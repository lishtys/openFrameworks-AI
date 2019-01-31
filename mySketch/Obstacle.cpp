#include "Obstacle.h"
#include "ofBitmapFont.h"


Obstacle::Obstacle()
{
	mRigidbody.Position.x = 0;
	mRigidbody.Position.y = 0;
}


Obstacle::~Obstacle()
{
}

void Obstacle::Draw()
{

	auto pos = mRigidbody.Position;
	ofSetColor(100, 125, 200);
	ofPushMatrix();//this saves the current transformations, so you can restore them later.
	ofTranslate(pos.x, pos.y);
	ofRotateZRad(mRigidbody.Orientation);
	ofTranslate(-pos.x, -pos.y); //note the negative sign. this is to bring back the drawing position to 0,0.
	ofDrawCircle(pos.x, pos.y, CircleRadius);
	auto tri1 = pos; tri1.x += CircleRadius + 7;
	auto tri2 = pos; tri2.y += (CircleRadius - 2); tri2.x += CircleRadius / 1.5f;
	auto tri3 = pos; tri3.y -= (CircleRadius - 2); tri3.x += CircleRadius / 1.5f;
	ofDrawTriangle(tri1.x, tri1.y, tri2.x, tri2.y, tri3.x, tri3.y);
	ofPopMatrix();//this restores the transformations saved before so the transformations made in between push and pop matrix dont affect what's drawn after this. 

}
