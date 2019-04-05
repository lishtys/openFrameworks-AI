#include "ofApp.h"

#include "BasicMotion.h"
#include "SeekMotion.h"
#include "WanderMotion.h"
#include "FlockMotion.h"
#include "AStarPathfinding.h"
#include "DFSPathfinding.h"


BasicMotion bMotion;
SeekMotion sMotion;
WanderMotion wMotion;
FlockMotion fMotion;

AStarPathfinding a_pathfinding;
DFSPathfinding d_pathfinding;




bool ofApp::useAStar;
bool  ofApp::useMap;
int ofApp::editorRow;
int ofApp::editorColumns;
int ofApp::HeuristicsType;
float ofApp::hWeight;
bool ofApp::needBoid;
bool ofApp::showImg;
bool ofApp::showUnwalkableNode;



void ofApp::onDropdownEvent(ofxDatGuiDropdownEvent e)
{


	
}


void ofApp::onToggleBoidEvent(ofxDatGuiToggleEvent e)
{
}


void ofApp::onMapDropdownEvent(ofxDatGuiDropdownEvent e)
{
	
}

void ofApp::onShowNodeDropdownEvent(ofxDatGuiDropdownEvent e)
{
	
}

void ofApp::onHeuristicsDropdownEvent(ofxDatGuiDropdownEvent e)
{
	
}

void ofApp::onButtonEvent(ofxDatGuiButtonEvent e)
{
		
}

void ofApp::onButtonGetPathEvent(ofxDatGuiButtonEvent e)
{

}


//--------------------------------------------------------------
void ofApp::setup() {

	
	



}


//--------------------------------------------------------------
void ofApp::update() {

	

}

//--------------------------------------------------------------
void ofApp::draw() {

	

}

void ofApp::keyPressed(int key)
{
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {



}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {
	
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}


//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

}
