#pragma once
#include <set>
#include "Node.h"
#include "ofPixels.h"


class Graph
{
public:
	Graph();
	~Graph();


	void Setup(ofPixels& pix);



	ofPtr<Node>& GetNode(int x, int y);
	
	std::vector<ofPtr<Node>> NodeList;

	float width;
	float height;
};

