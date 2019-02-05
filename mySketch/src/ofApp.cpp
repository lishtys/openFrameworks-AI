#include "ofApp.h"
#include "../Boid.h"
#include "../BasicMotion.h"
#include "../SeekMotion.h"
#include "../WanderMotion.h"
#include "../FlockMotion.h"


	BasicMotion bMotion;
	SeekMotion sMotion;
    WanderMotion wMotion;
	FlockMotion fMotion;

//--------------------------------------------------------------
void ofApp::setup(){





	switch (currentMotionIdx)
	{
	case 0: bMotion.Init();break;
	case 1: sMotion.Init();break;
	case 2: wMotion.Init();break;
	case 3: fMotion.Init();break;

	}
	
}

//--------------------------------------------------------------
void ofApp::update(){
	

	switch (currentMotionIdx)
	{
	case 0: bMotion.Update(); break;
	case 1: sMotion.Update(); break;
	case 2: wMotion.Update(); break;
	case 3: fMotion.Update(); break;

	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	
	switch (currentMotionIdx)
	{
	case 0: bMotion.Draw(); break;
	case 1: sMotion.Draw(); break;
	case 2: wMotion.Draw(); break;
	case 3: fMotion.Draw(); break;

	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

	if (key == 'q') currentMotionIdx = 0;
	if (key == 'w') currentMotionIdx = 1;
	if (key == 'e') currentMotionIdx = 2;
	if (key == 'r') currentMotionIdx = 3;

	setup();

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	switch (currentMotionIdx)
	{
	case 0: bMotion.OnMousePressed(x,y,button); break;
	case 1: sMotion.OnMousePressed(x, y, button); break;
	case 2: wMotion.OnMousePressed(x, y, button); break;
	case 3: fMotion.OnMousePressed(x, y, button); break;

	}
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
