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


		void onToggleBoidEvent(ofxDatGuiToggleEvent e);

		ofxDatGui* gui;


		// weights
		ofxDatGuiFolder* f_weights;
		ofxDatGuiDropdown* algorithmnDropdown;

		void onDropdownEvent(ofxDatGuiDropdownEvent e);
		void onMapDropdownEvent(ofxDatGuiDropdownEvent e);
		void onShowNodeDropdownEvent(ofxDatGuiDropdownEvent e);
		void onHeuristicsDropdownEvent(ofxDatGuiDropdownEvent e);
		void onButtonEvent(ofxDatGuiButtonEvent e);
		void onButtonGetPathEvent(ofxDatGuiButtonEvent e);
		
	// ------------


		// bound control variables
	
	

//-- config

	static bool useMap;
	static bool useMazeMap;
	static bool useGoogleMap;
	 
	static  bool useAStar; 
	 
	static bool showImg;
	static bool showUnwalkableNode;
	 
	 
	static int editorRow;
	static int editorColumns;
	static int HeuristicsType;
	static float hWeight;

	static  bool needBoid; 



};


