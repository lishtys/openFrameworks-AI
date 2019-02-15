#include "Graph.h"



Graph::Graph()
{
}


Graph::~Graph()
{
}

void Graph::Setup(ofPixels& pix)
{
	width = pix.getWidth(), height = pix.getHeight();
	NodeList.clear();
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++) 
		{
			
			NodeList.push_back(ofPtr<Node>(new Node()));
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

ofPtr<Node>& Graph::GetNode(int x, int y)
{
	return NodeList[y*width + x];
}
