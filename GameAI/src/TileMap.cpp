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


	float scaleX = ofGetWidth() / width;
	float scaleY = ofGetHeight() / height;

	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++) 
		{
			
			NodeList.push_back(ofPtr<Cell>(new Cell()));
			GetNode(x, y)->pos = ofVec2f(x, y);
			float brightness = pix.getColor(x, y).getBrightness() / 255.;
			
			if (brightness < 0.85)
			
			{ // black tiles are not walkable
				GetNode(x, y)->SetCost(0);
			}

			else if (brightness < 1.) 
			{ // slow tiles (darker) have higher cost
				GetNode(x, y)->SetCost(1. / brightness);
			}


			GetNode(x, y)->worldPos.x = scaleX * x;
			GetNode(x, y)->worldPos.y = scaleY * y;


		}
	}
}

void TileMap::Setup(int col, int row)
{
	width =col, height =row;
	NodeList.clear();
	float scaleX = ofGetWidth() / width;
	float scaleY = ofGetHeight() / height;


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


			GetNode(x, y)->worldPos.x = scaleX * x;
			GetNode(x, y)->worldPos.y = scaleY * y;
		}
	}
}

void TileMap::DarwNodes()
{
	


		
	}



ofPtr<Cell>& TileMap::GetNode(int x, int y)
{
	return NodeList[y*width + x];
}
