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
	ofPopMatrix();//this restores the transformations saved before so the transformations made in between push and pop matrix dont affect what's drawn after this. 

}
