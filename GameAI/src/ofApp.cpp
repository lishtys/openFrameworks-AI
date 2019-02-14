#include "ofApp.h"

#include "BasicMotion.h"
#include "SeekMotion.h"
#include "WanderMotion.h"
#include "FlockMotion.h"


BasicMotion bMotion;
SeekMotion sMotion;
WanderMotion wMotion;
FlockMotion fMotion;
int currentMotionIdx;
//--------------------------------------------------------------
void ofApp::setup() {
	// set up gui

	fMotion.SetApp(*this);
	fMotion.Init();

	gui = new ofxDatGui(ofxDatGuiAnchor::TOP_RIGHT);
	gui->addHeader(":: Controls ::");
	gui->addFooter();

	// weight sliders
	f_weights = gui->addFolder("Weights");

	s_separation = f_weights->addSlider("Separation", 0, 5.0);
	s_alignment = f_weights->addSlider("Alignment", 0, 5.0);
	s_cohesion = f_weights->addSlider("Cohesion", 0, 5.0);
	s_bounding = f_weights->addSlider("Bounding", 0, 5.0);
	s_flee = f_weights->addSlider("Flee", 0, 5.0);

	// weight slider bindings
	s_separation->bind(separation_weight);
	s_alignment->bind(alignment_weight);
	s_cohesion->bind(cohesion_weight);
	s_bounding->bind(bounding_weight);
	s_flee->bind(flee_weight);

	// other controls
	s_speed = gui->addSlider("Simluation Speed", 0, 10.0);
	s_desired_separation = gui->addSlider("Separation Distance", 0, 20.0);
	s_neighbor_radius = gui->addSlider("Neighbor Radius", 0, 20.0);

	t_wraparound = gui->addToggle("Wraparound");
	t_wraparound->onToggleEvent(this, &ofApp::onToggleEvent);

	gui->addFRM(1.0f);

	// and their bindings
	s_speed->bind(sim_speed);
	s_desired_separation->bind(desired_separation);
	s_neighbor_radius->bind(neighbor_search_radius);



}

void ofApp::onToggleEvent(ofxDatGuiToggleEvent e)
{
	cout << e.target->getLabel() << " checked = " << e.checked << endl;
	wraparound = e.checked;
}
//--------------------------------------------------------------
void ofApp::update() {

	fMotion.Update();
	fMotion.maxSpeed = sim_speed;
}

//--------------------------------------------------------------
void ofApp::draw() {

	fMotion.Draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {

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
