#include "ofApp.h"
#include "../Boid.h"
#include "../BasicMotion.h"
#include "../SeekMotion.h"
#include "../WanderMotion.h"
#include "../FlockMotion.h"


 // BasicMotion motion;
   // SeekMotion motion;
     // WanderMotion motion;
  FlockMotion motion;

//--------------------------------------------------------------
void ofApp::setup(){
	motion.Init();
	// Seekmotion.Init();
	// Wondermotion.Init();
}

//--------------------------------------------------------------
void ofApp::update(){
	motion.Update();
	// Seekmotion.Update();
	// Wondermotion.Update();
}

//--------------------------------------------------------------
void ofApp::draw(){
	motion.Draw();
	// Seekmotion.Draw();
	// Wondermotion.Draw();
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
	motion.OnMousePressed(x,y,button);
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
