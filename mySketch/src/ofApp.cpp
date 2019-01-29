#include "ofApp.h"
#include "../Boid.h"
#include "../BasicMotion.h"
#include "../SeekMotion.h"

BasicMotion BasicMotion;
SeekMotion Seekmotion;

//--------------------------------------------------------------
void ofApp::setup(){
	//BasicMotion.Init();
	Seekmotion.Init();

}

//--------------------------------------------------------------
void ofApp::update(){
//	BasicMotion.Update();
	Seekmotion.Update();
}

//--------------------------------------------------------------
void ofApp::draw(){
//	BasicMotion.Draw();
	Seekmotion.Draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	Seekmotion.OnMousePressed();
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
