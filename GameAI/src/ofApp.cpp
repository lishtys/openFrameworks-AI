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
int currentMotionIdx;


AStarPathfinding a_pathfinding;
DFSPathfinding d_pathfinding;

ofImage img_maze;
ofImage img_node;
ofImage img_eae;


ofImage* cur_img;





bool ofApp::useAStar; 
bool  ofApp::useMap;
int ofApp::editorRow;
int ofApp::editorColumns;
int ofApp::HeuristicsType;
float ofApp::hWeight;
bool ofApp::needBoid;
bool ofApp::showImg;
bool ofApp::showUnwalkableNode;





void SetupData()
{
	a_pathfinding.pathList.clear();
	a_pathfinding.srcNode = nullptr;
	a_pathfinding.targetNode = nullptr;	
	
	d_pathfinding.pathList.clear();
	d_pathfinding.srcNode = nullptr;
	d_pathfinding.targetNode = nullptr;
	if (ofApp::useAStar)
	{
		if (ofApp::useMap)
		{
			img_node.loadImage("SimpleNode.png");
			a_pathfinding.m_map.Setup(*cur_img);
		}
		else
		{
			a_pathfinding.m_map.Setup(ofApp::editorRow, ofApp::editorColumns);
		}
	}
	else
	{
		if (ofApp::useMap)
		{
			d_pathfinding.m_map.Setup(*cur_img);
		}
		else
		{

			d_pathfinding.m_map.Setup(ofApp::editorRow, ofApp::editorColumns);
		}

	}
}


void ofApp::onDropdownEvent(ofxDatGuiDropdownEvent e)
{

	cout << "the option at index # " << e.child << " was selected " << endl;
	if (e.child == 0) useAStar = true;
	if (e.child == 1) useAStar = false;
	SetupData();
	
}


void ofApp::onToggleBoidEvent(ofxDatGuiToggleEvent e)
{
	cout << "the option at index # " << e.checked << " was selected " << endl;
	needBoid = e.checked;
	SetupData();
}


void ofApp::onMapDropdownEvent(ofxDatGuiDropdownEvent e)
{
	cout << "the option at index # " << e.child << " was selected " << endl;
	if (e.child == 0) cur_img = NULL;
	if (e.child == 1) cur_img = &img_node;
	if (e.child == 2) cur_img = &img_maze;
	if (e.child == 3) cur_img = &img_eae;

	useMap = e.child != 0;

	SetupData();
}

void ofApp::onShowNodeDropdownEvent(ofxDatGuiDropdownEvent e)
{
	cout << "the option at index # " << e.child << " was selected " << endl;
	 showImg = e.child == 0;
	 showUnwalkableNode = e.child == 1;
	SetupData();
}

void ofApp::onHeuristicsDropdownEvent(ofxDatGuiDropdownEvent e)
{
	cout << "the option at index # " << e.child << " was selected " << endl;
	HeuristicsType = e.child;
	SetupData();
}

void ofApp::onButtonEvent(ofxDatGuiButtonEvent e)
{
		cout << e.target->getLabel() << " was clicked!" << endl;
		SetupData();
}

void ofApp::onButtonGetPathEvent(ofxDatGuiButtonEvent e)
{
	if (useAStar)
	{
		a_pathfinding.GetPath(0,0,0,0);
	}
	else
	{
		d_pathfinding.GetPath(0, 0, 0, 0);
	}
}


//--------------------------------------------------------------
void ofApp::setup() {

	useAStar = true;
	needBoid = false;
	useMap = false;
	showUnwalkableNode = false;
	showImg = true;
	editorColumns = 27;
	editorRow = 50;
	hWeight = 1.0;
	// set up gui


	img_eae.loadImage("EAEBuildingMap.png");
	img_node.loadImage("SimpleNode.png");
	img_maze.loadImage("maze.png");

	{
	 gui = new ofxDatGui(ofxDatGuiAnchor::TOP_RIGHT);
	//  gui->addHeader(":: Controls ::");

	vector<string> options = { "A Star", "D"};
	algorithmnDropdown = gui->addDropdown("A Star", options);
	algorithmnDropdown->select(0);
	algorithmnDropdown->onDropdownEvent(this, &ofApp::onDropdownEvent);


	vector<string> mapOption = { "Editor Mode", "Simple Node","Maze Node","Real Google Map" };
	algorithmnDropdown = gui->addDropdown("Editor Mode", mapOption);
	algorithmnDropdown->select(0);
	algorithmnDropdown->onDropdownEvent(this, &ofApp::onMapDropdownEvent);

	auto s_row = gui->addSlider("Editor Rows", 20, 500);
	s_row->bind(editorRow);

	s_row = gui->addSlider("Editor Column", 20, 270);
	s_row->bind(editorColumns);



	vector<string> iMGOption = { "Show Map", "Show Unwalkable Area", };
	algorithmnDropdown = gui->addDropdown("Show Map", iMGOption);
	algorithmnDropdown->select(0);
	algorithmnDropdown->onDropdownEvent(this, &ofApp::onShowNodeDropdownEvent);


		
	vector<string> Heuristics = { "Manhattan", "Diagonal","Euclidean" };
	algorithmnDropdown = gui->addDropdown("Manhattan", Heuristics);
	algorithmnDropdown->select(0);
	algorithmnDropdown->onDropdownEvent(this, &ofApp::onHeuristicsDropdownEvent);

	s_row = gui->addSlider("Heuristics Weight", 0.1, 20);
	s_row->bind(hWeight);


	gui->addFooter();

	auto toggle=	gui->addToggle("Show Boid");
	toggle->onToggleEvent(this, &ofApp::onToggleBoidEvent);


	auto btn= gui->addButton("Reload");
	btn->onButtonEvent(this, &ofApp::onButtonEvent);
	 btn= gui->addButton("Run Path Finding");
	btn->onButtonEvent(this, &ofApp::onButtonGetPathEvent);

	}

	
	SetupData();
	



}


//--------------------------------------------------------------
void ofApp::update() {

	if(useAStar&&needBoid)
	{
		a_pathfinding.RunBoid();
	}

}

//--------------------------------------------------------------
void ofApp::draw() {

	// ofBackground(0);

	ofSetColor(255);

	if(useMap&&showImg)
	{
		if(cur_img!=NULL)
		cur_img->draw(0, 0, 1920, 1080);
	}
	

	if (useAStar)
	{
		a_pathfinding.m_map.DarwNodes();
		a_pathfinding.Draw();
	}
	else
	{
		d_pathfinding.m_map.DarwNodes();
		d_pathfinding.Draw();
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {

	if (useAStar)
	{
		a_pathfinding.OnKeyPressed(key);
	}
	else
	{
		d_pathfinding.OnKeyPressed(key);
	}

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {


	if (useAStar)
	{
		a_pathfinding.OnKeyReleased(key);

	}
	else
	{
		d_pathfinding.OnKeyReleased(key);
	}

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {
	if (useAStar)
	{
		if(!needBoid)
		a_pathfinding.OnMousePressed(x, y, button);


	}
	else
	{
		d_pathfinding.OnMousePressed(x, y, button);
	}

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {
	if (useAStar&&needBoid){
		a_pathfinding.OnMouseClick(x, y, button);
	}

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
