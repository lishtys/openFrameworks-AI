#pragma once

#include "ofMain.h"
#include "ofxDatGui.h"
#include "Flock.h"


class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);


		void onToggleEvent(ofxDatGuiToggleEvent e);

		ofxDatGui* gui;


		// weights
		ofxDatGuiFolder* f_weights;
		ofxDatGuiSlider* s_separation;
		ofxDatGuiSlider* s_alignment;
		ofxDatGuiSlider* s_cohesion;
		ofxDatGuiSlider* s_bounding;
		ofxDatGuiSlider* s_flee;

		// other controls
		ofxDatGuiSlider* s_speed;
		ofxDatGuiSlider* s_neighbor_radius;
		ofxDatGuiSlider* s_desired_separation;

		ofxDatGuiToggle* t_wraparound;


	// ------------


		// bound control variables
		float desired_separation; // planes within this distance will invoke the force
		float neighbor_search_radius; // planes within this radius are used in calculation
		float sim_speed; // multiplied with the timestep to increase the speed of everything
		bool wraparound; // whether or not to use a sphere or allow position looping

	
		float separation_weight;
		float alignment_weight;
		float cohesion_weight;
		float bounding_weight;
		float flee_weight;


	// Map



};


