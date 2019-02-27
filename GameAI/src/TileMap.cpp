#include "TileMap.h"
#include "ofMesh.h"
#include "ofGLProgrammableRenderer.h"


TileMap::TileMap()
{
}


TileMap::~TileMap()
{
}

void TileMap::Setup(ofPixels& pix)
{
	width = pix.getWidth(), height = pix.getHeight();
	NodeList.clear();
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++) 
		{
			
			NodeList.push_back(ofPtr<Cell>(new Cell()));
			GetNode(x, y)->pos = ofVec2f(x, y);
			float brightness = pix.getColor(x, y).getBrightness() / 255.;
			
			if (brightness == 0.)
			
			{ // black tiles are not walkable
				GetNode(x, y)->SetCost(0);
			}

			else if (brightness < 1.) 
			{ // slow tiles (darker) have higher cost
				GetNode(x, y)->SetCost(1. / brightness);
			}
		}
	}
}

void TileMap::Setup(int col, int row)
{
	width =col, height =row;
	NodeList.clear();
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{

			NodeList.push_back(ofPtr<Cell>(new Cell()));
			GetNode(x, y)->pos = ofVec2f(x, y);
		//	float brightness = pix.getColor(x, y).getBrightness() / 255.;
		//	if (brightness == 0.)
			{ 
				GetNode(x, y)->SetCost(1);
			}

			// else if (brightness < 1.)
			// { // slow tiles (darker) have higher cost
			// 	GetNode(x, y)->SetCost(1. / brightness);
			// }
		}
	}
}

void TileMap::DarwNodes()
{
	for (auto node : NodeList)
	{

		// int x = node->pos.x;
		// int y= node->pos.y;
		//
		// float scaleX = ofGetWidth() / width;
		// float scaleY = ofGetHeight() / height;
		//
		// float cost = node->cost;
		//
		// if(cost>=10)
		// ofSetColor(ofColor::black);
		// else
		// ofSetColor(ofColor::white);
		//
		// ofDrawRectangle((x-1)*scaleX, (y-1) *scaleY, scaleX, scaleY);
	}


		
	}



ofPtr<Cell>& TileMap::GetNode(int x, int y)
{
	return NodeList[y*width + x];
}
